reset
set key on
set grid
set terminal png size 640,480 enhanced font 'Helvetica,12'
set output './data/extra.png'
set title 'Taxa de crescimento por ano no RN (1994-2014) (filtrado)'
set xrange[1994:2014]
set xtics 1
set xtic rotate by -90 scale 0
set ytic 20
set xlabel 'Anos'
set ylabel 'Taxa de crescimento (%)'
set yrange[-30:42]
plot './data/extra.dat' using 1:2 title 'Natal' lw 2 with lines, './data/extra.dat' using 1:3 title 'Parnamirim' lw 2 with lines, './data/extra.dat' using 1:4 title 'Extremoz' lw 2 with lines, './data/extra.dat' using 1:5 title 'São Gonçalo do Amarante' lw 2 with lines, './data/extra.dat' using 1:6 title 'Ceará-Mirim' lw 2 with lines, 
