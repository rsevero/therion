OUTDIR ?= .
THPLATFORM ?= LINUX
ifneq ($(OUTDIR),.)
LOUTDIR = $(OUTDIR)/loch
else
LOUTDIR = .
endif



# common therion objects
CMNOBJECTS = \
  lxTR.o lxOGLFT.o lxSetup.o lxRender.o lxWX.o \
  lxImgIO.o lxLRUD.o lxFile.o lxSTree.o \
  lxData.o lxMath.o lxSView.o lxSScene.o \
  lxGUI.o lxGLC.o lxOptDlg.o lxAboutDlg.o lxPres.o \
  img.o

CROSS =
EXT =

WX_CONFIG = wx-config

VTKSUFFIX = $(shell tclsh ./getvtkver.tcl suffix)
VTKVERSION = $(shell tclsh ./getvtkver.tcl version)
VTKPATH = $(shell tclsh ./getvtkver.tcl incpath)
VTKLIBPATH = $(shell tclsh ./getvtkver.tcl libpath)
VTKV6 = $(shell tclsh ./getvtkver.tcl version6)
ifeq ($(VTKV6),1)
VTKLIBS = \
    -lvtkCommonExecutionModel$(VTKSUFFIX) \
    -lvtkCommonDataModel$(VTKSUFFIX) \
    -lvtkCommonCore$(VTKSUFFIX) \
    -lvtkFiltersCore$(VTKSUFFIX) \
    -lvtkFiltersHybrid$(VTKSUFFIX) \
    -lvtkIOLegacy$(VTKSUFFIX) \
    $(shell pkg-config --libs freetype2) \
    -lpng -ljpeg
else
VTKLIBS = -lvtkHybrid -lvtkImaging -lvtkIO -lvtkGraphics -lvtkFiltering -lvtkCommon -lvtkjpeg -lvtkpng -lvtkzlib -lvtksys -lfreetype
endif
# VTKVERSION = 5.4
# VTKPATH = /usr/local/include/vtk-$(VTKVERSION)
# VTKLIBPATH = /usr/local/lib/vtk-$(VTKVERSION)
POSTMAKE =
STRIPFLAG = -s

# PLATFORM CONFIG

# PLATFORM LINUX
##CXX = c++
##CC = gcc
##POBJECTS = lxR2P.o
##ifeq ($(VTKV6),1)
##VTKLIBS = -lvtkCommonExecutionModel-$(VTKVERSION) -lvtkCommonDataModel-$(VTKVERSION) -lvtkCommonCore-$(VTKVERSION) -lvtkFiltersCore-$(VTKVERSION) -lvtkFiltersHybrid-$(VTKVERSION) -lvtkIOLegacy-$(VTKVERSION) -lfreetype -lpng -ljpeg
##else
##VTKLIBS = -lvtkHybrid -lvtkImaging -lvtkIO -lvtkGraphics -lvtkFiltering -lvtkCommon -lfreetype
##endif
##CXXPFLAGS = -DLXLINUX -std=c++11 $(shell wx-config --cxxflags) -Wno-deprecated $(shell pkg-config freetype2 --cflags) -I$(VTKPATH)
##CCPFLAGS = -DLXLINUX  $(shell wx-config --cflags)
##LXLIBDIR = linux
##PLIBS = $(shell wx-config --libs --gl-libs) -L$(VTKLIBPATH) $(VTKLIBS) -lGLU -lGL -lpthread -lX11 -lz
##LXPLATFORM = LINUX

# PLATFORM DEBIAN
CXX = c++
CC = gcc
ifeq ($(VTKV6),1)
else
VTKLIBS = -lvtkHybrid -lvtkImaging -lvtkIO -lvtkGraphics -lvtkFiltering -lvtkCommon -lfreetype
endif
CXXPFLAGS = \
    -std=c++11 \
    -Wno-deprecated \
    $(shell $(WX_CONFIG) --cxxflags) \
    $(shell pkg-config freetype2 --cflags) \
    -I$(VTKPATH)
CCPFLAGS = $(shell $(WX_CONFIG) --cflags)
LXLIBDIR = linux
PLIBS = $(shell wx-config --libs --gl-libs) -L$(VTKLIBPATH) $(VTKLIBS) -lGLU -lGL -lpthread -lX11 -lz
LXPLATFORM = LINUX

