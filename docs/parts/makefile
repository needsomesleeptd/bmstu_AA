PDF = RPZ_RAZIN_IU7_44B
MAIN = main

$(PDF) : $(MAIN).tex *.tex
	pdflatex --shell-escape $< 
	biber $<
	pdflatex --shell-escape $< 
	biber $<
	pdflatex --shell-escape $< 
	
	make clean



clean:
	rm  *.aux *.log *.out *.toc *.bbl *.blg  *.gz *.aux *.fls

.PHONY: clean, bib