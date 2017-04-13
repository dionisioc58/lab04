#Inicializacao
clear
reset
set key off

#Configuracoes de saida: inclui formato de exportacao, tamanho do grafico,
#fontes utilizadas e nome do arquivo de saida

#Exportacao para o formato .png
set terminal png size 640,480 enhanced font 'Helvetica,12'
set output './data/histograma.png'

set title 'Total de nascidos vivos no RN (1994-2014)'

set xrange[1994:2014]
set xtics 1
set xtic rotate by -45 scale 0

set yrange[0:80000]

set style data histogram
set style histogram clustered gap 1
set style fill solid border -1
set linetype 1 lc rgb 'green'
set boxwidth 0.6

plot './data/totais.dat' using 1:2 title '' smooth freq with boxes