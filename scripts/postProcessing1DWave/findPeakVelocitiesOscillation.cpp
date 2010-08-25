

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <math.h>


using namespace std;

int main (){
  
  const int n_col=8;// number of columns in simulation output file
  double buffer;
  double timeInterval;// output time interval for simulation data output files
  double lambda; // wave length
  int counter=0;
  vector<double> row(n_col,0);
  vector <vector <double> > inputFileData; // stores data read from inputfile
  vector <vector <double> > MaxVelocAllInstants;// vector for max velocities of all instants and their corresponding time value
  vector <double>maxVelThisInstAndTime(2,0);
  int fileCounter=0;
  
  cout<<"please enter the output time interval in s (as specified in 1DWave.tcl file:"<<endl;
  cin>>timeInterval;
cout<<"please enter the wavelength of the oscillation (as specified in createIC-file):"<<endl;
 cin>>lambda;

  // while loop over all output intervall values
  for(;;) {
    double maxVelocThisInstant=-10000;// max velocity of current instant(=output time)
    
    // assemble input file name
    stringstream number;//string for number (time stamp)
    stringstream number2;//string for second time stamp if first one not o.k.
    // calculate number (time stamp) for file name
    // needs to be casted to int as otherwise numbers over 1,000,000 
    // have the format 1e+6 which is not ok for the file name
    number << setw(8) << setfill('0') <<(int)(fileCounter*timeInterval*1000000);
    const string inputfile = "../../src/outdata/prtl" + number.str() + ".dat";
    cout<<endl<<inputfile<<endl;

    // create and open inputfile
    ifstream fin(inputfile.c_str(), ios::in);
    // test if inputfile opened, if not try different filename
    if (!fin) {
      // this is as sometimes filenames are...999 instead of ..0000
      // because time value is truncated for timestamp of file name...
      number2 << setw(8) << setfill('0') <<(int)(fileCounter*timeInterval*1000000-1);
      const string inputfile2 = "../../src/outdata/prtl" + number2.str() + ".dat";
      cout<<endl<<inputfile2<<endl;
      // assign a new filename to the streaming object
      fin.open(inputfile2.c_str(), ifstream::in);
      if(!fin) {
	cout<<"no (more)file could be found: either all files have already been processed"<<endl;
	cout<<"or there is a problem with the file name"<<endl;
	cout<<"to chech if all files have already been treated, here the number of files that are read by the program: "<<fileCounter<<endl;
	break;
      }
    }     
    // while reading directly sort out the boundary particles
    while(!fin.eof()) {
      
      // very "elegant" way of cutting off first to lines of file 
      // (as they do not contain data), but did not know any better
      string garbage;
      getline(fin,garbage);
      getline(fin,garbage);
      
      for (int i=0; i<n_col&&!fin.eof();i++) {
	// problem: reads always one more than eof
	fin>>buffer;
	row[i]=buffer; 
      }
      // to be sure the last row (which is already eof and does
      // not correspond to a physical row of the file any more)
      // is not added make ID=0;
      if(fin.eof()) {
	row[6]=0;
      }
      // determine max velocity for this instant if
      // -the row does not correspond to a boundary particle
      // (for which ID=0)
      // - and if x is <wavelength/2 (to only treat LHS of the first wave 
      // (as there would be other maximum at T/2 for RHS of wave)      
      if(row[n_col-2]!=0&&row[0]<0.5*lambda) {
	inputFileData.push_back(row);
      }
    } 
    
    fin.close();// close inputfile
    
    // now determine max velocity this instant
    // being aware that values at the edges (0 and 0.5) are no local maxima
    // and therefore are not to be considered
    // that is by the way why a simple allgorithm like:
    // if (row[4]>maxVelocThisInstant)
    //	  maxVelocThisInstant=row[4];
    // does not work!

    // he program has got some slight problems comparing those double and
    // exacuting this allgorithm: if the two values next to the maximum are
    // exactly identical, it finds nothing, and some times it takes the value
    // before or after the actual maximum!
    // is there something wrong with this allgorithm or is it a c++ problem
    // related to double comparison or something lese???
    for (int i=0;i<inputFileData.size()-2;i++) {
      //if it is a real local maximum (not at the edges)
      if(inputFileData[i][4]<inputFileData[i+1][4])
	if( inputFileData[i+1][4]>inputFileData[i+2][4]) {
	  // if now it is bigger than possible previous max at this instant:
	  if (inputFileData[i+1][4]>maxVelocThisInstant)
	    maxVelocThisInstant=inputFileData[i+1][4];
	}
    }
    //clear inputfile data for next file
    inputFileData.clear();

    // pair maximum velocity of this instant with corresponding time:
    maxVelThisInstAndTime[0]=maxVelocThisInstant;
    maxVelThisInstAndTime[1]=fileCounter*timeInterval;
    //put max velocity this instant in an array/vector
    MaxVelocAllInstants.push_back(maxVelThisInstAndTime);
    //increment file counter as loop will restart for next input file
    fileCounter++;  
  }
  // end while loop over all files
  
  // now find the local maxima in the  MaxVelocAllInstants vector as they are the 
  // needed peak velocity values for each period
  vector <vector <double> >PeakVelocEachPeriod;
  // first entry is a maximum (known, as initialization is done that way)
  PeakVelocEachPeriod.push_back(MaxVelocAllInstants[0]);
  // now iterate all aoterh entries and try to find local maxima
  for(int i=0;i< MaxVelocAllInstants.size()-2;i++) {
    if(MaxVelocAllInstants[i][0]<MaxVelocAllInstants[i+1][0]
       &&MaxVelocAllInstants[i+2][0]<MaxVelocAllInstants[i+1][0])
      PeakVelocEachPeriod.push_back(MaxVelocAllInstants[i+1]);
  }
  
  const string outputfile = "../../results/ResultsInProgress/peakVelocities.dat";
  // create and open outputfile
  ofstream out(outputfile.c_str());
  
  // test if file opened
  if (!out){
    cout<<"Cannot create file "<<outputfile<<"\n" ;
    exit(1);
  }
  else cout<<"\n writing in file\n"; 
  // write file header
  out<<"peak velocity for each period and corresponding time\n";
  out<<"period number | peak velocity | adimensional peak velocity| time |adimensional time \n";
  // write data into file
  for(int i=0;i<PeakVelocEachPeriod.size();i++) {
    out<<setprecision(9)
       << ::setw(17)<<i+1 // period number (starting at 1)
       << ::setw(17)<<PeakVelocEachPeriod[i][0] // peak velocity
       << ::setw(17)<<PeakVelocEachPeriod[i][0]/PeakVelocEachPeriod[0][0] // peak velocity (adimensional)
       << ::setw(17)<<PeakVelocEachPeriod[i][1] // corresponding time    
       << ::setw(17)<<PeakVelocEachPeriod[i][1]/PeakVelocEachPeriod[1][1] // corresponding time   
       <<"\n";
  }
  out.close();// close output file
  cout<<"\n 1D Wave port-processing date written to:\n";
  cout<<"   "<<outputfile<<"\n";
  






 const string outputfile2 = "../../results/ResultsInProgress/DampingPeriod.dat";
  // create and open outputfile
  ofstream out2(outputfile2.c_str());
  
  // test if file opened
  if (!out2){
    cout<<"Cannot create file "<<outputfile2<<"\n" ;
    exit(1);
  }
  else cout<<"\n writing in file\n"; 
  // write file header
  out2<<"Damping and periodic time\n";
  out2<<"period number (1 means: damping between period 1 and 2,...) | damping | periodic time (normalized with T of first period\n";
  // write data into file
  for(int i=0;i<PeakVelocEachPeriod.size()-1;i++) {
    out2<<setprecision(9)
       << ::setw(17)<<i+1 // period number (starting at 1)
       << ::setw(17)<<(PeakVelocEachPeriod[i+1][0]-PeakVelocEachPeriod[i][0])/-PeakVelocEachPeriod[i][0]// damping
       << ::setw(17)<<(PeakVelocEachPeriod[i+1][1]-PeakVelocEachPeriod[i][1])/PeakVelocEachPeriod[1][1]// normalized periodic time
       <<"\n";
  }
  out2.close();// close output file
  cout<<"\n 1D Wave port-processing date written to:\n";
  cout<<"   "<<outputfile2<<"\n";




  cout<<"\n program ended\n";
  return 0;
}

   
