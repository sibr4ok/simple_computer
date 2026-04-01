all: mySimpleComputer myTerm myBigChars console

mySimpleComputer:
	$(MAKE) -C mySimpleComputer

myTerm:
	$(MAKE) -C myTerm

myBigChars:
	$(MAKE) -C myBigChars

console: mySimpleComputer myTerm myBigChars
	$(MAKE) -C console

font: console
	cd console && ./font

run: all font
	cd console && ./pr01

clean:
	$(MAKE) -C mySimpleComputer clean
	$(MAKE) -C myTerm clean
	$(MAKE) -C myBigChars clean
	$(MAKE) -C console clean
	rm -f console/font.bin

.PHONY: all mySimpleComputer myTerm myBigChars console font run clean