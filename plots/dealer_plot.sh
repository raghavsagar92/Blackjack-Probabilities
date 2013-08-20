gnuplot << EOF
set term png enhanced size 1280,800

set output "dealer_plot.png"

reset

unset tics
unset grid
unset label

set title "Probability v/s Dealer Card"
set xlabel "Dealer Card"
set ylabel "Probability"

set xtics ('2' 2, '3' 3, '4' 4, '5' 5, '6' 6, '7' 7, '8' 8, '9' 9, '10.J,Q,K' 10, 'A' 11)
set ytics auto
set yrange [0:1]

set style line 1 lt 1 pt 2 lc rgb "red" lw 2
set style line 2 lt 1 pt 2 lc rgb "orange" lw 2
set style line 3 lt 1 pt 2 lc rgb "yellow" lw 2
set style line 4 lt 1 pt 2 lc rgb "green" lw 2
set style line 5 lt 1 pt 2 lc rgb "violet" lw 2
set style line 6 lt 1 pt 2 lc rgb "blue" lw 2
set style line 7 lt 1 pt 2 lc rgb "violet" lw 2

plot './dealersp_plot.out' using 1:2 axes x1y1 title "Dealer Score : 17"  with linespoints ls 1, \
	'./dealersp_plot.out' using 1:3 axes x1y1 title "Dealer Score : 18"  with linespoints ls 2, \
	'./dealersp_plot.out' using 1:4 axes x1y1 title "Dealer Score : 19"  with linespoints ls 3, \
	'./dealersp_plot.out' using 1:5 axes x1y1 title "Dealer Score : 20"  with linespoints ls 4, \
	'./dealersp_plot.out' using 1:6 axes x1y1 title "Dealer Score : 21"  with linespoints ls 5, \
	'./dealersp_plot.out' using 1:7 axes x1y1 title "Dealer Busted"  with linespoints ls 6

EOF
exit 0
