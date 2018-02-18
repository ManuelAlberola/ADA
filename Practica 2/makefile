#Manuel Alberola Torres 74017527-P
OPTS = -O3 -std=c++0x

all: qs-vs-hs qs-vs-hs.Msteps graphs

qs-vs-hs: qs-vs-hs.cc
	g++ ${OPTS} -o qs-vs-hs qs-vs-hs.cc

qs-vs-hs.Msteps: qs-vs-hs
	./qs-vs-hs > qs-vs-hs.Msteps

graphs: qs-vs-hs.Msteps qs-vs-hs.gnuplot
	gnuplot qs-vs-hs.gnuplot
