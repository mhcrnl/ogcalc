OGCALC_MOC_HEADERS = $(wildcard *.h)
OGCALC_MOC_SOURCES = $(addprefix moc_,$(addsuffix .cpp,$(basename $(OGCALC_MOC_HEADERS))))

ifeq ($(OS),Windows_NT)
  QT_DIR ?= C:\Qt\\5.1.0\mingw48_32
  QT_CXXFLAGS = -fno-keep-inline-dllexport -O2 -frtti -Wall -Wextra -fexceptions -mthreads -DUNICODE -DQT_NO_DEBUG -I"$(QT_DIR)\include"
  QT_LDFLAGS = -Wl,-s -Wl,-subsystem,windows -mthreads
  QT_LIBS = -lglu32 -lopengl32 -lgdi32 -luser32 -lmingw32 -lqtmain -L$(QT_DIR)\lib -lQt5Svg -lQt5Widgets -lQt5Gui -lQt5Core
  OGCALC_RES = res.o
  EXEEXT=.exe
else
  QT_CXXFLAGS += $(shell pkg-config --cflags Qt5Core Qt5Gui Qt5Widgets Qt5Svg) -fPIC
  QT_LIBS += $(shell pkg-config --libs Qt5Core Qt5Gui Qt5Widgets Qt5Svg)
endif

all: ogcalc$(EXEEXT)

OGCALC_SOURCES = 		\
	main.cpp		\
	ogcalc.cpp 		\
	SpinBoxEntry.cpp

OGCALC_OBJECTS = $(addsuffix .o,$(basename $(OGCALC_SOURCES) $(OGCALC_MOC_SOURCES))) $(OGCALC_RES)

OGCALC_CXXFLAGS = $(CXXFLAGS) $(QT_CXXFLAGS)
OGCALC_LIBS = $(QT_LIBS)

moc_%.cpp: %.h
	moc $< -o $@

%.o: %.cpp
	$(CXX) $(OGCALC_CXXFLAGS) -o $@ -c $<

res.o: ogcalc.rc
	windres -I . -i $< -o $@

ogcalc$(EXEEXT): $(OGCALC_MOC_SOURCES) $(OGCALC_OBJECTS)
	$(CXX) -o $@ $(OGCALC_OBJECTS) $(OGCALC_LIBS)

clean:
	$(RM) $(OGCALC_MOC_SOURCES) $(OGCALC_OBJECTS) $(OGCALC_RES) ogcalc$(EXEEXT)

distclean: clean

maintainerclean: distclean

.PHONY: default clean distclean maintainerclean
