tex_files:=$(wildcard *.tex)

all:geom

geom: $(tex_files)
	pdflatex -jobname $@ $^ 

clean:
	rm -f *.aux
	rm -f *.log
	rm -f *.pdf
	rm -f *.out
