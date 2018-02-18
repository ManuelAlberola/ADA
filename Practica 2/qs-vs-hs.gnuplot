#Manuel Alberola Torres 74017527P


##########################################################################
set terminal png
#set output "qs-vs-hs.png"

set xlabel "Array size"
set ylabel "Steps"


set title  "Quick Sort: Empirical Analysis of Exact Time Complexity"
plot "qs-vs-hs.Msteps" using 1:2 with lines title "pasos de ejemplo"


##########################################################################
#Testing different analytical functions to determine which best fits:

set output "quickSort.png"
set yrange [0:100]
set xrange [32768:4194304]

#quickSort.png.
plot  "qs-vs-hs.Msteps" using 1:2 w l title "Sin orden", "qs-vs-hs.Msteps" using 1:4 w l title "Con orden", "qs-vs-hs.Msteps" using 1:6 w l title "Orden inverso"


##########################################################################
set output "heapSort.png"
#heapSort.png.
plot  "qs-vs-hs.Msteps" using 1:3 w l title "Sin orden", "qs-vs-hs.Msteps" using 1:5 w l title "Con orden", "qs-vs-hs.Msteps" using 1:7 w l title "Orden inverso"


##########################################################################
set output "qs-vs-hs-RA.png"

#n*log(n)
y(x)=a*x*log(x)+b*x
fitFunction="nlog(n)+n quick"
fit y(x) "qs-vs-hs.Msteps" using 1:2 via a,b

h(x)=a*x*log(x)+b*x
fitFunction1="nlog(n)+n heap"
fit h(x) "qs-vs-hs.Msteps" using 1:3 via a,b
#qs-vs-hs-RA.png
# para estos  +n  
plot "qs-vs-hs.Msteps" using 1:2 w l title "Quick SO","qs-vs-hs.Msteps" using 1:3 w l title "Heap SO",h(x) title fitFunction1,y(x) title fitFunction

##########################################################################

set output "qs-vs-hs-SA.png"
#n*log(n)
y(x)=a*x*log(x)+b*x
fitFunction="nlog(n)+n quick"
fit y(x) "qs-vs-hs.Msteps" using 1:4 via a,b

h(x)=a*x*log(x)+b*x
fitFunction1="nlog(n)+n heap"
fit h(x) "qs-vs-hs.Msteps" using 1:5 via a,b
plot "qs-vs-hs.Msteps" using 1:4 w l title "Quick CO","qs-vs-hs.Msteps" using 1:5 w l title "Heap CO",h(x) title fitFunction1,y(x) title fitFunction

##########################################################################
set output "qs-vs-hs-RSA.png"
#n*log(n)
y(x)=a*x*log(x)+b*x
fitFunction="nlog(n)+n quick"
fit y(x) "qs-vs-hs.Msteps" using 1:6 via a,b

h(x)=a*x*log(x)+b*x
fitFunction1="nlog(n)+n heap"
fit h(x) "qs-vs-hs.Msteps" using 1:7 via a,b
set output "qs-vs-hs-RSA.png"
plot "qs-vs-hs.Msteps" using 1:6 w l title "Quick OI","qs-vs-hs.Msteps" using 1:7 w l title "Heap OI",h(x) title fitFunction1,y(x) title fitFunction










