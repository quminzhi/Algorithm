# _*_ MakeFile _*_

CC=g++
FLAG=-Wall -I.
GFLAG=-Wall -g -I.

Target=csort
CleanFile=*.o *.dSYM data

ALL: $(Target).cpp
	$(CC) $(FLAG) $(Target).cpp -o $(Target)

test: $(Target).cpp
	$(CC) $(GFLAG) $(Target).cpp -o $(Target)tt

clean:
	rm -rf $(CleanFile) $(Target) $(Target)tt
