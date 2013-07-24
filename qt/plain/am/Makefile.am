OGCALC_MOC_H = $(shell egrep -l "[[:space:]]*((public|protected|private)[[:space:]]+)?signals|slots:" *.h)
OGCALC_MOC_SRC = $(addprefix moc_,$(addsuffix .cpp,$(basename $(OGCALC_MOC_H))))

BUILT_SOURCES = moc.cpp

moc.cpp: $(OGCALC_MOC_SRC)
	cat $^ > $@

bin_PROGRAMS = ogcalc

ogcalc_SOURCES =		\
	main.cpp		\
	ogcalc.h		\
	ogcalc.cpp		\
	SpinBoxEntry.cpp
nodist_ogcalc_SOURCES = moc.cpp
ogcalc_CXXFLAGS = $(CXXFLAGS) $(QT_CFLAGS) -fPIC
ogcalc_LDADD = $(QT_LIBS)

moc_%.cpp: %.h
	moc $< -o $@

CLEANFILES = $(OGCALC_MOC_SOURCES) $(BUILT_SOURCES)
