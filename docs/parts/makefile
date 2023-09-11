PDF = RPZ_RAZIN_IU7_44B
MAIN = main

$(PDF) : $(MAIN).tex *.tex
	pdflatex  $< 
	pdflatex  $< 
	
	make clean



clean:
	rm  *.aux *.log *.out *.toc *.bbl *.blg  *.gz *.aux *.fls

.PHONY: clean, bib