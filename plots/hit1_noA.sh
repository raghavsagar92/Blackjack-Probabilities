gnuplot << EOF
set term png enhanced size 1280,800

set output "hit1_noA.png"

reset

unset tics
unset grid
unset label

set title "Player Winning Probability in Blackjack (no Ace) - Hit once"
set xlabel "Sum of Player Cards"
set ylabel "Dealer Card"

set style line 1 lt 1 pt 2 lc rgb "red" lw 2
set style line 2 lt 1 pt 2 lc rgb "orange" lw 2
set style line 3 lt 1 pt 2 lc rgb "yellow" lw 2
set style line 4 lt 1 pt 2 lc rgb "green" lw 2
set style line 5 lt 1 pt 2 lc rgb "violet" lw 2
set style line 6 lt 1 pt 2 lc rgb "blue" lw 2
set style line 7 lt 1 pt 2 lc rgb "violet" lw 2

set xrange [4:20.5]
set yrange [2:11]
set zrange [0:1]
set ytics ('0' 0, '1' 1, '2' 2, '3' 3, '4' 4, '5' 5, '6' 6, '7' 7, '8' 8, '9' 9, '10,J,Q,K' 10, 'A' 11 )
set xtics auto
set ztics 0,0.2

set dgrid3d
set contour both
set hidden3d

set pm3d at sb
set palette gray
set ticslevel 1.8
set isosample 40,40
set cntrparam levels discrete 0.35,0.4, 0.45

splot './hit1_noA.out' using 1:2:3 with lines notitle




EOF
exit 0
