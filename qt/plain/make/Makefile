OGCALC_MOC_HEADERS = $(shell egrep -l "[[:space:]]*((public|protected|private)[[:space:]]+)?signals|slots:" *.h)
OGCALC_MOC_SOURCES = $(addprefix moc_,$(addsuffix .cpp,$(basename $(OGCALC_MOC_HEADERS))))

QT_CXXFLAGS += $(shell pkg-config --cflags Qt5Core Qt5Gui Qt5Widgets Qt5Svg)
QT_LIBS += $(shell pkg-config --libs Qt5Core Qt5Gui Qt5Widgets Qt5Svg)

OGCALC_SOURCES = 		\
	main.cpp		\
	ogcalc.cpp 		\
	SpinBoxEntry.cpp

OGCALC_OBJECTS = $(addsuffix .o,$(basename $(OGCALC_SOURCES) $(OGCALC_MOC_SOURCES)))

OGCALC_CXXFLAGS = $(CXXFLAGS) $(QT_CXXFLAGS) -fPIC
OGCALC_LIBS = $(QT_LIBS)

all: ogcalc

moc_%.cpp: %.h
	moc $< -o $@

%.o: %.cpp
	$(CXX) $(OGCALC_CXXFLAGS) -o $@ -c $<

ogcalc: $(OGCALC_MOC_SOURCES) $(OGCALC_OBJECTS)
	$(CXX) -o $@ $(OGCALC_OBJECTS) $(OGCALC_LIBS)

clean:
	rm -f $(OGCALC_MOC_SOURCES) $(OGCALC_OBJECTS) ogcalc

distclean: clean

maintainerclean: distclean

.PHONY: default clean distclean maintainerclean
