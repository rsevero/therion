/**
 * @file thconvert.cxx
 */
  
/* Copyright (C) 2005 Martin Budaj
 * 
 * $Date: $
 * $RCSfile: $
 * $Revision: $
 *
 * -------------------------------------------------------------------- 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 * --------------------------------------------------------------------
 */
 
#include <iomanip>
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <regex>

#include <cstring>
#include <cstdio>
#include <cfloat>
#include <cmath>
#include <fmt/core.h>
#include <fmt/ostream.h>

#include "thepsparse.h"
#include "thpdfdbg.h"
#include "thpdfdata.h"
#include "therion.h"
#include "thversion.h"
#include "thconfig.h"
#include "thlegenddata.h"
#include "thtexfonts.h"
#include "thdouble.h"

const int prec_xy = 2;
bool scraps_in_defs = false;

////////////////////////////////////////////////////////////////////////////////

std::string escape_html(std::string s) {
  s = replace_all(s,"<center>","");  // could be implemented using left-aligned table
  s = replace_all(s,"<centre>","");
  s = replace_all(s,"<left>","");
  s = replace_all(s,"<right>","");
  s = replace_all(s,"<br>","\x1B\x1");
  s = replace_all(s,"<thsp>","\x1B\x2");
  s = replace_all(s,"<rm>","\x1B\x3");
  s = replace_all(s,"<it>","\x1B\x4");
  s = replace_all(s,"<bf>","\x1B\x5");
  s = replace_all(s,"<ss>","\x1B\x6");    // which font should we choose?
  s = replace_all(s,"<si>","\x1B\x7");
  s = replace_all(s,"<rtl>","");   // <span dir="rtl"> has no effect
  s = replace_all(s,"</rtl>","");  // in firefox or chrome

  s = replace_all(s,"&","\x1B\x8");
  s = replace_all(s,"<","&lt;");
  s = replace_all(s,">","&gt;");
  s = replace_all(s,"'","&apos;");
  s = replace_all(s,"\"","&quot;");

  std::string t = "";
  std::string close_font = "";
  size_t i;
  for (i=0; i<s.length(); i++) {
    if ((char) s[i] == 27) {
      thassert(i<s.length()-1);
      switch (s[++i]) {
        case 0x1:
          t += "<br/>"; 
          break;
        case 0x2: 
          t += "&thinsp;"; 
          break;
        case 0x3:
        case 0x6:
        case 0x7:
          if (close_font!="") t+= close_font;
          close_font = ""; 
          break;
        case 0x4: 
          if (close_font!="") t+= close_font;
          t += "<i>"; 
          close_font = "</i>"; 
          break;
        case 0x5: 
          if (close_font!="") t+= close_font;
          t += "<b>"; 
          close_font = "</b>"; 
          break;
        case 0x8: 
          t += "&amp;";
          break;
      }
    } else {
      t += s[i];
    }
  }
  if (close_font!="") t+= close_font;

  return t;
}

// https://www.w3.org/TR/SVG2/struct.html#IDAttribute
// https://www.w3.org/TR/xml/#NT-Name
std::string sanitize_xml_id(const std::string& s) {
    if (s.empty()) return "_";
    std::regex invalid_chars("[^a-zA-Z0-9_:.-]");
    std::regex valid_first("^[a-zA-Z_:]");

    std::string sanitized = std::regex_replace(s, invalid_chars, "_");
    if (!std::regex_search(sanitized, valid_first)) sanitized = '_' + sanitized;

    return sanitized;
}

