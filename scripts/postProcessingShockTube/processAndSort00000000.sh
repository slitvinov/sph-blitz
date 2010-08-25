#! /bin/bash
#this script processes the file prtl00000000.dat which consists of the initial particle values. It aimes to find out particle IDs of particles initially being located at the same x. The particles values after a certain simulation time will then be averaged for each particle ensemble initially having the sa,e x position

# remove first to lines from file and save under new file name
sed '1,2d' ~/sph-blitz/src/outdata/prtl00000000.dat >tempfile.dat
if [ -d ~/sph-blitz/results/ResultsInProgress ]
then
echo "directory sph-blitz/results/ResultsInProgress already exists. Its former content has been deleted"
rm -rf  ~/sph-blitz/results/ResultsInProgress
mkdir ~/sph-blitz/results/ResultsInProgress
else
echo "creating directory sph-blitz/results/ResultsInProgress where all the processed files are written into "
mkdir ~/sph-blitz/results/ResultsInProgress
fi 
# sort particles on the y-position
sort -t: +1 -2 tempfile.dat >~/sph-blitz/results/ResultsInProgress/sorted00000000.dat
echo "file sorted00000000.dat has been written into: sph-blitz/results/ResultsInProgress "
rm tempfile.dat
