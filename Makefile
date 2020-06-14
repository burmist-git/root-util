all: makeHistFromFile

makeHistFromFile: makeHistFromFile.C
	g++ -o makeHistFromFile makeHistFromFile.C `root-config --cflags --glibs`

clean:
	rm makeHistFromFile
	rm *~
