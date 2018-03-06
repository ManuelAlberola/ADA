#Manuel Alberola Torres 74017527-P
OPTS = -Wall -O3 -std=c++0x

all: pow2 pow2.recursiveCalls pow2.png

pow2: pow2.cc
	g++ ${OPTS} -o pow2 pow2.cc

pow2.recursiveCalls: pow2
	./pow2 > pow2.recursiveCalls

pow2.png: pow2.recursiveCalls pow2.gnuplot
	gnuplot pow2.gnuplot
