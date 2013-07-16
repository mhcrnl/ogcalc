MOC_HEADERS = $(shell egrep -l "[[:space:]]*((public|protected|private)[[:space:]]+)?signals|slots:" *.h)
MOC_SOURCES = $(addprefix moc_,$(addsuffix .cpp,$(basename $(MOC_HEADERS))))

UI_DEFS = $(wildcard *.ui)
UI_SOURCES = $(addprefix ui_,$(addsuffix .h,$(basename $(UI_DEFS))))

default:
	echo $(MOC_HEADERS)
	echo $(MOC_SOURCES)
	echo $(UI_DEFS)
	echo $(UI_SOURCES)

moc_%.cpp: %.h
	moc $< -o $@

ui_%.h: %.ui
	uic $< -o $@
