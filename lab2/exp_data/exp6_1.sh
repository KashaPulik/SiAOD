#!/usr/bin/gnuplot

set termoption enhanced
set terminal svg size 1600,800 font "Arial, 18"
set output "exp6_1.svg"

set style line 1 lc rgb "0xDC143C" lt 1 lw 4 pt 9 ps 1
set style line 2 lc rgb "0x6495ED" lt 1 lw 4 pt 7 ps 1

set border lw 2
set grid
set key top left

set xlabel "Количество элементов в словаре" font "Arial, 24"
set ylabel "Время поиска элемента, с" rotate by 90  font "Arial, 24"
set xtics 10000
set ytics 0.0001
set yrange [0:0.0003]
set mxtics
set format x "%6.0f"
set format y "%.6f"

plot "exp6.dat" using 1:2 title "KRHash" with linespoints ls 1, \
"exp6.dat" using 1:4 title "Jenkins Hash" with linespoints ls 2
