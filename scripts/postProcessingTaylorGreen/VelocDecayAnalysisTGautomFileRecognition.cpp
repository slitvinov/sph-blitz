

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <math.h>
//#include <boost/regex.hpp> // to compare filenames with desired format
#include <boost/filesystem.hpp> // to iterate all files of directory

using namespace std;

int main (){

  int n_col=11;// number of columns in inputfile (for SPLASH-optim. output)
  int counter=0;
  vector<double> row(n_col,0);//variable for one row of data file
  vector <vector <double> > inputFileData; // stores data read from inputfile
  vector <vector <double> > MaxVelocAllInstants;// 2D vector for max velocities of all instants and their corresponding time value
  vector <double>maxVelThisInstAndTime(2,0);//vector for max velocities of ONE instant and  corresponding time value
  int fileCounter=0;// counter for number of read files
    
  //iterare all files in the specified directory and store the name of all
  // files that correspond to output-files

  const std::string target_path( "../../src/outdata/");// specify directory
  // const boost::regex filter( "prtl.*\.dat" );// filter to detect prtlXXXXXXXX.dat-files
  
  // string-vector for names of all matching files (files that are to be read)
  std::vector< std::string > all_matching_files;
  
  boost::filesystem::directory_iterator end_itr; // Default ctor yields past-the-end
  //iterate all files in directory
  for( boost::filesystem::directory_iterator i( target_path ); i != end_itr; ++i )
    {
      // Skip if not a file
      // if( !boost::filesystem::is_regular_file( i->status() ) )// continue;
      
      // boost::smatch what;
      
      // // Skip if no match
      // if( !boost::regex_match( i->leaf(), what, filter ) ) continue;
      
      // File matches, store it
      all_matching_files.push_back( i->leaf() );
    }
  
  //
 
  // WHILE LOOP OVER ALL FILES (that have been identified just above)
  for(int i=0;i<all_matching_files.size();i++) {
    // max velocity of current instant(=output time)
    double maxVelocThisInstant=-10000;    
    string inputfile=all_matching_files[i];//assign filename
        
    // extract time from filename:
    //    format of the inputfile name xxxx/x...x12345678.dat,
    //    where 12345678 time in ms
    size_t length;
    char timeString[20];
    // cut the string containing the time off
    length=inputfile.copy(timeString,8,inputfile.size()-12);
    timeString[length]='\0';// add the end string sign
    cout << "time is (string) " << timeString << "\n";// test output
    // convert string into an integer using a stringstream
    stringstream ss(timeString); 
    int time;// time in ms
    double t;// time in s
    ss >> time;// 
    t=time/1e6;//convert time from ms to s
    
    //control output
    cout<<"currently processed file is: "<<inputfile;
    cout << "time for currently processed file is( in s) " << t << "\n";
    
    // create and open inputfile
    ifstream fin(inputfile.c_str(), ios::in);
    // test if inputfile opened, if not try different filename
    if (!fin) {
      
      cout<<"file "<<inputfile<<" could not be opened"<<endl;
      break;
    }
    
    // WHILE_LOOP TO READ ALL ENTRIES OF A SINGLE INPUTFILE (=one instant)
    // and calc max. velcity for this instant
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
	fin>>row[i];
	
      }
      
      // IF the row does not correspond to a boundary particle
      // (for which ID=0):
      // calculate velocity for this row (=this particle) and 
      // save is as max for this instant if bigger than previous max.
      //
      // the different rows in the underlying simulation data-
      // file are (in SPLASH-optimized output-format)
      // x | y | Ux | Uy | rho | e | p | h=supportlength/2 | m | V | ID    
      if(row[10]!=0) {
	// determine max velocity this instant
	const double velocity=sqrt(pow(row[4],2)+pow(row[9],2));
	if (velocity>maxVelocThisInstant)
	  maxVelocThisInstant=velocity;
      }
    } 
    //END OF WHILE- LOOP TO READ SINGLE INPUTFILE 
    fin.close();// close inputfile
    
    // pair maximum velocity of this instant with corresponding time (in sec):
    maxVelThisInstAndTime[0]=maxVelocThisInstant;
    maxVelThisInstAndTime[1]=t;
    // store max velocity this instant(incl. time) in an array/vector
    MaxVelocAllInstants.push_back(maxVelThisInstAndTime);
    // increment file counter as loop will restart for next input file
    fileCounter++;  
  }
  // END OF WHILE LOOP OVER ALL FILES
  
  // calculate exact solution (theoretical decay) in
  // the interval t=0 bis t=t_simulation (
  
  // variables needed for computation of exact solution 
  // (exact solution taken from  HuAdams07 and Chaniotis2002)
  const double gamma=1.4;
  const double M_ref=0.5;
  const double p_ref=1/(gamma*pow(M_ref,2));
  const double U=0.04;
  double Re;
  const double PI=3.14159265358979323846;
  const double b=(-8*pow(PI,2)/Re);
  cout<<"enter the Reynolds-number of the simulation: ";
  cin>>Re;
  
  // temporal resolution of evaluated points higher 
  // (by a factor tempResFact) than for simulation results 
  // (this is due to plotting-reasons, as the exact results 
  // are displayed as a line
  const int tempResFact=10;

  // simulation time (=time of last simulation-data-output-file)
  const double simuTime=MaxVelocAllInstants[MaxVelocAllInstants.size()-1][1];  

  // temporal resolution for exact solution (decay of velocity)
  const double dt_exact=simuTime/(fileCounter*tempResFact);
 
  // vector array to save (t, U_max) for different times
  vector < vector <double> > U_max_exact;
  for(int i=0;i*dt_exact<simuTime;i++) {
    const double time=i*dt_exact;
    const double U_max=U*exp(b*time);
    vector <double> couple_t_Umax(2,0);
    couple_t_Umax[0]=U_max;
    couple_t_Umax[1]=time;
    U_max_exact.push_back(couple_t_Umax);
  }

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

