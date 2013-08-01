OGCALC_MOC_H = $(shell egrep -l "[[:space:]]*((public|protected|private)[[:space:]]+)?signals|slots:" *.h)
OGCALC_MOC_SRC = $(addprefix moc_,$(addsuffix .cpp,$(basename $(OGCALC_MOC_H))))

OGCALC_UI_DEFS = $(wildcard *.ui)
OGCALC_UI_SRC = $(addprefix ui_,$(addsuffix .h,$(basename $(OGCALC_UI_DEFS))))

BUILT_SOURCES = moc.cpp $(OGCALC_UI_SRC)

moc.cpp: $(OGCALC_MOC_SRC)
	cat $^ > $@

bin_PROGRAMS = ogcalc

lib_LTLIBRARIES = libentry.la

plugindir = /lib
plugin_LTLIBRARIES = libplugin.la

libentry_la_SOURCES =		\
	SpinBoxEntry.h		\
	SpinBoxEntry.cpp
libentry_la_CXXFLAGS = $(AM_CXXFLAGS) $(QTW_CFLAGS) -fPIC
libentry_la_LIBADD = $(QTW_LIBS)

libplugin_la_SOURCES =		\
	SpinBoxEntryPlugin.h	\
	SpinBoxEntryPlugin.cpp
libplugin_la_CXXFLAGS = $(AM_CXXFLAGS) $(QTUI_CFLAGS) -fPIC
libplugin_la_LDFLAGS = -module -avoid-version
libplugin_la_LIBADD = $(QTUI_LIBS)


ogcalc_SOURCES =		\
	main.cpp		\
	ogcalc.h		\
	ogcalc.cpp		\
nodist_ogcalc_SOURCES = moc.cpp $(OGCALC_UI_SRC)
ogcalc_CXXFLAGS = $(AM_CXXFLAGS) $(QT_CFLAGS) -fPIC
ogcalc_LDADD = $(QT_LIBS) libentry.la

moc_%.cpp: %.h
	moc $< -o $@

ui_%.h: %.ui
	uic $< -o $@

CLEANFILES = $(OGCALC_MOC_SRC) $(OGCALC_UI_SRC) $(BUILT_SOURCES)