# LXLINUX doesn't work with Arch Linux
ifneq ($(shell lsb_release -si),Arch)
  POBJECTS = lxR2P.o
  CXXPFLAGS += -DLXLINUX
  CCPFLAGS += -DLXLINUX
endif

# PLATFORM WIN32
##CXX = c++
##CC = gcc
##POBJECTS = loch.res lxR2D.o getline.o
##CXXPFLAGS = -W -Wall -DLXWIN32 $(shell wx-config --static --cxxflags) $(shell pkg-config freetype2 --cflags) -I$(VTKPATH) -Wno-deprecated
##CCPFLAGS = -W -Wall -DLXWIN32 $(shell wx-config --static --cflags)
##LXLIBDIR = mingw
##PLIBS = $(shell pkg-config freetype2 --libs) $(shell wx-config --static --libs --gl-libs) -L$(VTKLIBPATH) $(VTKLIBS)
##LXPLATFORM = WIN32
##STRIPFLAG = -static-libgcc -static -s

# PLATFORM WIN32CROSS
##CROSS= i686-w64-mingw32.static-
##EXT = .exe
##VTKVERSION = 8.2
##VTKPATH = /usr/lib/mxe/usr/i686-w64-mingw32.static/include/vtk-$(VTKVERSION)
##VTKLIBPATH = /usr/lib/mxe/usr/i686-w64-mingw32.static/lib
##VTKLIBS = -lvtkCommonExecutionModel-$(VTKVERSION) -lvtkCommonDataModel-$(VTKVERSION) \
##  -lvtkFiltersCore-$(VTKVERSION) -lvtkFiltersHybrid-$(VTKVERSION) \
##  -lvtkIOLegacy-$(VTKVERSION) -lvtkCommonCore-$(VTKVERSION) -lvtkIOCore-$(VTKVERSION) \
##  -lvtkCommonTransforms-$(VTKVERSION) -lvtkCommonMisc-$(VTKVERSION) -lvtkCommonMath-$(VTKVERSION) -lvtkCommonSystem-$(VTKVERSION) \
##  -lvtksys-$(VTKVERSION) -lvtkfreetype-$(VTKVERSION) -lvtkpng-$(VTKVERSION) -lvtkjpeg-$(VTKVERSION) -lvtkzlib-$(VTKVERSION)
##CXX = $(CROSS)c++
##CC = $(CROSS)gcc
##POBJECTS = loch.res lxR2D.o getline.o
##CXXPFLAGS = -W -Wall -std=gnu++11 -DLXWIN32 $(shell $(CROSS)wx-config --static --cxxflags) $(shell $(CROSS)pkg-config freetype2 --cflags) -I$(VTKPATH) -Wno-deprecated
##CCPFLAGS = -W -Wall -DLXWIN32 $(shell $(CROSS)wx-config --static --cflags)
##LXLIBDIR =
##PLIBS = $(shell $(CROSS)pkg-config freetype2 --libs) $(shell $(CROSS)wx-config --static --libs --gl-libs) -L$(VTKLIBPATH) $(VTKLIBS)
##LXPLATFORM = WIN32
##STRIPFLAG = -static-libgcc -static -s

# PLATFORM MACOSX
##CXX = c++
##CC = cc
##POBJECTS =
##CXXPFLAGS = -W -Wall -std=c++11 -DLXMACOSX $(shell wx-config --cxxflags) $(shell pkg-config freetype2 --cflags) -I$(VTKPATH) -Wno-deprecated -I/usr/X11R6/include -I/usr/X11R6/include/freetype2
##CCPFLAGS = -W -Wall -DLXMACOSX $(shell wx-config --cflags) -I/usr/X11R6/include
##LXLIBDIR =
##PLIBS = -lz -L/usr/X11R6/lib $(shell wx-config --libs --gl-libs) -L$(VTKLIBPATH) $(VTKLIBS)
##LOCHAPPBINDIR := $(shell mkdir -p ./loch.app/Contents/MacOS)
##POSTMAKE = cp -f ./loch ./loch.app/Contents/MacOS/loch
##STRIPFLAG =

