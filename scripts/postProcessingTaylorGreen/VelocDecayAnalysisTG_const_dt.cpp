

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

  // settings for calculation of exact solution
  const double U=1.0;
  const double Re=0.01;

  int n_col=0;// number of columns in inputfile

  cout<<"\n"<<"please enter the number of columns in the input file:  ";
  cin>>n_col;

  int high_res_timestamp=2;
  while (high_res_timestamp!=1 &&high_res_timestamp!=0) {
    cout<<"\n"<<"please enter the timestamp resolution \n  ";
    cout<<"\n"<<"0: standard timestamp resolution (10^-6) \n ";
    cout<<"\n"<<"1: high timestamp resolution (10^-10) \n ";
    cin>>high_res_timestamp;
  }

  double timeStampRes;
  if(high_res_timestamp==1)
    timeStampRes=1e10;
  else
    timeStampRes=1e6;

  double buffer;
  double timeInterval;// output time interval for simulation data output files
  int counter=0;
  vector<double> row(n_col,0);
  vector <vector <double> > inputFileData; // stores data read from inputfile
  vector <vector <double> > MaxVelocAllInstants;// vector for max velocities of all instants and their corresponding time value
  vector <double>maxVelThisInstAndTime(2,0);
  int fileCounter=0;
  
  cout<<"please enter the output time interval in s (as specified in TaylorGreen.tcl file:"<<endl;
  cin>>timeInterval;
  
  // while loop over all output interval values
  for(;;) {
    double maxVelocThisInstant=-10000;// max velocity of current instant(=output time)
    
    // assemble input file name
    stringstream number;// string for number (time stamp)
    stringstream number2;// string for second time stamp if first one not o.k.
    stringstream number3;// string for third time stamp if second one not o.k.

    // calculate number (time stamp) for file name
    // needs to be casted to int as otherwise numbers over 1,000,000 
    // have the format 1e+6 which is not ok for the file name
    number << setw(8) << setfill('0') <<(int)(fileCounter*timeInterval*timeStampRes);
    const string inputfile = "../../src/outdata/prtl" + number.str() + ".dat";
    cout<<endl<<inputfile<<endl;

    // create and open inputfile
    ifstream fin(inputfile.c_str(), ios::in);
    // test if inputfile opened, if not try different filename
    if (!fin) {
      // this is, as sometimes filenames are...999 instead of ..0000
      // because time value is truncated for timestamp of file name...
      number2 << setw(8) << setfill('0') <<(int)(fileCounter*timeInterval*timeStampRes-1);
      const string inputfile2 = "../../src/outdata/prtl" + number2.str() + ".dat";
      cout<<endl<<inputfile2<<endl;
      // assign a new filename to the streaming object
      fin.open(inputfile2.c_str(), ifstream::in);
      if (!fin) {
	// this is, as sometimes filenames are...999 instead of ..0000
	// because time value is truncated for timestamp of file name...
	number3 << setw(8) << setfill('0') <<(int)(fileCounter*timeInterval*timeStampRes+1);
	const string inputfile3 = "../../src/outdata/prtl" + number3.str() + ".dat";
	cout<<endl<<inputfile3<<endl;
	// assign a new filename to the streaming object
	fin.open(inputfile3.c_str(), ifstream::in);
	if(!fin) {
	  cout<<"no (more)file could be found: either all files have already been processed"<<endl;
	  cout<<"or there is a problem with the file name"<<endl;
	  cout<<"to chech if all files have already been treated, here the number of files that are read by the program: "<<fileCounter<<endl;
	  break;
	}
      }   
    } 
    // while reading, directly sort out the boundary particles
    while(!fin.eof()) {
      
      // very "elegant" way of cutting off first two lines of file 
      // (as they do not contain data), but did not know any better
      string garbage;
      getline(fin,garbage);
      getline(fin,garbage);
      
      // loop over all entries in one row
      for (int i=0; i<n_col&&!fin.eof();i++) {
	// read every entry and save it in the corresponding spot
	// in the row variable 
	fin>>buffer;
	row[i]=buffer; 
      }
      
      // store particle data (=row) in input-file-variable if:
      // -the row does not correspond to a boundary particle
      // (for which ID=0)
      // the different rows in the underlying simulation data file are
      // (in the SPLASH-optimized output mode)
      // x | y | Ux | Uy | rho | e | p | h=supportlength/2 | m | V | ID 
      if(row[10]!=0) {

	// determine max velocity this instant
	const double velocity=sqrt(pow(row[2],2)+pow(row[3],2));
	if (velocity>maxVelocThisInstant)
	  maxVelocThisInstant=velocity;
      }
    } 
    
    fin.close();// close inputfile
       
    // pair maximum velocity of this instant with corresponding time:
    maxVelThisInstAndTime[1]=maxVelocThisInstant;
    maxVelThisInstAndTime[0]=fileCounter*timeInterval;
    // put max velocity this instant in an array/vector
    MaxVelocAllInstants.push_back(maxVelThisInstAndTime);
    // increment file counter as loop will restart for next input file
    fileCounter++;  
  }
  // end while loop over all files

  //control-output
  cout<<"number of instants (=data-files): "<<MaxVelocAllInstants.size()<<endl;
  
  // calculate exact solution (theoretical decay)
  
  // variables needed for computation of exact solution
  const double PI=3.14159265358979323846;
  const double b=(-8*pow(PI,2)/Re);
  
  // temporal resolution of evaluated points higher (by a factor tempResFact) than
  // for simulation results (this is due to plotting-reasons, as the exact results 
  // are displayed as a line
  int tempResFact=10;

  // temoral resolution for exact solution (decay of velocity)
  const double dt_exact=timeInterval/tempResFact;
  
  // simulation time
  const double simuTime=fileCounter*timeInterval; 
  // vector array to save (t, U_max) for different times
  vector < vector <double> > U_max_exact;
  for(int i=0;i*dt_exact<simuTime;i++) {
    const double time=i*dt_exact;
    const double U_max=U*exp(b*time);
    vector <double> couple_t_Umax(2,0);
    couple_t_Umax[0]=time;
    couple_t_Umax[1]=U_max;
    U_max_exact.push_back(couple_t_Umax);
  }

  // control output
  cout<<"size of U_max_exact: "<<U_max_exact.size()<<endl;

  const string outputfile = "../../results/ResultsInProgress/decayAnalysis.dat";
  
  // create and open outputfile
  ofstream out(outputfile.c_str());
  if (!out){
    cout<<"Initialtion: Cannot create "<<outputfile <<"! \n";
    exit(1);
  }
  else cout<<"\n writing the velocity decay data into "<< outputfile <<" \n"; 
  
  // write data into file (4 columns)
  // file structure: (time|exact Max Velocity| simu Max Velocity|rel. Error) 
  int j=0; // parameter for output of data in files (to synchronize the simulated with the exact data (iterator for maxVelocity (Simulated) vector)

  for(int i=0;i< U_max_exact.size();i++){
    //cout <<i<<endl;
    // following a little construction that allows for conditional output
    // of the 3. column value (either the numerical value for the
    // max_velocity or "--" if there is novalue for the corresponding time)
    stringstream conditionalOutputVelSS;
    string conditionalOutputVel;
    if ((i+tempResFact)%tempResFact==0 && j<MaxVelocAllInstants.size()) {
      conditionalOutputVelSS<<  MaxVelocAllInstants[j][1] ;
    }
    else 
      conditionalOutputVelSS<<"--";
    // convert stringstream to string
    conditionalOutputVel=conditionalOutputVelSS.str();

    // same conditional output operations for the 4. column (rel. error)
    stringstream conditionalOutputErrSS;
    string conditionalOutputErr;
    if ((i+tempResFact)%tempResFact==0 && j<MaxVelocAllInstants.size()) {
      conditionalOutputErrSS<< fabs( (U_max_exact[i][1]-MaxVelocAllInstants[j][1])/U_max_exact[i][1]);
      j++;
      //cout<<"j incremented to: "<<j<<endl;
    }
    else 
      conditionalOutputErrSS<<"--";
    // convert stringstream to string
    conditionalOutputErr=conditionalOutputErrSS.str();
        
    // write into file
    // (time | exact Max Velocity | simu Max Velocity | rel. Error)
    out<<setprecision(9)
       << ::setw(17)<<U_max_exact[i][0]
       << ::setw(17)<<U_max_exact[i][1]
       << ::setw(17) <<conditionalOutputVel
       << ::setw(17) <<conditionalOutputErr
       <<"\n";
    
    
    
  }
  out.close();// close outputfile
  cout<<"\n file successfully written \n";// user output

return 0;
}
