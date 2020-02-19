.DEFAULT: all

all:
	@pdflatex Main
	@cd batcapture && pdflatex batcapture
	@cd batrec && pdflatex batrec
	@cd sonart && pdflatex sonart
	@cd upone && pdflatex upone
	@cd wbox && pdflatex wbox
	@cd plain && pdflatex plain

main:
	@pdflatex Main

tidy:
	@rm -f *.aux
	@rm -f *.toc
	@rm -f *.out
	@rm -f *.log
	@rm -f */*.aux
	@rm -f */*.toc
	@rm -f */*.out
	@rm -f */*.log

clean: tidy
	@mv images/logo-top.pdf images/logo-top.pdf.bak
	@rm -f *.pdf
	@rm -f */*.pdf
	@mv images/logo-top.pdf.bak images/logo-top.pdf
