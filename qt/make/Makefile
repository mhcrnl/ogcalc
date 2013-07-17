OGCALC_MOC_HEADERS = $(shell egrep -l "[[:space:]]*((public|protected|private)[[:space:]]+)?signals|slots:" *.h)
OGCALC_MOC_SOURCES = $(addprefix moc_,$(addsuffix .cpp,$(basename $(OGCALC_MOC_HEADERS))))

OGCALC_UI_DEFS = $(wildcard *.ui)
OGCALC_UI_SOURCES = $(addprefix ui_,$(addsuffix .h,$(basename $(OGCALC_UI_DEFS))))

QT_CXXFLAGS += $(shell pkg-config --cflags Qt5Core Qt5Gui Qt5Widgets)
QT_LIBS += $(shell pkg-config --libs Qt5Core Qt5Gui Qt5Widgets)

OGCALC_SOURCES = 		\
	main.cpp		\
	ogcalc.cpp 		\
	SpinBoxEntry.cpp

OGCALC_OBJECTS = $(addsuffix .o,$(basename $(OGCALC_SOURCES) $(OGCALC_MOC_SOURCES)))

OGCALC_CXXFLAGS = $(CXXFLAGS) $(QT_CXXFLAGS) -fPIC
OGCALC_LIBS = $(QT_LIBS)

default:
	echo $(OGCALC_MOC_HEADERS)
	echo $(OGCALC_MOC_SOURCES)
	echo $(OGCALC_UI_DEFS)
	echo $(OGCALC_UI_SOURCES)
	echo $(OGCALC_CXXFLAGS)
	echo $(OGCALC_LIBS)

moc_%.cpp: %.h
	moc $< -o $@

ui_%.h: %.ui
	uic $< -o $@

%.o: %.cpp
	$(CXX) $(OGCALC_CXXFLAGS) -o $@ -c $<

ogcalc: $(OGCALC_MOC_SOURCES) $(OGCALC_UI_SOURCES) $(OGCALC_OBJECTS)
	$(CXX) -o $@ $(OGCALC_OBJECTS) $(OGCALC_LIBS)

clean:
	rm -f $(OGCALC_MOC_SOURCES) $(OGCALC_UI_SOURCES) $(OGCALC_OBJECTS) ogcalc