# PLATFORM ENDCONFIG


# BUILD CONFIG

# BUILD OZONE
##CCBFLAGS = -O3
##CXXBFLAGS = -O3
##LDBFLAGS = $(STRIPFLAG)

# BUILD OXYGEN
CCBFLAGS = -O2
CXXBFLAGS = -O2
LDBFLAGS = $(STRIPFLAG)

# BUILD RELEASE
##CCBFLAGS =
##CXXBFLAGS =
##LDBFLAGS = $(STRIPFLAG)

# BUILD DEBUG
##CCBFLAGS = -ggdb
##CXXBFLAGS = -ggdb -DLXDEBUG
##LDBFLAGS =

# BUILD ENDCONFIG


# compiler settings
CXXFLAGS := -Wall -D_GNU_SOURCE -DLOCH $(CXXPFLAGS) $(CXXBFLAGS)
CCFLAGS := -Wall -D_GNU_SOURCE -DLOCH $(CCPFLAGS) $(CCBFLAGS)
OBJECTS = $(addprefix $(LOUTDIR)/,$(POBJECTS)) $(addprefix $(LOUTDIR)/,$(CMNOBJECTS))


# linker settings
LIBS = $(PLIBS)
LDFLAGS = $(LDBFLAGS)


$(LOUTDIR)/%.o : %.cxx
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(LOUTDIR)/%.o : %.cc
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(LOUTDIR)/%.o : %.c
	$(CC) -c $(CCFLAGS) -o $@ $<


all: $(LOUTDIR)/loch hlp

hlp:
	$(MAKE) -C ./help

$(LOUTDIR)/loch: $(OBJECTS)
	$(CXX) -o $(LOUTDIR)/loch$(EXT) -Wall $(OBJECTS) $(LIBS) $(LDFLAGS)
	$(POSTMAKE)

$(LOUTDIR)/loch.res: loch.rc loch.ico
	$(CROSS)windres -i loch.rc $(shell $(CROSS)wx-config --cflags | tr ' ' '\n' | grep "^-I" | tr '\n' ' ') -J rc -o $(LOUTDIR)/loch.res -O coff

graphs:
	dot -Tps graph-vispipe.dot -o graph-vispipe.ps


depend:
	perl makedepend.pl > Makefile.dep
	perl maketest.pl Makefile.dep
	perl makefile.pl mv Makefile.dep Makefile
	$(CXX) -DLXDEPCHECK -DLOCH -D'wxCHECK_VERSION(X,Y,Z)=1' -MM *.cxx >> Makefile
	$(CC) -DLXDEPCHECK -DLOCH -MM *.c >> Makefile
	perl makedepend2.pl


config-debug:
	perl makeconfig.pl BUILD DEBUG

test-release:
	zip -9 loch.zip loch.exe test.th test.jpg thconfig

config-release:
	perl makeconfig.pl BUILD RELEASE

config-oxygen:
	perl makeconfig.pl BUILD OXYGEN

config-ozone:
	perl makeconfig.pl BUILD OZONE

config-linux:
	perl makeconfig.pl PLATFORM LINUX

config-debian:
	perl makeconfig.pl PLATFORM DEBIAN

config-win32:
	perl makeconfig.pl PLATFORM WIN32

config-win32cross:
	perl makeconfig.pl PLATFORM WIN32CROSS

config-macosx:
	perl makeconfig.pl PLATFORM MACOSX

