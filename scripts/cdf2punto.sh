#!/bin/bash
#converts netcdf sph++ data to text format and sands the data to punto (http://www.fisfun.uned.es/~mrevenga/punto.html)
#Input arguments
#  $1: netcdf file name,
#  $2: the number of the first time snapshot to show (default: 0)
#  $3: the number of the last time snapshot to show (default: the maximum number of snapshot in the file)
#Notes: the program leave the file punto.dat with sph++ data in the text format
#Options:
# -q: dont output the step numbers
# -p: print output to the stdout
# -o "filename": output file name (default value is punto.dat)
# -v variable name (default value is R)
# -l output just polymer (no solvent)
#Usage:
#  ./cdf2punto.sh par.nc 3 8
#  ./cdf2punto.sh par.nc 10    
# ./cdf2punto.sh par.nc


#program options
OUTSTREAM="/dev/stdout"
OUTPUT=punto.dat
VARNAME=R

while getopts ":qpo:v:l" Option
do
    case $Option in
	q) OUTSTREAM=/dev/null;;
	p) OUTSTREAM=/dev/null; OUTPUT=/dev/stdout;;
	o) OUTPUT=$OPTARG;;
	v) VARNAME=$OPTARG;;
	l) OUTPOLY=1
    esac
done

shift $(($OPTIND - 1))


TIME=0
INPUT=$1
MAXTIME=$(ncdump -h $INPUT | grep timestep.*currently | grep -o [0-9][0-9]*)
MAXTIME=$(($MAXTIME - 1))



if [ "$#" -gt "1" ]; then
	TIME=$2
fi

if [ "$#" -gt "2" ]; then
    if [ "$3" -gt "0" ]; then
	MAXTIME=$3	
    fi
fi

if [ "$#" -gt "3" ]; then
    RUNPUNTOSHOW=1
fi


TMPTYPE=`mktemp /tmp/type.XXXXXXX`
TMPDAT=`mktemp /tmp/type.XXXXXXX`



while [ $TIME -le "$MAXTIME" ]; do    
    ncks -d timestep,$TIME,$TIME  -s "%4.3e\n" -v $VARNAME $INPUT | \
	awk 'NF==1' | \
	awk 'NR%2 {s=$0}; !(NR%2) {print s, $0}' >> ${TMPDAT}
    printf "\n" >> ${TMPDAT}

    ncks -d timestep,$TIME,$TIME  -s "%.0f\n" -v type $INPUT | \
	awk 'NF==1' >> ${TMPTYPE}
    printf "\n" >> ${TMPTYPE}
    echo $TIME > $OUTSTREAM
    TIME=$(($TIME+1))
done

if [ -n "$OUTPOLY" ]; then
    paste -d " " ${TMPDAT} ${TMPTYPE} | gawk 'NF==0{printf "\n"} $3>0{print $1, $2}' > $OUTPUT 
else
    paste -d " " ${TMPDAT} ${TMPTYPE} | gawk 'NF==0{printf "\n"} NF' > $OUTPUT 
fi

rm ${TMPDAT} ${TMPTYPE}
exit
