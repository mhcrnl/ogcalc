AUTOMAKE_OPTIONS = foreign

OGCALC_MOC_H = $(shell egrep -l "[[:space:]]*((public|protected|private)[[:space:]]+)?signals|slots:" $(srcdir)/*.h)
OGCALC_MOC_SRC = $(addsuffix .moc.cpp,$(basename $(OGCALC_MOC_H)))

BUILT_SOURCES = moc.cpp

moc.cpp: $(OGCALC_MOC_SRC)
	cat $^ > $@

bin_PROGRAMS = ogcalc

ogcalc_SOURCES =		\
	main.cpp		\
	ogcalc.h		\
	ogcalc.cpp		\
	SpinBoxEntry.h		\
	SpinBoxEntry.cpp
nodist_ogcalc_SOURCES = moc.cpp
ogcalc_CXXFLAGS = $(CXXFLAGS) $(QT_CFLAGS) -fPIC
ogcalc_LDADD = $(QT_LIBS)

%.moc.cpp: %.h
	moc $< -o $@

CLEANFILES = $(OGCALC_MOC_SRC) $(BUILT_SOURCES)
