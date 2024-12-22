set datafile separator ';'
set term png
set output "graphs/lv_all_graphe.png"
set boxwidth 1
set title 'Postes LV les moins chargés et les plus chargés'
set grid
set style fill solid 1.0 border -1
set xtics border in scale 0,10  nomirror rotate by -45
set xlabel 'Identifiant'
set ylabel 'Capacité restante'
unset key
plot "tests/lv_all_minmax.csv" using ($0):4:(column(4) > 0 ? 0x00FF00 : 0xFF0000):xticlabels(1) w boxes lc rgb variable

