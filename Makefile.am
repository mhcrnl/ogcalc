# Subdirectories to make.
SUBDIRS = C C++ python figures

# Rules to build documentation.
docs: ogcalc.pdf

ogcalc.pdf: ogcalc.tex pdf_figures
	pdflatex $<
	pdflatex $<
	pdflatex $<
#	thumbpdf $(basename $<)
	pdflatex $<
	$(MAKE) tidy
	$(MAKE) -C figures tidy

pdf_figures:
	make -C figures $@

# Rules for cleaning.
tidy:
	rm -f ogcalc.aux ogcalc.lof ogcalc.log ogcalc.lol ogcalc.out ogcalc.toc ogcalc.tpt

clean-local: tidy

MAINTAINERCLEANFILES = ogcalc.pdf

# Data to distribute.
EXTRA_DIST = ogcalc.tex ogcalc.pdf

.PHONY: pdf_figures tidy
