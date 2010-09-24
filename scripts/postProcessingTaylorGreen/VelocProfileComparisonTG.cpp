

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

  int n_col=0;// number of columns in inputfile
  double buffer;
  vector<double> row(n_col,0);
  vector <vector <double> > inputFileData; // stores data read from inputfile
 
  cout<<"\n"<<"please enter the number of columns in the input file:  ";
  cin>>n_col;

  //create file name for inputfile (=simulation result file prtlXXXXXXXX.dat)
  string prefix("../../src/outdata/prtl");
  string suffix(".dat");
  string timestamp;
  // read timestamp from user
  cout<<"Please enter the time stamp (8 digits) of the file to post-process";
  cin>> timestamp;  
  // assemble file name
  inputfile=prefix +timestamp+suffix;

  // convert the timestamp-srting into a number
  stringstream ss(timestamp); 
  int time;// time in ms
  double t;// time in s
  ss >> time;// 
  cout << "time is (int) in ms " << time << "\n";
  t=time/1e6;//convert time from ms to s
  cout << "time is (int) in s " << t << "\n";


 
  // read simulation result data from file and save it in 2D-vector
  // simulation data (maintaining the same structure(rows/columns) as in file
  
  // 2D vector to save content of read file
  vector <vector <double> > simulationData;
  
  //open the file
  ifstream fin3(inputfile.c_str(), ios::in);
  buffer=0;//initialize the buffer variable
  vector<double> row(n_col,0);// vector to save a whole row
  // throw away first to lines of input file
  getline(fin3,garbage);
  getline(fin3,garbage);
  //read rest of file
  while(!fin3.eof()){
    // read every row
    for (int i=0; i<n_col;i++){
      //problem: reads always one more than eof
      fin3>>buffer;
      row[i]=buffer; 
    }
    //append every row to 2D array (matrix) simulationData
    simulationData.push_back(row);
    
  }  
  //  need to remove last row (as it reads one more row than physically contained in the file!?!)
  simulationData./ 
  fin3.close();// close file

  
  // calculate exact solution (theoretical decay)
  
  // variables needed for computation of exact solution
  const double gamma=1.4;
  const double M_ref=0.5;
  const double p_ref=1/(gamma*pow(M_ref,2));
  const double U=0.04;
  const double Re=100;
  const double PI=3.14159265358979323846;
  const double b=(-8*pow(PI,2)/Re);
  
  // temporal resolution of evaluated points higher (by a factor tempResFact) than
  // for simulation results (this is due to plotting-reasons, as the exact results 
  // are displayed as a line
  const int tempResFact=10;

  // temoral resolution for exact solution (decay of velocity)
  const double dt_exact=timeInterval/tempResFact;
  
  // simulation time
  const double simuTime=(fileCounter+1)*timeInterval; // "+1" as outputfiles start at t=0
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

    // following a little construction that allows for conditional output
    // of the 3. column value (either the numerical value for the
    // max_velocity or "--" if there is novalue for the corresponding time)
    stringstream conditionalOutputVelSS;
    string conditionalOutputVel;
    if ((i+tempResFact)%tempResFact==0) {
      conditionalOutputVelSS<<  MaxVelocAllInstants[j][0] ;
    }
    else 
      conditionalOutputVelSS<<"--";
    // convert stringstream to string
    conditionalOutputVel=conditionalOutputVelSS.str();

    // same conditional output operations for the 4. column (rel. error)
    stringstream conditionalOutputErrSS;
    string conditionalOutputErr;
    if ((i+tempResFact)%tempResFact==0) {
      conditionalOutputErrSS<<  (U_max_exact[i][0]-MaxVelocAllInstants[j][0])/U_max_exact[i][0];
      j++;
    }
    else 
      conditionalOutputErrSS<<"--";
    // convert stringstream to string
    conditionalOutputErr=conditionalOutputErrSS.str();
        
    // write into file
    // (time | exact Max Velocity | simu Max Velocity | rel. Error)
    out<<setprecision(9)
       << ::setw(17)<<U_max_exact[i][0]
       << ::setw(17)<<U_max_exact[i][0]
       << ::setw(17) <<conditionalOutputVel
       << ::setw(17) <<conditionalOutputErr
       <<"\n";
    
    // increment iterator
    if((i+tempResFact)%tempResFact==0)
      j++;
    
  }
  out.close();// close outputfile
  cout<<"\n file successfully written \n";// user output

return 0;
}