//while-loop for output
 double timeForOutput=0;// variable designating the current output-time
 int iter_exact=0;// iterator for exact solution vector
 int iter_simData=0;// iterator for simulation data vector
 while(timeForOutput<simuTime){
   // file structure for output-file:
   // (time | exact Max Velocity | simu Max Velocity | rel. Error)
   //
   // 3rd and 4th column may be ommitted if no simulation data available
   // (as temporal resolution for exact solution higher due to plotting reasons

   // in outputfile: the simulation data have to be written at the right
   // places between the exact solution data 
   // (depending on their respective times)

   // time of currently considered exact solution
   const double t_currExact=U_max_exact[iter_exact][1]; 
   // time of currently considered simulation data
   const double t_currSimData=MaxVelocAllInstants[iter_simData][1];

   if(t_currExact==t_currSimData)// print exact results + simu-data in same column
     out<<setprecision(9)
	<< ::setw(17)<<U_max_exact[iter_exact][1]
	<< ::setw(17)<<U_max_exact[iter_exact][0]
	<< ::setw(17) <<MaxVelocAllInstants[iter_simData][0]
	<< ::setw(17) <<fabs((U_max_exact[iter_exact][0]-MaxVelocAllInstants[iter_simData][0])/U_max_exact[iter_exact][0])
	<<"\n";
   else if(t_currExact<t_currSimData)// print exact. results only
     out<<setprecision(9)
	<< ::setw(17)<<U_max_exact[iter_exact][1]
	<< ::setw(17)<<U_max_exact[iter_exact][0]
	<< ::setw(17) <<"--"
	<< ::setw(17) <<"--"
	<<"\n";
   else// print simu-data (and calc&print exact results at this instant as well)
     out<<setprecision(9)
	<< ::setw(17)<<t_currSimData
	<< ::setw(17)<<U*exp(b*t_currSimData)
	<< ::setw(17) <<MaxVelocAllInstants[iter_simData][0]
	<< ::setw(17) <<fabs((U*exp(b*t_currSimData)-MaxVelocAllInstants[iter_simData][0])/U*exp(b*t_currSimData))
	<<"\n";
 }
 out.close();// close outputfile
 cout<<"\n file: "<<outputfile<<" successfully written \n";// user output

return 0;
}
