all: 	firfilt.c iirfilt.c iirfilt_float.c eq
	gcc firfilt.c -o firfilt
	gcc iirfilt.c -o iirfilt
	gcc iirfilt_float.c -o iirfilt_float

eq:	eq3band.c
	gcc eq3band.c -o eq
	./eq > out.dat

clean:
	rm -f firfilt
	rm -f iirfilt
	rm -f iirfilt_float
	rm -f eq
	rm -f out.dat
