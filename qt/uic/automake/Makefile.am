OGCALC_MOC_H = $(shell egrep -l "[[:space:]]*((public|protected|private)[[:space:]]+)?signals|slots:" $(srcdir)/*.h)
OGCALC_MOC_SRC = $(addsuffix .moc.cpp,$(basename $(OGCALC_MOC_H)))

OGCALC_UI_DEFS = $(wildcard $(srcdir)/*.ui)
OGCALC_UI_SRC = $(addprefix ui_,$(addsuffix .h,$(basename $(OGCALC_UI_DEFS))))

BUILT_SOURCES = moc.cpp $(OGCALC_UI_SRC)

moc.cpp: $(OGCALC_MOC_SRC)
	cat $^ > $@

bin_PROGRAMS = ogcalc

ogcalc_SOURCES =		\
	main.cpp		\
	ogcalc.h		\
	ogcalc.cpp		\
	SpinBoxEntry.h		\
	SpinBoxEntry.cpp
nodist_ogcalc_SOURCES = moc.cpp $(OGCALC_UI_SRC)
ogcalc_CXXFLAGS = $(CXXFLAGS) $(QT_CFLAGS) -fPIC
ogcalc_LDADD = $(QT_LIBS)

%.moc.cpp: %.h
	moc $< -o $@

ui_%.h: %.ui
	uic $< -o $@

CLEANFILES = $(OGCALC_MOC_SRC) $(OGCALC_UI_SRC) $(BUILT_SOURCES)