clean:
	perl makefile.pl rm -q *~
	perl makefile.pl rm -q help/*/*~
	perl makefile.pl rm -q loch.exe
	perl makefile.pl rm -q loch
	perl makefile.pl rm -q loch.app/Contents/MacOS/loch
	perl makefile.pl rm -q *.o
	perl makefile.pl rm -q *.log
	perl makefile.pl rm -q core
	perl makefile.pl rmdir -q .xvpics
	perl makefile.pl rm -q *.bmp
	perl makefile.pl rm -q *.ppm
	perl makefile.pl rm -q *.zip
	perl makefile.pl rm -q *.pdf
	perl makefile.pl rm -q *.png
#	$(MAKE) -C help clean



# DEPENDENCIES
$(LOUTDIR)/lxAboutDlg.o: lxAboutDlg.cxx lxWX.h icons/about.xpm ../thversion.h
$(LOUTDIR)/lxData.o: lxData.cxx lxData.h lxMath.h lxImgIO.h lxFile.h lxLRUD.h
$(LOUTDIR)/lxFile.o: lxFile.cxx lxFile.h lxMath.h img.h ../extern/img.h
$(LOUTDIR)/lxGLC.o: lxGLC.cxx lxGLC.h lxMath.h lxGUI.h lxData.h lxImgIO.h lxFile.h \
 lxSetup.h lxSView.h lxWX.h lxFNT6x13_bdf.h lxFNT10x20_bdf.h \
 lxFNTFreeSans_ttf.h lxRender.h lxTR.h
$(LOUTDIR)/lxGUI.o: lxGUI.cxx lxGUI.h lxGLC.h lxMath.h lxData.h lxImgIO.h lxFile.h \
 lxSetup.h lxRender.h lxOptDlg.h lxAboutDlg.h lxSView.h lxWX.h lxSScene.h \
 lxSTree.h lxPres.h icons/open.xpm icons/render.xpm icons/reload.xpm \
 icons/stereo.xpm icons/rotation.xpm icons/lockrot.xpm icons/fit.xpm \
 icons/home.xpm icons/rendersetup.xpm icons/plan.xpm icons/profile.xpm \
 icons/fullscreen.xpm icons/orto.xpm icons/camera.xpm icons/scene.xpm \
 icons/viscline.xpm icons/vissurface.xpm icons/visbbox.xpm \
 icons/viswalls.xpm icons/visinds.xpm icons/visentrance.xpm \
 icons/visfix.xpm icons/visstation.xpm icons/vislabel.xpm loch.xpm
$(LOUTDIR)/lxImgIO.o: lxImgIO.cxx lxImgIO.h
$(LOUTDIR)/lxLRUD.o: lxLRUD.cxx lxLRUD.h lxMath.h
$(LOUTDIR)/lxMath.o: lxMath.cxx lxMath.h
$(LOUTDIR)/lxOGLFT.o: lxOGLFT.cxx lxOGLFT.h
$(LOUTDIR)/lxOptDlg.o: lxOptDlg.cxx lxWX.h lxGUI.h lxGLC.h lxMath.h
$(LOUTDIR)/lxPres.o: lxPres.cxx lxPres.h lxWX.h lxGUI.h lxGLC.h lxMath.h lxSetup.h \
 lxData.h lxImgIO.h lxFile.h loch.xpm
$(LOUTDIR)/lxRender.o: lxRender.cxx lxRender.h lxWX.h lxGLC.h lxMath.h lxGUI.h \
 lxSetup.h lxData.h lxImgIO.h lxFile.h lxTR.h
$(LOUTDIR)/lxSScene.o: lxSScene.cxx lxSScene.h lxWX.h lxGUI.h lxGLC.h lxMath.h \
 lxSetup.h lxData.h lxImgIO.h lxFile.h loch.xpm
$(LOUTDIR)/lxSTree.o: lxSTree.cxx lxSTree.h lxWX.h lxGUI.h lxGLC.h lxMath.h \
 lxSetup.h lxData.h lxImgIO.h lxFile.h loch.xpm
$(LOUTDIR)/lxSView.o: lxSView.cxx lxSView.h lxWX.h lxGUI.h lxGLC.h lxMath.h \
 lxSetup.h lxData.h lxImgIO.h lxFile.h loch.xpm
$(LOUTDIR)/lxSetup.o: lxSetup.cxx lxSetup.h lxData.h lxMath.h lxImgIO.h lxFile.h
$(LOUTDIR)/lxWX.o: lxWX.cxx lxWX.h
$(LOUTDIR)/getline.o: getline.c
$(LOUTDIR)/img.o: img.c ../extern/img.c ../extern/img.h
$(LOUTDIR)/lxR2D.o: lxR2D.c lxR2D.h
$(LOUTDIR)/lxR2P.o: lxR2P.c lxR2P.h
$(LOUTDIR)/lxTR.o: lxTR.c lxTR.h
