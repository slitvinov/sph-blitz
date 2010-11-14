
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

  // parameters for eact solution
  const double k=1; // thermal conductivity
  const double c_v=1; // heat capacity
  const double rho=1000;// density of material 
  const double alpha=k/(rho*c_v);// thermal diffusivity 
  const double T_0=0;// initial temperature domain
  const double T_w=1;// temperature of wall (isothermal BC)
  
  int n_col=11;// number of columns in inputfile (11 for SPLASH optimized output)
  double dy_exact=0.005; // dy for exact solution (exactxxxxxxxxxxxx.dat) for plotting
 
  //read filestamp from user
  cout<<"Please enter the file stamp (12 digits) for the file of which the exact result should be calculated:\n ";
  string timestamp;//intermediate variable for timestamp user input
  cin>>timestamp;
  // string containing input-file name
  const string inputfile = "../../src/outdata/prtl" + timestamp + ".dat";

  // convert timestamp-string into an integer using a stringstream
    stringstream ss(timestamp); //define stringstream
  int time;// time in ms
  double t;// time in s
  ss >> time;// stream stringstream into int variable 
  cout << "time is (int) in ms " << time << "\n";
  t=time/1e6;//convert time from ms to s
  cout << "time is (int) in s " << t << "\n";

  // read y position of isothermal wall (so y-values of simu can be translated
  // as exact solution assumes y_wall=0)
  cout<<"enter y-position of isothermal wall: ";
  double y_wall;
  cin>>y_wall;

  // ------------read input file----------------------

  string garbage; // string for first 2 lines of input file

  // data structure for an image of file content
  vector <vector <double> > simulationData;//data structure for an image of file content
  
  // first particles x value (see README, to ensure that only 1 row
  // of particles is read as particle distribution is 2D)
  double first_prtl_x;

  // read inputfile and save content
  // (without boundary particles, their ID is 0) in simulationData
  // (maintaining the file-structure) 
  ifstream fin(inputfile.c_str(), ios::in);
  if (!fin){
    cout<<"Initialtion: Cannot open "<< inputfile <<"! Restart program and try different file name \n";
    exit(1);
  }
  else cout<<"Starting the extraction of the file content "<< inputfile <<" \n"; 

  vector<double> row(n_col,0);// vector to save a whole row
  // throw away first 2 lines of input file (contain no data, only text)

  // first real particle row indicator 
  // only purpose is to identify 1st row of real particles (NO boundary particles) 
  // 0 at start, 1 once first real particle row is reached
  int firstRowSwitch =0;
  getline(fin,garbage);
  getline(fin,garbage);
  // read rest of file
  while(!fin.eof()){
    // read one row (problem reads one row more than eof)
    for (int i=0; i<n_col;i++){
      fin>> row[i];
    }
    // save first REAL (ID!=0) particle's x (see README, to ensure that only 1 row
    // of particles is read, as particle distribution is 2D)
    if(firstRowSwitch==0&&row[10]!=0) {
      first_prtl_x=row[0];
      firstRowSwitch++;
    }    
    // append every row to 2D array (matrix) simulationData
    // if this row does not correspond to a boundary particle for which ID=0
    // AND if this row's y is the same as first particles( rows) y
    // to be sure the last row (which is already eof and does
    // not correspond to a physical row of the file any more)
    // is not added: set last row's ID=0;
    // file structure: x, y, Ux, Uy, rho, e, p, h, m, V, ID 
    if(fin.eof()) {
      row[n_col-1]=0;
    }
    // if the row does not correspond to a boundary particle
    // (for which ID=0)
    // AND if this row's x is the same as first particles( rows) x
    // add it to the matrix vector
    if(row[n_col-1]!=0&&first_prtl_x==row[0]) {
      simulationData.push_back(row);
    }
  }  
  fin.close();// close file
  cout<<endl<<"file read!"<<endl;
  
  // calculate exact solution at all particle positions (needed for norm calculation)
  // exact solution is: analytical solution for 2 semi infinite bodies
  // (taken from Cleary1999, NO from different source (see thesis)
  // Ccleary was not working... )

  //variable to store one (y,T) couple
  vector <double> one_y_T_couple(2,0);
  // vector for all (y,T) couples
  vector <vector <double> > all_y_T_couples;

  //variable for energy content (to check its conservation over time)
  double energy_content=0;
  for (int i=0;i<simulationData.size();i++) {
    // extract y and translate it so that y_wall = 0 for exact solution
    const double y= simulationData[i][1]-y_wall;
    double T;
    
    T=T_w+erf((y)/(2.0*sqrt(alpha*t)+1e-35))*(T_0-T_w);
    one_y_T_couple[0]=y;
    one_y_T_couple[1]=T;
    // append current y,T couple to  all_y_T_couples 2D array
    all_y_T_couples.push_back(one_y_T_couple);
  }
  cout<<endl<<"exact results calculated"<<endl;

  // L norm calculation
  
  // variables for norms
  double L_1Norm=0;
  double L_2Norm=0;
  double L_infNorm=0;
  
  int N_part=0;//number of particles
  
  //actual norm calculation
  
  // iterate all rows of simulation data matrix(=file)
  for(int i=0;i<simulationData.size();i++) {
    //take into account only area to 0.5 as beyond solution not valid any more
    // (calculation domain is symmetrical to 0.5)
    if(simulationData[i][1]-y_wall<=0.5) {
      // calculate the point's contribution to the norm
      N_part++;// increment number of particles in the domain
      // calculate delta between exact and simu
      const double delta_T=fabs( all_y_T_couples[i][1]-simulationData[i][5]);
      // calculate L_1 norm contribution (add contribution to norm)
      L_1Norm=L_1Norm+delta_T;
      // calculate L2 norm contributions (add contribution to norm)
      L_2Norm=L_2Norm+pow(delta_T,2);
      
      // calculate Linf norm (=maximum value)
      if(delta_T>L_infNorm)
	L_infNorm=delta_T;
    }
  }
  //divide final results (except for L_inf norm) by the number of particles in the domain
  L_1Norm=L_1Norm/N_part;
  L_2Norm=L_2Norm/N_part;
  
  //for L_2 norm: sqrt (according to definition)
  L_2Norm=sqrt(L_2Norm);
  
  // and finally normalize them with characteristic value which is 
  // T_w (isothermal wall temperature)
  L_1Norm=L_1Norm/T_w;
  L_2Norm=L_2Norm/T_w;
  L_infNorm= L_infNorm/T_w;
  
  cout<<endl<<"norms calculated"<<endl;  
  
  // output the results in files
  
  // output file: global errors (norms)
  
  // assemble filename
  const string filename2 = "../../results/ResultsInProgress/ErrorNorms" + timestamp + ".dat";
  
  // create and open outputfile
  ofstream out4(filename2.c_str());
  if (!out4){
    cout<<"Initialtion: Cannot create "<<filename2 <<"! \n";
    exit(1);
  }
  else cout<<"\n writing norm error data into "<< filename2 <<" \n"; 
  
  // write file header
  out4<<"norm errors\n\n";
  out4<<" L1  |  L2  |  L_oo"<<endl<<endl;
  //write L error data
  out4<<setprecision(6)
      << L_1Norm<<" "<< L_2Norm<<" "<< L_infNorm <<endl<<endl;
    
  // close output file
  out4.close();
  
  cout<<"\n norm error file successfully written \n";
  
  // besides output simulation data (only one particle row) in a file for plotting 
 const string filename3 = "../../results/ResultsInProgress/simuForPlot" +timestamp + ".dat";
 ofstream out3(filename3.c_str());
  if (!out3){
    cout<<"Initialtion: Cannot create "<<filename3 <<"! \n";
    exit(1);
  }
  else cout<<"\n writing simu (y,T) data into "<< filename3 <<" \n"; 
  
  // write file header
  out3<<"extracted simu data (only one row of particles\n";
  out3<<"file structure:\n";
  out3<<"  y  |  T  "<<endl<<endl;
  for (int k=0;k< simulationData.size();k++) {
  out3<<setprecision(6)
      << simulationData[k][1]-y_wall <<" "<< simulationData[k][5]<<" "<<"\n";
  }
  // close output file
  out3.close();
  
  cout<<"\n file with extracted simu data (y,T) for plotting successfully written \n";
  
  // besides output file with exact solution which can be used for plotting purposes
  // assemble output file name 
  const string outputfile = "../../results/ResultsInProgress/exact" +timestamp + ".dat";
  
  // create and open outputfile
  ofstream out(outputfile.c_str());
  if (!out){
    cout<<"Initialtion: Cannot create "<<outputfile <<"! \n";
    exit(1);
  }
  else cout<<"\n writing the exact solution into "<< outputfile <<" \n"; 
  
  //write data into file (2 columns)
  // file structur:  y, T_exact
  for(double y_exact=0;y_exact<0.5+dy_exact;y_exact=y_exact+dy_exact){
    double T_exact;  
    // calculate exact solutioon at this point
    T_exact=T_w+erf((y_exact)/(2.0*sqrt(alpha*t)+1e-35))*(T_0-T_w);
    //print position and exact solution
    out<<setprecision(9)
       << ::setw(17)<<y_exact// output y value 
       << ::setw(17)<<T_exact //output corresponding T-value
       <<"\n";
  }
  out.close();// close outputfile
  cout<<"\n file successfully written \n";// user output
  
  return 0;
}
