# The figures used in the tutorial document.
noinst_DATA = \
	box-packing.fig \
	c-glade.png \
	c++-glade.png \
	c-gobject.png \
	container-hbox.fig \
	container-table.fig \
	container-vbox.fig \
	c-plain.png \
	c++-plain.png \
	glade-main-window.png \
	glade-ogcalc.png \
	glade-palette.png \
	glade-properties.png \
	glade-widget-tree.png \
	gtk-button.png \
	gtk-check-button.png \
	gtk-combo-box.png \
	gtk-font-selection.png \
	gtk-label.png \
	gtk-menu.png \
	gtk-text-entry.png \
	packing-1.fig \
	packing-2.fig \
	packing-3.fig \
	packing-4.fig \
	packing-5.fig \
	packing-final.fig \
	signals.fig \
	sketch.fig

# Rule for generating PDF figures.
%.pdf: %.fig
	fig2dev -L pdf $< $@

# Generated PDF figures.
PDF_FIGURES = \
	box-packing.pdf \
	container-hbox.pdf \
	container-table.pdf \
	container-vbox.pdf \
	packing-1.pdf \
	packing-2.pdf \
	packing-3.pdf \
	packing-4.pdf \
	packing-5.pdf \
	packing-final.pdf \
	signals.pdf \
	sketch.pdf

# Create generated PDF figures.
pdf_figures: $(PDF_FIGURES)

# Clean generated PDF figures.
tidy:
	rm -f $(PDF_FIGURES)

clean-local: tidy

# Distribute figures.
EXTRA_DIST = $(noinst_DATA)

.PHONY: pdf_figures tidy
