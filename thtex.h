/**
 * @file thtex.h
 *
 * THIS FILE IS GENERATED AUTOMATICALLY, DO NOT MODIFY IT !!!
 */  
 
#ifndef thtex_h
#define thtex_h

/**
 * Metapost source file.
 */
 
const char * thtex_library = 
"%% \n"
"%% therion.tex\n"
"%%\n"
"%% Copyright (C) 2001-2004 Martin Budaj\n"
"%%\n"
"%% -------------------------------------------------------------------- \n"
"%% This program is free software; you can redistribute it and/or modify\n"
"%% it under the terms of the GNU General Public License as published by\n"
"%% the Free Software Foundation; either version 2 of the License, or\n"
"%% any later version.\n"
"%%\n"
"%% This program is distributed in the hope that it will be useful,\n"
"%% but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"%% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"%% GNU General Public License for more details.\n"
"%% \n"
"%% You should have received a copy of the GNU General Public License\n"
"%% along with this program; if not, write to the Free Software\n"
"%% Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA\n"
"%% -------------------------------------------------------------------- \n"
"\n"
"\\ifx\\pdfoutput\\undefined\n"
"     \\newlinechar`\\^^J\n"
"     \\immediate\\write16{^^J^^JProcess me with pdfTeX, please!^^J^^J}\n"
"     \\expandafter\\end\n"
"\\fi\n"
"\n"
"\\def\\requiredformat{plain}\n"
"\\ifx\\requiredformat\\fmtname\\else\n"
"     \\newlinechar`\\^^J\n"
"     \\immediate\\write16{^^J^^JTherion works only with plain TeX format!^^J}\n"
"     \\immediate\\write16{Your format is: \\fmtname^^J^^J}\n"
"     \\expandafter\\end\n"
"\\fi\n"
"\n"
"\\def\\wlog#1{}\n"
"\n"
"\n"
"\\parindent=0pt\n"
"\\raggedbottom\n"
"\\nopagenumbers\n"
"\\tracingstats=1\n"
"\\pdfimageresolution=300\n"
"\n"
"%\\pdfinfo{/Creator <feff%\n"
"%  03b803b703c103af03bf03bd0020%\n"
"%  002800740068006500720069006f006e0029002c0020%\n"
"%  004d0065007400610050006f00730074002c0020%\n"
"%  005400650058>}%\n"
"\n"
"\\newbox\\xxx\n"
"\\newbox\\mapbox\n"
"\\newbox\\navbox\n"
"\\newcount\\pointerE\n"
"\\newcount\\pointerW\n"
"\\newcount\\pointerN\n"
"\\newcount\\pointerS\n"
"\\newtoks\\pointerU\n"
"\\newtoks\\pointerD\n"
"\\newcount\\pagenum\n"
"\\newtoks\\pagename\n"
"\\newtoks\\pagelabel\n"
"\\newtoks\\opacity \\opacity{0.7}\n"
"\\newtoks\\surfaceopacity \\surfaceopacity{0.7}\n"
"\\newif\\ifpagenumbering \\pagenumberingfalse\n"
"\\newtoks\\bgcolor\n"
"\\newif\\iflegendbgfill\n"
"\n"
"\\let\\ne\\noexpand\n"
"\\def\\notdef{notdef}\n"
"\n"
"% hyperlinks\n"
"\n"
"\\def\\flatlink#1#2#3#4#5{%\n"
"  \\setbox\\xxx=\\hbox{}\\wd\\xxx=#3bp\\ht\\xxx=#4bp%\n"
"  \\rlap{\\kern#1bp\\raise#2bp\\hbox{%\n"
"  \\vbox to0bp{\\vss\\hbox to 0bp{%\n"
"  \\pdfstartlink attr {/Border [0 0 0]} goto name {#5}%\n"
"  \\box\\xxx\\pdfendlink\\hss}}}}}%\n"
"\n"
"\\def\\textlink#1#2{%\n"
"  \\pdfstartlink attr {/Border [0 0 0]} goto name {#2}#1\\pdfendlink}%\n"
"\n"
"\n"
"\\def\\includechars#1:#2\\endinclude{\\pdfincludechars#1{#2}}\n"
"\n"
"\\newbox\\tmpboxa\n"
"\\newbox\\tmpboxb\n"
"\n"
"\\newdimen\\legendsymbolwd\n"
"\\newdimen\\legendsymbolht \\legendsymbolht=12pt\n"
"\\newdimen\\tmpdimen\n"
"\n"
"\\def\\legendsymbolbox#1#2{%\n"
"  \\setbox\\tmpboxa=\\hbox{\\pdfrefxform#1}%\n"
"  \\setbox\\tmpboxb=\\hbox{(}%\n"
"  \\legendsymbolwd=\\wd\\tmpboxa\n"
"  \\legendsymbolht=\\ht\\tmpboxa\n"
"  \\advance\\legendsymbolht by -\\ht\\tmpboxb\n"
"  \\advance\\legendsymbolht by -1dd\n"
"  \\tmpdimen=\\hsize\n"
"    \\advance\\tmpdimen by 10pt \n"
"    \\divide\\tmpdimen by\\legendcolumns \n"
"    \\advance\\tmpdimen by-10pt\n"
"  \\hbox to \\tmpdimen{%\n"
"     \\box\\tmpboxa\\kern10pt\\raise\\legendsymbolht\\vtop{%\n"
"       \\advance\\tmpdimen by -\\legendsymbolwd\n"
"       \\advance\\tmpdimen by -10pt\n"
"       \\hsize=\\tmpdimen\\rightskip=0pt plus \\tmpdimen minus 0pt\\relax#2\\vskip1dd}\\hss}%\n"
"}\n"
"\n"
"\\def\\colorlegendbox#1#2#3{%\n"
"  \\setbox\\xxx=\\hbox to 36bp{\\PL{q #1 #2 #3 rg 0 0 36 24 re f Q}\\hfil}%\n"
"  \\ht\\xxx=25bp\\dp\\xxx=0bp\n"
"  \\immediate\\pdfxform\\xxx\n"
"}\n"
"\n"
"\n"
"\\let\\PL\\pdfliteral\n"
"\n"
"\\newdimen\\xcorr\n"
"\\newdimen\\ycorr\n"
"\n"
"\\def\\PB#1#2#3{\\rlap{\\kern#1bp\\raise#2bp\\hbox{\\pdfrefxform#3}}} %placebox\n"
"\n"
"\\def\\PBcorr#1#2#3{%\n"
"  \\xcorr=#1bp\\advance\\xcorr by\\extraW\\advance\\xcorr by\\overlap%\n"
"  \\ycorr=#2bp\\advance\\ycorr by\\extraS\\advance\\ycorr by\\overlap%\n"
"  \\rlap{\\kern\\xcorr\\raise\\ycorr\\hbox{\\pdfrefxform#3}}} %placebox\n"
"\n"
"\\def\\bitmap#1#2#3#4#5#6#7{%\n"
"  \\pdfliteral{q #1 #2 #3 #4 #5 #6 cm}%\n"
"  \\rlap{\\pdfrefximage#7}%\n"
"  \\pdfliteral{Q}%\n"
"}\n"
"\n"
"\\def\\bitmapcorr#1#2#3#4#5#6#7{%\n"
"  \\xcorr=#5bp\\advance\\xcorr by\\extraW\\advance\\xcorr by\\overlap\n"
"  \\ycorr=#6bp\\advance\\ycorr by\\extraS\\advance\\ycorr by\\overlap\n"
"  \\dimtobp{\\xcorr}\\edef\\wdth{\\tmpdef}%\n"
"  \\dimtobp{\\ycorr}\\edef\\hght{\\tmpdef}%\n"
"  \\pdfliteral{q #1 #2 #3 #4 \\wdth\\space\\hght\\space cm}%\n"
"  \\rlap{\\pdfrefximage#7}%\n"
"  \\pdfliteral{Q}%\n"
"}\n"
"\n"
"\\def\\TITLE#1{\\eject\\hbox{}\\vskip5cm\\centerline{\\size[24]#1}\\vfil\\eject}\n"
"\n"
"% processing of the E-W-N-S references\n"
"\n"
"\\def\\showpointer#1{\\ifnum\\the#1=0\\else\\the#1\\fi}\n"
"\n"
"% processing of the up and down references\n"
"\n"
"\\def\\showpointerlist#1{\\edef\\test{\\the#1}\\ifx\\test\\notdef\\else\n"
"                   \\expandafter\\process\\the#1\\endarg\\fi}\n"
"\n"
"\\def\\process#1||#2\\endarg{\n"
"  \\expandafter\\processpointeritem#1\\endarg%\n"
"  \\if@#2@\\def\\next##1\\endarg{}\n"
"  \\else\\let\\next=\\process\\fi\n"
"  \\next#2\\endarg}\n"
"\n"
"\\def\\processpointeritem#1|#2|#3\\endarg{\\hbox{\\textlink{\\arr\\ #2 (#1)}{#3}}}\n"
"\n"
"\\def\\arr{}        % to be redefined in the \\dopage macro\n"
"\n"
"\n"
"\\def\\pagesetup#1#2#3#4#5#6{\n"
"  \\pdfpagewidth#1\n"
"  \\pdfpageheight#2\n"
"  \\hsize#3\n"
"  \\vsize#4\n"
"  \\pdfhorigin#5\n"
"  \\pdfvorigin#6\n"
"  \\hoffset0pt\n"
"  \\voffset0pt\\relax\n"
"}\n"
"\n"
"\\def\\linestyle{1 J 1 j 1.5 w}\n"
"\n"
"\\def\\framed#1{% \n"
"  \\dimtobp{\\wd#1}\\edef\\wdth{\\tmpdef}%\n"
"  \\dimtobp{\\ht#1}\\edef\\hght{\\tmpdef}%\n"
"  \\hbox to \\wd#1{\\rlap{\\box#1}\\PL{q \\linestyle\\space 0 0 \\wdth\\space\\hght\\space re S Q}\\hfill}%\n"
"}\n"
"\n"
"{\\catcode`\\p=12\\catcode`\\t=12\\gdef\\SKIPPT#1pt{#1}}\n"
"\n"
"\\def\\dimtobp#1{%\n"
"  \\tmpdimen=#1%\n"
"  \\tmpdimen=0.996264\\tmpdimen\n"
"  \\edef\\tmpdef{\\the\\tmpdimen}%\n"
"  \\edef\\tmpdef{\\expandafter\\SKIPPT\\tmpdef}%\n"
"}\n"
"\n"
"\\def\\color[#1 #2 #3]{%\n"
"  \\tmpdimen=#1pt%\n"
"  \\divide\\tmpdimen100\n"
"  \\edef\\tmpdef{\\the\\tmpdimen}%\n"
"  \\edef\\tmpdef{\\expandafter\\SKIPPT\\tmpdef}%\n"
"  \\pdfliteral{\\tmpdef}%\n"
"  \\tmpdimen=#2pt%\n"
"  \\divide\\tmpdimen100\n"
"  \\edef\\tmpdef{\\the\\tmpdimen}%\n"
"  \\edef\\tmpdef{\\expandafter\\SKIPPT\\tmpdef}%\n"
"  \\pdfliteral{\\tmpdef}%\n"
"  \\tmpdimen=#3pt%\n"
"  \\divide\\tmpdimen100\n"
"  \\edef\\tmpdef{\\the\\tmpdimen}%\n"
"  \\edef\\tmpdef{\\expandafter\\SKIPPT\\tmpdef}%\n"
"  \\pdfliteral{\\tmpdef}%\n"
"  \\pdfliteral{rg}\n"
"}\n"
"\n"
"% actual placing of the page elements\n"
"\n"
"\\def\\dopage{%\n"
" \\vbox{\\centerline{\\framed{\\mapbox}}\n"
"  \\bigskip\n"
"  \\line{%\n"
"    \\vbox to \\ht\\navbox{\n"
"      \\hbox{\\size[20]\\the\\pagelabel\n"
"        \\ifpagenumbering\\space(\\the\\pagenum)\\fi\n"
"        \\space\\size[16]\\the\\pagename}\n"
"      \\ifpagenumbering\n"
"        \\medskip\n"
"        \\hbox{\\qquad\\qquad\n"
"          \\vtop{%\n"
"            \\hbox to 0pt{\\hss\\showpointer\\pointerN\\hss}\n"
"            \\hbox to 0pt{\\llap{\\showpointer\\pointerW\\hskip0.7em}%\n"
"              \\raise1pt\\hbox to 0pt{\\hss$\\updownarrow$\\hss}%\n"
"              \\raise1pt\\hbox to 0pt{\\hss$\\leftrightarrow$\\hss}%\n"
"              \\rlap{\\hskip0.7em\\showpointer\\pointerE}}\n"
"              \\hbox to 0pt{\\hss\\showpointer\\pointerS\\hss}\n"
"          }\\qquad\\qquad\n"
"          \\vtop{\n"
"            \\def\\arr{$\\uparrow$}\n"
"            \\showpointerlist\\pointerU\n"
"            \\def\\arr{$\\downarrow$}\n"
"            \\showpointerlist\\pointerD\n"
"          }\n"
"        }\n"
"      \\fi\n"
"      \\vss\n"
"    }\\hss\\ifscalebar\\hbox to 0pt{\\hss\\scalebar\\qquad}\\fi\n"
"    \\box\\navbox\n"
"  }\n"
" }\n"
"}\n"
"\n"
"\\newif\\iflegend\n"
"\\newif\\ifcolorlegend\n"
"\\newtoks\\legendcontent\n"
"\n"
"\\newtoks\\cavename\n"
"\\newtoks\\comment\n"
"\\newtoks\\legendtitle\n"
"\\newtoks\\colorlegendtitle\n"
"\\newif\\ifnortharrow\n"
"\\newif\\ifscalebar\n"
"\\newtoks\\explotitle\n"
"\\newtoks\\explodate\n"
"\\newtoks\\exploteam\n"
"\\newtoks\\topotitle\n"
"\\newtoks\\topodate\n"
"\\newtoks\\topoteam\n"
"\\newtoks\\cartotitle\n"
"\\newtoks\\cartodate\n"
"\\newtoks\\cartoteam\n"
"\\newtoks\\copyrights\n"
"\\newtoks\\cavelength\n"
"\\newtoks\\cavedepth\n"
"\\newtoks\\cavelengthtitle\n"
"\\newtoks\\cavedepthtitle\n"
"\n"
"\\def\\scalebar{\\pdfrefxform\\THWscalebar}\n"
"\\def\\northarrow{\\pdfrefxform\\THWnortharrow}\n"
"\\newdimen\\legendwidth %\\legendwidth=14cm\n"
"\\newcount\\legendcolumns \\legendcolumns=2\n"
"\n"
"\\legendcontent={%\n"
"  \\hsize=\\legendwidth\n"
"  \\ifnortharrow\\vbox to 0pt{\\line{\\hfil\\northarrow}\\vss}\\fi\n"
"  \\edef\\tmp{\\the\\cavename} \\ifx\\tmp\\empty \\else\n"
"    \\color[0 0 0]{\\size[26]\\the\\cavename}\\color[0 0 0]\\vskip1cm\n"
"  \\fi\n"
"  \\ifscalebar\\scalebar\\vskip1cm\\fi\n"
"  {\\rightskip=0pt plus 3em\\parskip=3bp\n"
"    \\edef\\tmp{\\the\\comment} \\ifx\\tmp\\empty \\else\n"
"      {\\size[12]\\the\\comment} \\par\\medskip\n"
"    \\fi\n"
"    \\everypar{\\hangindent=2em\\hangafter=1}\n"
"    \\edef\\tmp{\\the\\cavelength} \\ifx\\tmp\\empty \\else\n"
"      {\\size[12]\\si\\the\\cavelengthtitle: \\ss\\the\\cavelength\\par}\n"
"    \\fi\n"
"    \\edef\\tmp{\\the\\cavedepth} \\ifx\\tmp\\empty \\else\n"
"      {\\size[12]\\si\\the\\cavedepthtitle: \\ss\\the\\cavedepth\\par}\n"
"    \\fi\n"
"    \\edef\\tmp{\\the\\exploteam} \\ifx\\tmp\\empty \\else\n"
"      {\\size[12]\\si\\the\\explotitle: \\ss\\the\\exploteam\\quad\\si\\the\\explodate\\par}\n"
"    \\fi\n"
"    \\edef\\tmp{\\the\\topoteam} \\ifx\\tmp\\empty \\else\n"
"      {\\size[12]\\si\\the\\topotitle: \\ss\\the\\topoteam\\quad\\si\\the\\topodate\\par}\n"
"    \\fi\n"
"    \\edef\\tmp{\\the\\cartoteam} \\ifx\\tmp\\empty \\else\n"
"      {\\size[12]\\si\\the\\cartotitle: \\ss\\the\\cartoteam\\quad\\si\\the\\cartodate\\par}\n"
"    \\fi\n"
"    \\edef\\tmp{\\the\\copyrights} \\ifx\\tmp\\empty \\else\n"
"      {\\size[12]\\ss\\the\\copyrights\\par}\n"
"    \\fi\n"
"  }\n"
"  \\formattedlegend\n"
"}\n"
"\n"
"\\def\\maplayout{\n"
"  \\legendbox{NW}{\\the\\legendcontent}\n"
"  \\legendbox{NE}{\\northarrow}\n"
"}\n"
"\n"
"\n"
"\\def\\formattedlegend{%\n"
"  \\ifcolorlegend\n"
"  \\vskip1cm{\\size[14]\\the\\colorlegendtitle}\\bigskip\n"
"  \\insertcolorlegend\n"
"  \\fi\n"
"  \\iflegend\n"
"  \\vskip1cm{\\size[14]\\the\\legendtitle}\\bigskip\n"
"  \\insertlegend\n"
"  \\fi}\n"
"\n"
"\\let\\atlaslegend=\\formattedlegend\n"
"\n"
"\\def\\atlastitlepages{\n"
"  \\edef\\tmp{\\the\\cavename} \\ifx\\tmp\\empty \\else\n"
"    \\TITLE{\\the\\cavename}\n"
"  \\fi\n"
"  {\\rightskip=0pt plus 3em\\parskip=3bp\n"
"    \\edef\\tmp{\\the\\comment} \\ifx\\tmp\\empty \\else\n"
"      {\\size[12]\\the\\comment} \\par\\medskip\n"
"    \\fi\n"
"    \\everypar{\\hangindent=2em\\hangafter=1}\n"
"    \\edef\\tmp{\\the\\exploteam} \\ifx\\tmp\\empty \\else\n"
"      {\\size[12]\\si\\the\\explotitle: \\ss\\the\\exploteam\\par}\n"
"    \\fi\n"
"    \\edef\\tmp{\\the\\topoteam} \\ifx\\tmp\\empty \\else\n"
"      {\\size[12]\\si\\the\\topotitle: \\ss\\the\\topoteam\\par}\n"
"    \\fi\n"
"    \\edef\\tmp{\\the\\cartoteam} \\ifx\\tmp\\empty \\else\n"
"      {\\size[12]\\si\\the\\cartotitle: \\ss\\the\\cartoteam\\par}\n"
"    \\fi\n"
"    \\edef\\tmp{\\the\\copyrights} \\ifx\\tmp\\empty \\else\n"
"      {\\size[12]\\ss\\the\\copyrights\\par}\n"
"    \\fi\n"
"  }\n"
"}\n"
"\n"
"\\newdimen\\sx\n"
"\\newdimen\\sy\n"
"\\newdimen\\sxd\n"
"\\newdimen\\syd\n"
"\n"
"\\def\\LEGN{N}\n"
"\\def\\LEGE{E}\n"
"\\def\\LEGW{W}\n"
"\\def\\LEGS{S}\n"
"\\def\\LEGNE{NE}\n"
"\\def\\LEGNW{NW}\n"
"\\def\\LEGSE{SE}\n"
"\\def\\LEGSW{SW}\n"
"\\def\\LEGC{C}\n"
"\n"
"\n"
"\\newdimen\\extraN \\extraN=0mm\n"
"\\newdimen\\extraS \\extraS=0mm\n"
"\\newdimen\\extraE \\extraE=0mm\n"
"\\newdimen\\extraW \\extraW=0mm\n"
"\\newdimen\\adjustedHS\n"
"\\newdimen\\adjustedVS\n"
"\\newdimen\\adjustedX\n"
"\\newdimen\\adjustedY\n"
"\n"
"\n"
"\\def\\legendbox#1#2#3#4{%\n"
"  \\unskip\n"
"  \\setbox\\tmpboxa=\\vbox{#4}%\n"
"  \\sx=\\wd\\tmpboxa\n"
"  \\sy=\\ht\\tmpboxa \\advance\\sy by \\dp\\tmpboxa\n"
"  \\sxd=\\hsize \\divide\\sxd by 100 \\multiply\\sxd by #1\n"
"  \\syd=\\vsize \\divide\\syd by 100 \\multiply\\syd by #2\n"
"  \\edef\\test{#3}%\n"
"  \\ifx\\test\\LEGN\n"
"    \\divide\\sx by 2 \\advance\\sxd by -\\sx\n"
"                    \\advance\\syd by -\\sy\n"
"  \\else\\ifx\\test\\LEGW\n"
"    \\divide\\sy by 2 \\advance\\syd by -\\sy \n"
"  \\else\\ifx\\test\\LEGE\n"
"                    \\advance\\sxd by -\\sx\n"
"    \\divide\\sy by 2 \\advance\\syd by -\\sy \n"
"  \\else\\ifx\\test\\LEGS\n"
"    \\divide\\sx by 2 \\advance\\sxd by -\\sx\n"
"  \\else\\ifx\\test\\LEGNW\n"
"                    \\advance\\syd by -\\sy \n"
"  \\else\\ifx\\test\\LEGNE\n"
"                    \\advance\\sxd by -\\sx\n"
"                    \\advance\\syd by -\\sy\n"
"  \\else\\ifx\\test\\LEGSW\n"
"  \\else\\ifx\\test\\LEGSE\n"
"                    \\advance\\sxd by -\\sx\n"
"  \\else\\ifx\\test\\LEGC\n"
"    \\divide\\sx by 2 \\advance\\sxd by -\\sx\n"
"    \\divide\\sy by 2 \\advance\\syd by -\\sy \n"
"  \\fi\\fi\\fi\\fi\\fi\\fi\\fi\\fi\\fi\n"
"  %\n"
"  \\ifdim\\sxd<-\\extraW \\global\\extraW=-\\sxd\\fi\n"
"  \\ifdim\\syd<-\\extraS \\global\\extraS=-\\syd\\fi\n"
"  \\sx=\\wd\\tmpboxa\n"
"  \\sy=\\ht\\tmpboxa \\advance\\sy by \\dp\\tmpboxa\n"
"  \\advance\\sx by \\sxd\n"
"  \\advance\\sy by \\syd\n"
"  \\ifdim\\sx>\\hsize \\global\\extraE=\\sx \\global\\advance\\extraE by -\\hsize\\fi\n"
"  \\ifdim\\sy>\\vsize \\global\\extraN=\\sy \\global\\advance\\extraN by -\\vsize\\fi\n"
"  %\n"
"  \\unskip\n"
"  \\advance\\sxd by \\extraW\n"
"  \\advance\\syd by \\extraS\n"
"\n"
"  % vypln pod legendou\n"
"  \\iflegendbgfill\n"
"    \\dimtobp{\\sxd}\\edef\\shiftx{\\tmpdef}%\n"
"    \\dimtobp{\\syd}\\edef\\shifty{\\tmpdef}%\n"
"    \\dimtobp{\\wd\\tmpboxa}\\edef\\wdth{\\tmpdef}%\n"
"    \\sy=\\ht\\tmpboxa \\advance\\sy by \\dp\\tmpboxa\n"
"    \\dimtobp{\\sy}\\edef\\hght{\\tmpdef}%\n"
"    \\rlap{\\PL{q \\the\\bgcolor\\space rg \\shiftx\\space \\shifty\\space \\wdth\\space \\hght\\space re f Q}}%\n"
"  \\fi\n"
"  %\n"
"  \\advance\\syd by \\dp\\tmpboxa\n"
"\n"
"  \\rlap{\\kern\\sxd\\raise\\syd\\box\\tmpboxa}%\n"
"  \\ignorespaces\n"
"}\n"
"\n"
"\n"
"\\def\\insertmaps{%\n"
"  \\color[0 0 0]\n"
"  \\input th_formdef\n"
"  \\input th_pagedef\n"
"  \\input th_pages\n"
"  \\immediate\\write-1{ \\the\\count10 \\space numeric registers used out of \n"
"            \\ifx\\eTeXversion\\undefined256\\else32768\\fi}\n"
"}\n"
"    \n"
"\\def\\insertlegend{%\n"
"  \\input th_legend\n"
"}\n"
"\n"
"\\def\\insertcolorlegend{%\n"
"  \\input th_legendcolor\n"
"}\n"
"\n"
"\\newcount\\stopcount\n"
"\\newcount\\stoprow\n"
"\\newcount\\rows\n"
"\\newcount\\rowstmp\n"
"\\newcount\\i\n"
"\\newcount\\j\n"
"\n"
"\n"
"\\def\\placemaps{\n"
"  \\message{ [Warning: \\string\\placemaps\\space is deprecated; \n"
"            use \\string\\insertmaps] }\n"
"  \\insertmaps\n"
"}\n"
"\n"
"%% Petr Olsak's multicolumn macros (slightly modified)\n"
"\n"
"\\newdimen\\colsep  \\colsep=1em % horiz. mezera mezi sloupci\n"
"\\newcount\\tempnum             % pracovn� prom�nn�\n"
"\\splittopskip=\\baselineskip\n"
"\\def\\roundtolines #1{%% zaokrouhl� na cel� n�sobky vel. ��dku\n"
"   \\divide #1 by\\baselineskip \\multiply #1 by\\baselineskip}\n"
"\\def\\corrsize #1{%% #1 := #1 + \\splittopskip - \\topskip\n"
"   \\advance #1 by \\splittopskip \\advance #1 by-\\topskip}\n"
"\n"
"\\def\\begmulti#1{\\par\\bigskip\\penalty0 \\def\\Ncols{#1}\n"
"   \\setbox0=\\vbox\\bgroup\\penalty0\n"
"   %% \\hsize := ���ka sloupce = (\\hsize+\\colsep) / n - \\colsep\n"
"   \\advance\\hsize by\\colsep\n"
"   \\divide\\hsize by\\Ncols  \\advance\\hsize by-\\colsep}\n"
"\\def\\endmulti{\\vfil\\egroup \\setbox1=\\vsplit0 to0pt\n"
"   %% \\dimen1 := velikost zbyl�ho m�sta na str�nce\n"
"   \\ifdim\\pagegoal=\\maxdimen \\dimen1=\\vsize \\corrsize{\\dimen1}\n"
"   \\else \\dimen1=\\pagegoal \\advance\\dimen1 by-\\pagetotal \\fi\n"
"   \\ifdim \\dimen1<2\\baselineskip\n"
"     \\vfil\\break \\dimen1=\\vsize \\corrsize{\\dimen1} \\fi\n"
"   %% \\dimen0 := v��ka n sloupcov� sazby po rozd�len� do sloupc�\n"
"   %% = (\\ht0 + (n-1)\\baselineskip) / n, zaokruhleno na ��dky\n"
"   \\dimen0=\\Ncols\\baselineskip \\advance\\dimen0 by-\\baselineskip\n"
"   \\advance\\dimen0 by \\ht0 \\divide\\dimen0 by\\Ncols\n"
"   \\roundtolines{\\dimen0}\n"
"   %% Rozd�lit sazbu n sloupc� do str�nek nebo nerozd�lit ?\n"
"   \\ifdim \\dimen0>\\dimen1 \\splitpart\n"
"   \\else \\makecolumns{\\dimen0} \\fi\n"
"   \\ifvoid0 \\else \\errmessage{Lost text in multiple columns?} \\fi\n"
"   \\bigskip}\n"
"\\def\\makecolumns#1{\\setbox1=\\hbox{}\\tempnum=0\n"
"   \\loop \\ifnum\\Ncols>\\tempnum\n"
"      \\setbox1=\\hbox{\\unhbox1 \\vsplit0 to#1 \\hss}\n"
"      \\advance\\tempnum by1\n"
"   \\repeat\n"
"   \\hbox{}\\nobreak\\vskip-\\splittopskip \\nointerlineskip\n"
"   \\line{\\unhbox1\\unskip}}\n"
"\\def\\splitpart{\\roundtolines{\\dimen1}\n"
"   \\makecolumns{\\dimen1} \\advance\\dimen0 by-\\dimen1\n"
"   %% \\dimen0 := v��ka _zbyl�_ n sloupcov� sazby\n"
"   %% \\dimen1 := pr�zdn� m�sto na str�nce = (cca) \\vsize\n"
"   \\vfil\\break\n"
"   \\dimen1=\\vsize \\corrsize{\\dimen1}\n"
"   %% Rozd�lit zbylou sazbu n sloupc� do v�ce str�nek ?\n"
"   \\ifvoid0 \\else\n"
"      \\ifdim \\dimen0>\\dimen1 \\splitpart\n"
"      \\else \\makecolumns{\\dimen0} \\fi \\fi}\n"
"\n"
"%% end of multicolumn macros\n"
"\n"
"\\input th_enc\n"
"\\input th_texts\n"
"\\input th_resources\n"
"\\input th_fontdef\n"
"\n"
"\\nonstopmode\n"
"\n";
 

#endif
