#

itime=2; plot "test/par.txt" u 2:3 every :::itime::itime


#plot polymer
itime=2; plot "test2/par.txt" u 1:2 every :::itime::itime, "" u 1:($2-0/$6) every :::itime::itime
