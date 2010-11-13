
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <math.h>
//#include <../../boost/format.hpp>


using namespace std;

int main (){

  int n_col=11;// number of columns in inputfile (11 for SPLASH optimized output)
  //read timestamps from user
  cout<<"Please enter the time stamp (12 digits) of the first file for temporal interpolation:\n ";
  string timestamp1;//intermediate variable for timestamp user input
  cin>>timestamp1;
  cout<<"Please enter the time stamp (12 digits) of the second file for temporal interpolation:\n ";
  string timestamp2;//intermediate variable for timestamp user input
  cin>>timestamp2;
  double t;
  cout<<"enter time for interpolation (in sec)";
  cin>>t;
 
  //read timestamp resolution from user
  double timestamResolution;
  int timestampCode=0;
  while(timestampCode!=1&&timestampCode!=2) { 
    cout<<"Please enter the  timestamp resolution for the simulation:\n ";
    cout<<"Enter 1 for standard resolution (1e-6)\n ";
    cout<<"Enter 2 for high resolution (1e-10)\n ";
    cin>>timestampCode;
    if(timestampCode!=1&&timestampCode!=2)
      cout<<"you should enter eitehr 1 or 2!"<<endl;
  }
  double timestampResolution;
  if(timestampCode==1)
    timestampResolution=1e-6;
  else
    timestampResolution=1e-10;
  
  // string containing input-file name (first file)
  const string inputfile1 = "../../src/outdata/prtl" + timestamp1 + ".dat";

  // string containing input-file name (second file)
  const string inputfile2 = "../../src/outdata/prtl" + timestamp2 + ".dat";

  // convert timestamp-strings into an integer using a stringstream
  stringstream ss1(timestamp1); //define stringstream
  int time1;// time in timestamp unit
  double t1;// time in s
  ss1 >> time1;// stream stringstream into int variable 
  cout << "time 1 is (int) in timestamp unit " << time << "\n";
  t1=time1*timestampResolution;//convert time from ms to s
  cout << "time 1 is  in s " << t << "\n";

 stringstream ss2(timestamp2); //define stringstream
  int time2;// time in timestamp unit
  double t2;// time in s
  ss2 >> time2;// stream stringstream into int variable 
  cout << "time 2 is (int) in timestamp unit " << time << "\n";
  t2=time2*timestampResolution;//convert time from ms to s
  cout << "time 2 is  in s " << t << "\n";

  while (t<t1||t>t2) {
    cout<<" the interpolation time must be between the file 1 and file 2 time!";
    cout<<"please try again:";
    cin>>t;
  }

  // ------------read input files----------------------

  string garbage1; // string for first line of input file
  string garbage2; // string for first line of input file

  // data structure for an image of file content
  vector <vector <double> > simulationData1;//data structure for an image of file content
  // read inputfile and save content
  ifstream fin1(inputfile1.c_str(), ios::in);
  if (!fin1){
    cout<<"Initialtion: Cannot open "<< inputfile1 <<"! Restart program and try different file name \n";
    exit(1);
  }
  else cout<<"Starting the extraction of the file content "<< inputfile1 <<" \n"; 
  vector<double> row1(n_col,0);// vector to save a whole row
  // throw away first 2 lines of input file (contain no data, only text)
  getline(fin1,garbage1);
  getline(fin1,garbage2);
  // first real particle row indicator 
  // only purpose is to identify 1st row of real particles (NO boundary particles) 
   // read rest of file
  while(!fin1.eof()){
    // read one row (problem reads one row more than eof)
    for (int i=0; i<n_col;i++){
      fin1>> row1[i];
    }
       
    // append every row to 2D array (matrix) simulationData
    // if this row does not correspond to a boundary particle for which ID=0
    // AND if this row's x is the same as first particles( rows) x.
    // To be sure the last row (which is already eof and does
    // not correspond to a physical row of the file any more)
    // is not added: set last row's ID=0;
    // file structure: x, y, Ux, Uy, rho, e, p, h, m, V, ID 
    if(fin1.eof()) {
      row1[n_col-1]=0;
    }
    simulationData1.push_back(row1);
	
  }  
  fin1.close();// close file
  cout<<endl<<"file 1 read!"<<endl;
  
  //-------read file 2 -------------------------------
 // data structure for an image of file content
  vector <vector <double> > simulationData2;//data structure for an image of file content
  // read inputfile and save content
  
  ifstream fin2(inputfile2.c_str(), ios::in);
  if (!fin2){
    cout<<"Initialtion: Cannot open "<< inputfile2 <<"! Restart program and try different file name \n";
    exit(1);
  }
  else cout<<"Starting the extraction of the file content "<< inputfile2 <<" \n"; 

  vector<double> row2(n_col,0);// vector to save a whole row
  // throw away first 2 lines of input file (contain no data, only text)
  getline(fin2,garbage1);
  getline(fin2,garbage2);
  // first real particle row indicator 
  // only purpose is to identify 1st row of real particles (NO boundary particles) 
   // read rest of file
  while(!fin2.eof()){
    // read one row (problem reads one row more than eof)
    for (int i=0; i<n_col;i++){
      fin2>> row2[i];
    }
       
    // append every row to 2D array (matrix) simulationData
    // if this row does not correspond to a boundary particle for which ID=0
    // AND if this row's x is the same as first particles( rows) x.
    // To be sure the last row (which is already eof and does
    // not correspond to a physical row of the file any more)
    // is not added: set last row's ID=0;
    // file structure: x, y, Ux, Uy, rho, e, p, h, m, V, ID 
    if(fin2.eof()) {
      row2[n_col-1]=0;
    }
    simulationData2.push_back(row2);
  }  
  fin2.close();// close file
  cout<<endl<<"file 2 read!"<<endl;
  
  //create outputfile and corresponding timestamp
  stringstream timestampOutput; //define stringstream
  double outputTime=t/timestampResolution;
  // timestampOutput= boost::str(boost::format("%012d") % static_cast<int>(outputTime));
  
  // timestampOutput<<t/timestampResolution;
  timestampOutput << setw(12) << setfill('0') << (int)outputTime;
  const string outputfile = "../../src/outdata/prtl" + timestampOutput.str() + ".dat";
  // besides output simulation data (only one particle row) in a file for plotting
  ofstream out(outputfile.c_str());
  if (!out){
    cout<<"Initialtion: Cannot create "<<outputfile <<"! \n";
    exit(1);
  }
  else cout<<"\n writing interpolated dataa into "<< outputfile <<" \n"; 
  
  // write file header
  out<<garbage1<<endl;
  out<<garbage2<<endl;
  
  for (int k=0;k< simulationData1.size();k++) {
    for (int m=0;m<n_col;m++) {
	out<<setprecision(6)<<::setw(17) 
	 << simulationData1[k][m]
	+(simulationData2[k][m] -simulationData1[k][m])*(t-t1)/(t2-t1)
	   <<" ";
    }
    out<<endl;
  }
  // close output file
  out.close();
  
  cout<<"\n file successfully written \n";// user output
  return 0;
}