static const char base64_tab[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void base64_encode(const char * fname, std::ofstream & fout) {
  int llength = 0;
  char in_buffer[3];
  unsigned char out_buffer[4];

  std::ifstream fin(fname, std::ios::binary);
  if (!fin) therror((fmt::format("Can't read file {}!\n", fname).c_str()));

  do {
      for (int i = 0; i < 3; i++) in_buffer[i] = '\x0';
      for (int i = 0; i < 4; i++) out_buffer[i] = '=';

      fin.read(in_buffer, 3);
      unsigned long value = 
        ((unsigned char)in_buffer[0]) << 16 |
        ((unsigned char)in_buffer[1]) << 8 |
	((unsigned char)in_buffer[2]) << 0;

      out_buffer[0] = base64_tab[(value >> 18) & 0x3F];
      out_buffer[1] = base64_tab[(value >> 12) & 0x3F];
      if (fin.gcount() > 1) out_buffer[2] = base64_tab[(value >> 6) & 0x3F];
      if (fin.gcount() > 2) out_buffer[3] = base64_tab[(value >> 0) & 0x3F];

      if (llength >= 76) {
        fout << '\n';
        llength = 0;
      }
      fout << out_buffer[0] << out_buffer[1] << out_buffer[2] << out_buffer[3];
      llength += 4;
  } while (fin);

  fin.close();
}

void find_dimensions(double & MINX,double & MINY,double & MAXX,double & MAXY) {
  double llx = 0, lly = 0, urx = 0, ury = 0;
  double a,b,w,h;
  MINX=DBL_MAX, MINY=DBL_MAX, MAXX=-DBL_MAX, MAXY=-DBL_MAX;
  for (std::list<scraprecord>::iterator I = SCRAPLIST.begin(); 
                                  I != SCRAPLIST.end(); I++) {
    llx = DBL_MAX; lly = DBL_MAX; urx = -DBL_MAX; ury = -DBL_MAX;
    if (I->F != "" && I->E == "" && I->G == "" && 
        I->B == "" && I->X == "") { // clipped symbols shouldn't affect map size
      if (I->F1 < llx) llx = I->F1;
      if (I->F2 < lly) lly = I->F2;
      if (I->F3 > urx) urx = I->F3;
      if (I->F4 > ury) ury = I->F4;
    }
    if (I->E != "") {
      if (I->E1 < llx) llx = I->E1;
      if (I->E2 < lly) lly = I->E2;
      if (I->E3 > urx) urx = I->E3;
      if (I->E4 > ury) ury = I->E4;
    }
    if (I->G != "") {
      if (I->G1 < llx) llx = I->G1;
      if (I->G2 < lly) lly = I->G2;
      if (I->G3 > urx) urx = I->G3;
      if (I->G4 > ury) ury = I->G4;
    }
    if (I->B != "") {
      if (I->B1 < llx) llx = I->B1;
      if (I->B2 < lly) lly = I->B2;
      if (I->B3 > urx) urx = I->B3;
      if (I->B4 > ury) ury = I->B4;
    }
    if (I->I != "") {
      if (I->I1 < llx) llx = I->I1;
      if (I->I2 < lly) lly = I->I2;
      if (I->I3 > urx) urx = I->I3;
      if (I->I4 > ury) ury = I->I4;
    }
    if (I->X != "") {
      if (I->X1 < llx) llx = I->X1;
      if (I->X2 < lly) lly = I->X2;
      if (I->X3 > urx) urx = I->X3;
      if (I->X4 > ury) ury = I->X4;
    }
    for (std::list<surfpictrecord>::iterator I_sk = I->SKETCHLIST.begin();
                                          I_sk != I->SKETCHLIST.end(); I_sk++) {
      for (int i = 0; i<=1; i++) {
        for (int j = 0; j<=1; j++) {
          w = i * I_sk->width;
          h = j * I_sk->height;
          a = I_sk->xx*w + I_sk->xy*h + I_sk->dx;
          b = I_sk->yx*w + I_sk->yy*h + I_sk->dy;
          if (a < llx) llx = a;
          if (b < lly) lly = b;
          if (a > urx) urx = a;
          if (b > ury) ury = b;
        }
      }
    };


    if (llx == DBL_MAX || lly == DBL_MAX || urx == -DBL_MAX || ury == -DBL_MAX) 
      therror(("This can't happen -- no data for a scrap!"));
    
    std::map<int,layerrecord>::iterator J = LAYERHASH.find(I->layer);
    thassert(J != LAYERHASH.end());

    std::map<int,std::set<std::string> >::iterator K = (((*J).second).scraps).find(I->level);
    if (K == (((*J).second).scraps).end()) {
      std::set<std::string> SCRP;
      (((*J).second).scraps).insert(make_pair(I->level,SCRP));
      K = (((*J).second).scraps).find(I->level);
    }
    ((*K).second).insert(I->name);
    
    (((*J).second).allscraps).insert(I->name); 
      
    if (((*J).second).Z == 0) {
      if (MINX > llx) MINX = llx;
      if (MINY > lly) MINY = lly;
      if (MAXX < urx) MAXX = urx;
      if (MAXY < ury) MAXY = ury;
    }
  }
}


void print_preview(int up,std::ofstream& F, std::string unique_prefix) {
  std::set<int> used_layers;
  std::set<std::string> used_scraps;
  
  if (up) { 
    F << "<g id=\":preview_above:\" fill=\"none\" stroke=\"" <<
       LAYOUT.col_preview_above.to_svg() << "\" stroke-width=\"0.1\">\n";
  }
  else { 
    F << "<g id=\":preview_below:\" stroke=\"none\" fill=\"" <<
       LAYOUT.col_preview_below.to_svg() << "\">\n";
  }
  used_layers = (up ? MAP_PREVIEW_UP : MAP_PREVIEW_DOWN);
  for (std::set<int>::iterator I=used_layers.begin(); I != used_layers.end(); I++) {
    std::map<int,layerrecord>::iterator J = LAYERHASH.find(*I);
    thassert (J != LAYERHASH.end());
    used_scraps = J->second.allscraps;
    if (!used_scraps.empty()) {
      for (std::list<scraprecord>::iterator K = SCRAPLIST.begin(); K != SCRAPLIST.end(); K++) {
        if (used_scraps.count(K->name) > 0) {
          if (up) {
            if (K->B != "" && K->sect == 0) {
              if (scraps_in_defs)
                F << "<use x=\"" << K->B1 << "\" y=\"" << K->B2 << "\" xlink:href=\"#B_" << K->name << "_" << unique_prefix << "\" />\n";
              else {
                F << "<g transform=\"translate(" << K->B1 << " " << K->B2 << ")\" id=\"" << sanitize_xml_id(K->src_name) << "." <<
                   sanitize_xml_id(K->src_survey) << ":preview_above:" << K->id << "\">\n";
                K->Bc.MP.print_svg(F, unique_prefix);
                F << "</g>\n";
              }
            }
          }
          else {
            if (K->I != "" && K->sect == 0) {
              if (scraps_in_defs)
                F << "<use x=\"" << K->I1 << "\" y=\"" << K->I2 << "\" xlink:href=\"#I_" << K->name << "_" << unique_prefix << "\" />\n";
              else {
                F << "<g transform=\"translate(" << K->I1 << " " << K->I2 << ")\" id=\"" << sanitize_xml_id(K->src_name) << "." <<
                   sanitize_xml_id(K->src_survey) << ":preview_below:" << K->id << "\">\n";
                K->Ic.MP.print_svg(F, unique_prefix);
                F << "</g>\n";
              }
            }
          }
        }
      }
    }
  }
  F << "</g>\n";
}


void print_grid(std::ofstream& PAGEDEF, double LLX,double LLY,double URX,double URY, std::string unique_prefix) {
  if (LAYOUT.grid == 0) return;
  PAGEDEF << "<g id=\":grid:\">\n";
  
  paired ll, ur, lr, ul, llrot, urrot, ulrot, lrrot, llnew, urnew, origin;
  ll.x = LLX;
  ll.y = LLY; 
  ur.x = URX;
  ur.y = URY; 
  lr.x = ur.x;
  lr.y = ll.y;
  ul.x = ll.x;
  ul.y = ur.y;
  origin.x = LAYOUT.hgridorigin;
  origin.y = LAYOUT.vgridorigin;
//cout << '\n' << origin.x << " " << origin.y << '\n';
  llrot = rotatedaround(ll,origin,-LAYOUT.gridrot);
  urrot = rotatedaround(ur,origin,-LAYOUT.gridrot);
  lrrot = rotatedaround(lr,origin,-LAYOUT.gridrot);
  ulrot = rotatedaround(ul,origin,-LAYOUT.gridrot);
  
  llnew.x = std::min(std::min(llrot.x, urrot.x), std::min(lrrot.x, ulrot.x));
  llnew.y = std::min(std::min(llrot.y, urrot.y), std::min(lrrot.y, ulrot.y));
  urnew.x = std::max(std::max(llrot.x, urrot.x), std::max(lrrot.x, ulrot.x));
  urnew.y = std::max(std::max(llrot.y, urrot.y), std::max(lrrot.y, ulrot.y));
  
  double grid_init_x = LAYOUT.hgridsize * floor ((llnew.x-origin.x)/LAYOUT.hgridsize) + origin.x;
  double grid_init_y = LAYOUT.vgridsize * floor ((llnew.y-origin.y)/LAYOUT.vgridsize) + origin.y;

double G_real_init_x = LAYOUT.XO + LAYOUT.XS * floor ((llnew.x-origin.x)/LAYOUT.hgridsize);
double G_real_init_y = LAYOUT.YO + LAYOUT.YS * floor ((llnew.y-origin.y)/LAYOUT.vgridsize);

  double cosr = cos(-LAYOUT.gridrot * 3.14159265 / 180);
  double sinr = sin(-LAYOUT.gridrot * 3.14159265 / 180);

  int row, col, elem;

  if (LAYOUT.proj == 0) {
    paired out,tmp;
    int ii,jj;
    double i, j;
    for (i = grid_init_x, ii=0; i < urnew.x + LAYOUT.hgridsize - 0.05; i += LAYOUT.hgridsize, ii++) {
      for (j = grid_init_y, jj=0; j < urnew.y + LAYOUT.vgridsize - 0.05; j += LAYOUT.vgridsize, jj++) {
        col = (i == grid_init_x ? 0 : (i >= urnew.x ? 2 : 1));
        row = (j == grid_init_y ? 0 : (j >= urnew.y ? 2 : 1));
	elem = col + 3*row;
        tmp.x = i+LAYOUT.gridcell[elem].x;
        tmp.y = j+LAYOUT.gridcell[elem].y;
        out = rotatedaround(tmp,origin,LAYOUT.gridrot);
//        out.x -= LLX;
//        out.y -= LLY;
        PAGEDEF << "<g transform=\"matrix(" << 
                   cosr << " " << sinr << " " << -sinr << " " << cosr << " " << 
                   out.x << " " << out.y << ")\">";
	PAGEDEF << "<use xlink:href=\"#grid_" << u2str(elem+1) << "_" << unique_prefix << "\" />";
        PAGEDEF << "</g>\n";

        if (LAYOUT.grid_coord_freq==2 || (LAYOUT.grid_coord_freq==1 && elem!=4)) {
          tmp.x = i+ (col==2 ? -2 : 2);
          tmp.y = j+ (row==2 ? -9 : 2);
          out = rotatedaround(tmp,origin,LAYOUT.gridrot);
          PAGEDEF << "<text fill=\"black\" stroke=\"none\" font-size=\"8\" " <<
	          (col == 2 ? "text-anchor=\"end\" " : "") <<
                  "transform=\"matrix(" << 
                   cosr << " " << sinr << " " << sinr << " " << -cosr << " " << 
                   out.x << " " << out.y << ")\">(" << 
	      std::setprecision(0) << G_real_init_x+ii*LAYOUT.XS << "," << 
              G_real_init_y+jj*LAYOUT.YS << std::setprecision(3) << ")</text>\n";
        }
  
/*  PAGEDEF << "<text font-family=\"arial\" font-size=\"10\" " <<
       "transform=\"matrix(" << 
                   1 << " " << 0 << " " << 0 << " " << -1 << " " << 
                   out.x << " " << out.y << ")\">";
  PAGEDEF << i/72*2.54/100*200 << " " << j/72*2.54/100*200;
  PAGEDEF << "</text>\n";*/
	
      }
    }
  }
  else {
    grid_init_x = LLX;
    int jj;
    double i, j;
    for (j = grid_init_y, jj=0; j < urnew.y + LAYOUT.vgridsize - 0.05; j += LAYOUT.vgridsize, jj++) {
      for (i = grid_init_x; i < urnew.x + LAYOUT.hgridsize - 0.05; i += LAYOUT.hgridsize) {
        col = (i == grid_init_x ? 0 : (i >= urnew.x ? 2 : 1));
        row = (j == grid_init_y ? 0 : (j >= urnew.y ? 2 : 1));
	elem = col + 3*row;
	PAGEDEF << "<use x=\"" << i/*-LLX*/+LAYOUT.gridcell[elem].x << "\" y=\"" << 
	                      j/*-LLY*/+LAYOUT.gridcell[elem].y << "\" xlink:href=\"#grid_" << "_" << unique_prefix << 
			      u2str(elem+1) << "\" />\n";
        if (col == 0 && LAYOUT.grid_coord_freq > 0) {
          PAGEDEF << "<text fill=\"black\" stroke=\"none\" font-size=\"8\" " << 
	      "transform=\"matrix(1,0,0,-1," << i << "," << 
	      j+1 /* podvihnutie o 1 bp */ << ")\">" << 
	      std::setprecision(0) << G_real_init_y+jj*LAYOUT.YS << "</text>\n";
	}
        if (col == 2 && LAYOUT.grid_coord_freq == 2) {
          PAGEDEF << "<text fill=\"black\" stroke=\"none\" font-size=\"8\" " << 
	      "transform=\"matrix(1,0,0,-1," << i << "," << 
	      j+1 /* podvihnutie o 1 bp */ << ")\" text-anchor=\"end\">" << 
	      std::setprecision(0) << G_real_init_y+jj*LAYOUT.YS << "</text>\n";
        }
      }
    }
  } 

  PAGEDEF << "</g>\n";
}

void print_surface_bitmaps (std::ofstream &F) {
  if (LAYOUT.transparency) 
    F << "<g id=\":surface_bitmap:\" opacity=\"" << LAYOUT.surface_opacity << "\">\n";
  F.precision(8);
  for (std::list<surfpictrecord>::iterator I = SURFPICTLIST.begin();
                                      I != SURFPICTLIST.end(); I++) {
    F << "<g transform=\"matrix(";
    F << I->xx << " " << I->yx << " " << -I->xy << " " << -I->yy << " " << 
         I->dx << " " << I->dy << ")\">";
    F << "<image x=\"0\" y=\"" << -I->height << "\" width=\"" << I->width << 
         "\" height=\"" << I->height << "\" xlink:href=\"data:image/" << 
         I->type << ";base64,\n";
    base64_encode(I->filename, F);
    F << "\" />";
    F << "</g>\n";
  };
  F.precision(3);
  if (LAYOUT.transparency) 
    F << "</g>\n";
}



#define ginit(ID) F << "<g id=\"" << ID << "_" << unique_prefix << "\">\n";
#define gend  F << "</g>\n";



void thsvg(const char * fname, int fmt, const legenddata& ldata) {
  if (fmt == 0)
    thprint("making svg map ... ");
  else
    thprint("making svg (xhtml) map ... ");
  std::string bgcol;
  std::string unique_prefix = fname;

  std::ofstream F(fname, std::ios_base::binary);
  F.setf(std::ios::fixed, std::ios::floatfield);  // dolezite pre velke suradnice
  F.precision(3);
  
  double llx=0, lly=0, urx=0, ury=0;
  find_dimensions(llx, lly, urx, ury);

  if (LAYOUT.proj > 0 && LAYOUT.grid > 0) {  // natiahnutie vysky aby sa zobrazil grid pod aj nad jaskynou
    lly = LAYOUT.vgridsize * floor ((lly-LAYOUT.vgridorigin)/LAYOUT.vgridsize) + LAYOUT.vgridorigin;
    ury = LAYOUT.vgridsize * ceil  ((ury-LAYOUT.vgridorigin)/LAYOUT.vgridsize) + LAYOUT.vgridorigin;
  }
  if (LAYOUT.map_grid) {
    llx = LAYOUT.hsize * floor (llx/LAYOUT.hsize);
    lly = LAYOUT.vsize * floor (lly/LAYOUT.vsize);
    urx = LAYOUT.hsize * ceil (urx/LAYOUT.hsize);
    ury = LAYOUT.vsize * ceil (ury/LAYOUT.vsize);
  }

  double llxo(llx), llyo(lly), urxo(urx), uryo(ury);  // rozmery mapy bez overlapu

  llx -= LAYOUT.overlap;
  urx += LAYOUT.overlap;
  lly -= LAYOUT.overlap;
  ury += LAYOUT.overlap;

  F << "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"no\"?>\n";

  F << "<!-- Generated by Therion";
  if (!thcfg.reproducible_output) {
    F << " " << THVERSION;
  }
  F << " -->\n";
  if (LAYOUT.doc_author != "") 
    F << "<!-- Author: " << LAYOUT.doc_author << " -->\n";
  if (LAYOUT.doc_title != "") 
    F << "<!-- Title: " << LAYOUT.doc_title << " -->\n";
  if (LAYOUT.doc_subject != "") 
    F << "<!-- Subject: " << LAYOUT.doc_subject << " -->\n";
  if (LAYOUT.doc_keywords != "") 
    F << "<!-- Keywords: " << LAYOUT.doc_keywords << " -->\n";

  if (fmt == 0)
    F << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
  else {
    F << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n";
    F << "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n";
    F << "<body>\n";
    // title
    if (!ldata.cavename.empty()) F << "<h2>" << escape_html(ldata.cavename) << "</h2>\n";
    if (!ldata.comment.empty()) F << "<p>" << escape_html(ldata.comment) << "</p>\n";
    // north, scale
    // ...
    if (!ldata.cavelength.empty()) F << "<p><i>" << escape_html(ldata.cavelengthtitle) << ":</i> " << ldata.cavelength << "</p>\n";
    if (!ldata.cavedepth.empty()) F << "<p><i>" << escape_html(ldata.cavedepthtitle) << ":</i> " << ldata.cavedepth << "</p>\n";
    if (!ldata.copyrights.empty()) F << "<p>" << escape_html(ldata.copyrights) << "</p>\n";
    if (ldata.scalebar && LAYOUT.scalebar != "") {
      F << "<p>\n";
      ScBar.print_svg(F,unique_prefix);
      F << "</p>\n";
    }
    if (ldata.northarrow && LAYOUT.northarrow != "") {
      F << "<p>\n";
      NArrow.print_svg(F,unique_prefix);
      F << "</p>\n";
    }
  }

  F << "<svg width=\"" << 2.54/72*(urx-llx) << 
        "cm\" height=\"" << 2.54/72*(ury-lly) << 
        "cm\" viewBox=\"" << llx << " " << -ury << 
        " " << urx-llx << " " << ury-lly << 
        "\" xmlns=\"http://www.w3.org/2000/svg\" " << // pridane pre xhtml
        "xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n";

  F << "<defs>\n";
  // patterns:
  // pattern is clipped according to width and height attributes;
  // it's not possible to specify clipping area independently
  // like using BBox in PDF -- may produce some strange results
  // if the pattern definition exceeds the BBox in MetaPost
  for (std::list<pattern>::iterator I = PATTERNLIST.begin();
                               I != PATTERNLIST.end(); I++) {
    if (I->used) {
      F << "<pattern id=\"patt_" << I->name << "_" << unique_prefix <<
           "\" patternUnits=\"userSpaceOnUse\"" << 
           " width=\"" << I->xstep <<   
           "\" height=\"" << I->ystep << 
           "\" patternTransform=\"matrix(" << I->xx << " " << I->xy << " " 
                                           << I->yx << " " << I->yy << " " 
                                           << I->x <<  " " << I->y  << 
           ")\">\n";
      F << "<g transform=\"translate(" 
                    << I->llx1-I->llx << " " << I->lly1-I->lly << ")\"" <<
                       " fill=\"black\" stroke=\"black\">\n";
                       // currentColor doesn't work to inherit the color of the symbol;
                       // context-fill/stroke doesn't work in patterns
      I->data.MP.print_svg(F,unique_prefix);
      F << "</g>\n";
      F << "</pattern>\n";
    }
  }
  // gradients
  for (auto &g: GRADIENTS) {
    if (!g.second.used_in_map) continue;
    if (g.second.type == gradient_lin) {
      fmt::print(F, "<linearGradient id=\"grad_{:s}_{:s}\" gradientUnits=\"userSpaceOnUse\" x1=\"{}\" y1=\"{}\" x2=\"{}\" y2=\"{}\">\n",
                 g.first, unique_prefix, thdouble(g.second.x0,prec_xy), thdouble(g.second.y0,prec_xy), thdouble(g.second.x1,prec_xy), thdouble(g.second.y1,prec_xy));
    } else {
      fmt::print(F, "<radialGradient id=\"grad_{:s}_{:s}\" gradientUnits=\"userSpaceOnUse\" fx=\"{}\" fy=\"{}\" fr=\"{}\" cx=\"{}\" cy=\"{}\" r=\"{}\">\n",
                 g.first, unique_prefix, thdouble(g.second.x0,prec_xy), thdouble(g.second.y0,prec_xy), thdouble(g.second.r0,prec_xy),
                                         thdouble(g.second.x1,prec_xy), thdouble(g.second.y1,prec_xy), thdouble(g.second.r1,prec_xy));
    }
    F << "<stop offset=\"0%\" stop-color=\"" << g.second.c0.to_svg() << "\"/>\n";
    F << "<stop offset=\"100%\" stop-color=\"" << g.second.c1.to_svg() << "\"/>\n";
    if (g.second.type == gradient_lin) {
      F << "</linearGradient>\n";
    } else {
      F << "</radialGradient>\n";
    }
  }
  // scraps:
  if (scraps_in_defs)
    for(std::list<scraprecord>::iterator I = SCRAPLIST.begin();
                                  I != SCRAPLIST.end(); I++) {
      ginit("F_" + I->name); I->Fc.MP.print_svg(F,unique_prefix); gend;
      ginit("G_" + I->name); I->Gc.MP.print_svg(F,unique_prefix); gend;
      ginit("B_" + I->name); I->Bc.MP.print_svg(F,unique_prefix); gend;
      ginit("I_" + I->name); I->Ic.MP.print_svg(F,unique_prefix); gend;
      ginit("E_" + I->name); I->Ec.MP.print_svg(F,unique_prefix); gend;
      ginit("X_" + I->name); I->Xc.MP.print_svg(F,unique_prefix); gend;
    }
  // grid:
  int i=0;
  for (std::list<converted_data>::iterator I = GRIDLIST.begin();
                                      I != GRIDLIST.end(); I++) {
    ginit("grid_" + u2str(++i)); I->MP.print_svg(F,unique_prefix); gend;
  }
  // clip to initial viewBox
  // (browsers mostly ignore clip="auto" overflow="hidden" root svg attributes)
  F << "<clipPath id=\"clip_viewBox\">\n";
    F << "<path d=\"M" << llx << " " << lly << 
         "L" << urx << " " << lly << 
         "L" << urx << " " << ury << 
         "L" << llx << " " << ury << "z\" />\n";
  F << "</clipPath>\n";
  
  F << "</defs>\n";
  // --- end of definitions ---

  F << "<g transform=\"scale(1,-1)\" fill=\"#000000\" stroke=\"#000000\" stroke-linecap=\"round\" stroke-linejoin=\"round\" stroke-miterlimit=\"10\" fill-rule=\"evenodd\" clip-rule=\"evenodd\" clip-path=\"url(#clip_viewBox)\" id=\"root\">\n";
  // page background:
  if (!LAYOUT.col_background.is_white()) {
    F << "<rect x=\"" << llx << "\" y=\"" << lly << 
         "\" width=\"" << urx-llx << "\" height=\"" << ury-lly << 
         "\" stroke=\"none\" fill=\"" << LAYOUT.col_background.to_svg() << "\" />\n";
  }
    
  // surface:
  if (LAYOUT.surface == 1) print_surface_bitmaps(F);

  // white scrap backgrounds (when transparency added):
  // grid:
  if (LAYOUT.grid == 1) print_grid(F,llxo,llyo,urxo,uryo,unique_prefix);

  // preview down:
  if (!MAP_PREVIEW_DOWN.empty()) print_preview(0,F,unique_prefix);
  
  // map export:
  for (std::map<int,layerrecord>::iterator J = LAYERHASH.begin();
                                      J != LAYERHASH.end(); J++) {
    if (J->second.Z == 0) {
      F << "<g id=\"" << sanitize_xml_id(J->second.Nraw) << ":map:" << J->first << "\">\n";
      std::map < int,std::set<std::string> > LEVEL;
      std::set <std::string> page_text_scraps,used_scraps;
      LEVEL = J->second.scraps;
      /*for (map < int,set<string> >::iterator I_l = LEVEL.begin();
                                             I_l != LEVEL.end(); I_l++) {
        used_scraps = I_l->second;
        for (std::list<scraprecord>::iterator K = SCRAPLIST.begin(); 
                                         K != SCRAPLIST.end(); K++) {
           if (used_scraps.count(K->name) > 0 && K->P != "") 
              page_text_scraps.insert(K->name);
        }
      }*/
      for (std::map < int,std::set<std::string> >::iterator I = LEVEL.begin();
                                             I != LEVEL.end(); I++) {
        used_scraps = I->second;
        
        // background
        for (std::list<scraprecord>::iterator K = SCRAPLIST.begin(); 
                                         K != SCRAPLIST.end(); K++) {
          if (!K->col_scrap.is_defined()) {
            bgcol=LAYOUT.col_foreground.to_svg();
          }
          else {
            bgcol=K->col_scrap.to_svg();
          }
          if (used_scraps.count(K->name) > 0 && K->I != "") {
            if (scraps_in_defs) {
              F << "<g fill=\"" << bgcol << "\">\n";
              F << "<use x=\"" << K->I1 << "\" y=\"" << K->I2 << "\" xlink:href=\"#I_" << K->name << "_" << unique_prefix << "\" />\n";
              F << "</g>\n";
            } else {
              F << "<g fill=\"" << bgcol << "\" transform=\"translate(" << K->I1 << " " << K->I2 << ")\" id=\"" << sanitize_xml_id(K->src_name) << "." <<
                   sanitize_xml_id(K->src_survey) << ":background:" << K->id << "\">\n";
              K->Ic.MP.print_svg(F, unique_prefix);
              F << "</g>\n";
            }
          }
        }

//    F << "<use x=\"" << I->G1 << "\" y=\"" << -I->G2 << "\" xlink:href=\"#G_" << I->name << "_" << unique_prefix << "\" />\n";

        // sketches
        F.precision(8);
        for (std::list<scraprecord>::iterator K = SCRAPLIST.begin(); 
                                         K != SCRAPLIST.end(); K++) {
          for (std::list<surfpictrecord>::iterator I_sk = K->SKETCHLIST.begin();
                                              I_sk != K->SKETCHLIST.end(); I_sk++) {
            F << "<g transform=\"matrix(";
            F << I_sk->xx << " " << I_sk->yx << " " << -I_sk->xy << " " << -I_sk->yy << " " << 
                 I_sk->dx << " " << I_sk->dy << ")\">";
            F << "<image x=\"0\" y=\"" << -I_sk->height << "\" width=\"" << I_sk->width << 
                 "\" height=\"" << I_sk->height << "\" xlink:href=\"data:image/" << 
                 I_sk->type << ";base64,\n";
            base64_encode(I_sk->filename, F);
            F << "\" />";
            F << "</g>\n";
          };
        }
        F.precision(3);
        
        // end of sketches


        for (std::list<scraprecord>::iterator K = SCRAPLIST.begin(); 
                                         K != SCRAPLIST.end(); K++) {
          if (used_scraps.count(K->name) > 0 && K->F != "") {
            if (scraps_in_defs)
              F << "<use x=\"" << K->F1 << "\" y=\"" << K->F2 << "\" xlink:href=\"#F_" << K->name << "_" << unique_prefix << "\" />\n";
            else {
              F << "<g transform=\"translate(" << K->F1 << " " << K->F2 << ")\" id=\"" << sanitize_xml_id(K->src_name) << "." <<
                   sanitize_xml_id(K->src_survey) << ":clipped_content:" << K->id << "\">\n";
              K->Fc.MP.print_svg(F, unique_prefix);
              F << "</g>\n";
            }
          }
        }

        for (std::list<scraprecord>::iterator K = SCRAPLIST.begin(); 
                                         K != SCRAPLIST.end(); K++) {
          if (used_scraps.count(K->name) > 0 && K->E != "") {
            if (scraps_in_defs)
              F << "<use x=\"" << K->E1 << "\" y=\"" << K->E2 << "\" xlink:href=\"#E_" << K->name << "_" << unique_prefix << "\" />\n";
            else {
              F << "<g transform=\"translate(" << K->E1 << " " << K->E2 << ")\" id=\"" << sanitize_xml_id(K->src_name) << "." <<
                   sanitize_xml_id(K->src_survey) << ":unclipped_content:" << K->id << "\">\n";
              K->Ec.MP.print_svg(F, unique_prefix);
              F << "</g>\n";
            }
          }
        }

        for (std::list<scraprecord>::iterator K = SCRAPLIST.begin(); 
                                         K != SCRAPLIST.end(); K++) {
          if (used_scraps.count(K->name) > 0 && K->X != "") {
            if (scraps_in_defs)
              F << "<use x=\"" << K->X1 << "\" y=\"" << K->X2 << "\" xlink:href=\"#X_" << K->name << "_" << unique_prefix << "\" />\n";
            else {
              F << "<g transform=\"translate(" << K->X1 << " " << K->X2 << ")\" id=\"" << sanitize_xml_id(K->src_name) << "." <<
                   sanitize_xml_id(K->src_survey) << ":texts:" << K->id << "\">\n";
              K->Xc.MP.print_svg(F, unique_prefix);
              F << "</g>\n";
            }
          }
        }

      }
      F << "</g>\n";  // end of the layer group
    }
  }

  // preview up:
  if (!MAP_PREVIEW_UP.empty()) print_preview(1,F,unique_prefix);
  
  // surface:
  if (LAYOUT.surface == 2) print_surface_bitmaps(F);

  // grid:
  if (LAYOUT.grid == 2) print_grid(F,llxo,llyo,urxo,uryo,unique_prefix);

  // map grid:
  if (LAYOUT.map_grid) {
    F << "<g id=\":map_grid:\" stroke=\"#000000\" fill=\"none\" stroke-width=\"0.4\">\n";
    F << "<rect x=\"" << llxo << "\" y=\"" << llyo << 
         "\" width=\"" << urxo-llxo << "\" height=\"" << uryo-llyo << 
         "\" />\n";
    for (double i=llxo; i <= urxo; i += LAYOUT.hsize) {
      F << "<line x1=\"" << i << "\" y1=\"" << llyo << "\" x2=\"" << i << "\" y2=\"" << uryo << "\" />\n";
    }
    for (double i=llyo; i <= uryo; i += LAYOUT.vsize) {
      F << "<line x1=\"" << llxo << "\" y1=\"" << i << "\" x2=\"" << urxo << "\" y2=\"" << i << "\" />\n";
    }
    F << "</g>\n";
  }

  F << "</g>\n";
  F << "</svg>\n";
  // end of main SVG data block

  if (fmt > 0) {  // legend in xhtml
    // title
    if (!ldata.exploteam.empty()) F << "<p><i>" << escape_html(ldata.explotitle) << ":</i> " << escape_html(ldata.exploteam) << 
          " <i>" << ldata.explodate << "</i></p>\n";
    if (!ldata.topoteam.empty()) F << "<p><i>" << escape_html(ldata.topotitle) << ":</i> " << escape_html(ldata.topoteam) << 
          " <i>" << ldata.topodate << "</i></p>\n";
    if (!ldata.cartoteam.empty()) F << "<p><i>" << escape_html(ldata.cartotitle) << ":</i> " << escape_html(ldata.cartoteam) << 
          " <i>" << ldata.cartodate << "</i></p>\n";

    // color legend
    if (LAYOUT.altitudebar.empty() && !COLORLEGENDLIST.empty()) {
      F << "<h3>" << escape_html(ldata.colorlegendtitle) << "</h3>\n";
      F << "<table cellspacing=\"5\">\n";
      for(std::list<colorlegendrecord>::iterator I = COLORLEGENDLIST.begin(); I != COLORLEGENDLIST.end(); I++) {
        F << "<tr>\n";
        F << "<td style=\"background-color: " << I->col_legend.to_svg() <<
             "; height: 24px; width: 36px;\">\n";
        F << "</td><td>" << I->name << "</td>\n";
        F << "</tr>\n";
      }
      F << "</table>\n";
    } else if (!LAYOUT.altitudebar.empty()) {
      F << "<p>\n";
      AltBar.print_svg(F,unique_prefix);
      F << "</p>\n";
    }

    // map symbols
    if (!LEGENDLIST.empty()) {
      F << "<h3>" << escape_html(ldata.legendtitle) << "</h3>\n";

      std::vector<legendrecord> L;
      for(std::list<legendrecord>::iterator I = LEGENDLIST.begin(); 
          I != LEGENDLIST.end(); I++) {
            L.push_back(*I);
      }
      int legendbox_num = LEGENDLIST.size();
      int columns = LAYOUT.legend_columns; 
      int rows = (int) ceil(double(legendbox_num) / columns);
      int pos = 0;

      F << "<table cellspacing=\"5\">\n";
      for (int i = 0; i < rows; i++) {
        F << "<tr>\n";
        for (int j = 0; j < columns; j++) {
          F << "<td>\n";
          pos = i + j * rows;
          if (pos < legendbox_num) {
            L[pos].ldata.print_svg(F,unique_prefix);
            F << L[pos].descr;
            // F << "</p>\n";
          }
          F << "</td>\n";
        }
        F << "</tr>\n";
      }
      F << "</table>\n";
    }

    F << "</body>\n" << "</html>\n";
  }

  F.close();
  thprint("done\n");
}


