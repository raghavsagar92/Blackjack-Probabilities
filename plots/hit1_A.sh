gnuplot << EOF
set term png enhanced size 1280,800

set output "hit1_A.png"

reset

unset tics
unset grid
unset label

set title "Player Winning Probability in Blackjack (Ace) - Hit once"
set xlabel "Player Cards"
set ylabel "Dealer Card"


set xrange [1:10.5]
set yrange [2:11]
set zrange [0:1]
set xtics ('A,2' 1, 'A,3' 2, 'A,4' 3, 'A,5' 4, 'A,6' 5, 'A,7' 6, 'A,8' 7, 'A,9' 8, 'A,(10,J,Q,K)' 9, 'A,A' 10)
set ytics ('0' 0, '1' 1, '2' 2, '3' 3, '4' 4, '5' 5, '6' 6, '7' 7, '8' 8, '9' 9, '10,J,Q,K' 10, 'A' 11 )

set ztics 0,0.2

set dgrid3d
set contour both
set hidden3d

set pm3d at sb
set palette gray
set ticslevel 0.8
set isosample 40,40
set cntrparam levels discrete 0.35 , 0.4, 0.5

splot './hit1_A.out' using 1:2:3 with lines notitle




EOF
exit 0
