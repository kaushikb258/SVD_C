all:
	gcc svd.c main.c matrix.c -lm -o svd.exe
clean:
	rm *.exe *.dat
