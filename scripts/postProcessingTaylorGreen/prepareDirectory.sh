#! /bin/bash
#this script makes a new directory ResultsInProgress or (if it already exists) deets its content

if [ -d ~/sph-blitz/results/ResultsInProgress ]
then
echo "directory sph-blitz/results/ResultsInProgress already exists. Its former content has been deleted"
rm -rf  ~/sph-blitz/results/ResultsInProgress
mkdir ~/sph-blitz/results/ResultsInProgress
else
echo "creating directory sph-blitz/results/ResultsInProgress where all the processed files are written into "
mkdir ~/sph-blitz/results/ResultsInProgress
fi 


