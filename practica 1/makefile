#Manuel Alberola Torres 74017527-P
OPTS = -Wall -O3 -std=c++0x

all: quickSort quickSort.CPUtimes graphs

quickSort: quickSort.cc
	g++ ${OPTS} -o quickSort quickSort.cc

quickSort.CPUtimes: quickSort
	./quickSort > quickSort.CPUtimes

graphs: quickSort.CPUtimes quickSort.gnuplot
	gnuplot quickSort.gnuplot
