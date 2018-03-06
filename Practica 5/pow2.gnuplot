#Manuel Alberola Torres 74017527P

set terminal png
set output "pow2.png"

set xlabel "n"
set ylabel "Recursive calls"
set title  "Exact time complexity pow2() functions"

set yrange [0:2000]
plot "pow2.recursiveCalls" using 1:2 with lines title "pow2(n)=2 x pow2(n-1)",\
"pow2.recursiveCalls" using 1:3 with lines title "pow2(n)=pow2(n/2) x pow2 (n/2)",\
"pow2.recursiveCalls" using 1:4 with lines title "pow2(n)=(pow2(n/2))²",\
"pow2.recursiveCalls" using 1:5 with lines title "pow2(n)=pow2(n-1)+pow2(n-1)"


