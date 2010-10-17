
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
  
  int n_col=11;// number of columns in inputfile (11 for SPLASH optimized output)
  double dx_exact=0.005; // dx for exact solution (exactxxxxxxxxxxxx.dat) for plotting
 
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


  // ------------read input file----------------------

  string garbage; // string for first 2 lines of inout file

  // data structure for an image of file content
  vector <vector <double> > simulationData;//data structure for an image of file content
  
  // first particles y value (see README, to ensure that only 1 row
  // of particles is read as particle distribution is 2D)
  double first_prtl_y;

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
    // save first REAL (ID!=0) particle's y (see README, to ensure that only 1 row
    // of particles is read, as particle distribution is 2D)
    if(firstRowSwitch==0&&row[10]!=0) {
      first_prtl_y=row[1];
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
    // AND if this row's y is the same as first particles( rows) y
    // add it to the matrix vector
    if(row[n_col-1]!=0&&first_prtl_y==row[1]) {
      simulationData.push_back(row);
    }
  }  
  fin.close();// close file
  cout<<endl<<"file read!"<<endl;
  
  // calculate exact solution at all particle positions (needed for norm calculation)
  // exact solution is: analytical solution for 2 semi infinite bodies
  // (taken from Cleary1999, NO from )

  const double k=1; // thermal conductivity
  const double c_v=1; // heat capacity
  const double rho=1000;// density of material 
  const double alpha=k/(rho*c_v);// thermal diffusivity 
  const double x_m=0.5;// x-value of temperature jump in slab
  const double T_l=0;// initial temperature LHS
  const double T_r=1;// initial temperature RHS
  // const double T_c=(T_l+T_r)/2; // temperature at center ("contact surface")
  vector <double> one_x_T_couple(2,0);
  // vector for all (x,T) couples
  vector <vector <double> > all_x_T_couples;

  //variable for energy content (to check its conservation over time)
  double energy_content=0;
  for (int i=0;i<simulationData.size();i++) {
    const double x= simulationData[i][0];// extract x (is more handy for the rest)
    double T;
    if(x<=x_m)// has to be lower/equal as it was used the same in initialization file
      T=0.5*T_r*(1-erf((x_m-x)/(2.0*sqrt(alpha*t)+1e-35)));
    else
      T=0.5*T_r*(1+erf((x-x_m)/(2.0*sqrt(alpha*t)+1e-35)));
    one_x_T_couple[0]=x;
    one_x_T_couple[1]=T;
    // append current x,T couple to  all_x_T_couples 2D array
    all_x_T_couples.push_back(one_x_T_couple);

    // in the sams loop: calculate energy content by summing all sinulated Ts(=energies)
    // for the particles and normalizing with n particles (later outside of loop)
    energy_content=energy_content+simulationData[i][5];
  }
  //divide energy content by number of particles 
  energy_content= energy_content/simulationData.size();
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
    // calculate the point's contribution to the norm
    N_part++;// increment number of particles in the domain
    // calculate delta between exact and simu
    const double delta_T=fabs( all_x_T_couples[i][1]-simulationData[i][5]);
    // calculate L_1 norm contribution (add contribution to norm)
    L_1Norm=L_1Norm+delta_T;
    // calculate L2 norm contributions (add contribution to norm)
    L_2Norm=L_2Norm+pow(delta_T,2);
    
    // calculate Linf norm (=maximum value)
    if(delta_T>L_infNorm)
      L_infNorm=delta_T;
  }
  //divide final results (except for L_inf norm) by the number of particles in the domain
  L_1Norm=L_1Norm/N_part;
  L_2Norm=L_2Norm/N_part;
  
  //for L_2 norm: sqrt (according to definition)
  L_2Norm=sqrt(L_2Norm);
  
  // and finally normalize them with characteristic value which is 
  // (choice not unique): T_r (initial temperature of the high temperature side)
  L_1Norm=L_1Norm/T_r;
  L_2Norm=L_2Norm/T_r;
  L_infNorm= L_infNorm/T_r;
  
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
  
  out4<<setprecision(6)
      << L_1Norm<<" "<< L_2Norm<<" "<< L_infNorm <<endl<<endl;
  // also output energy content in same file
  out4<<" energy content represented by=1/N_i*sum(e_i): "<<setprecision(6)<<energy_content<<endl;
  
  // close output file
  out4.close();
  
  cout<<"\n norm error file successfully written \n";
  
 const string filename3 = "../../results/ResultsInProgress/simuForPlot" +timestamp + ".dat";
 // besides output simulation data (only one particle row) in a file for plotting
  ofstream out3(filename3.c_str());
  if (!out3){
    cout<<"Initialtion: Cannot create "<<filename3 <<"! \n";
    exit(1);
  }
  else cout<<"\n writing simu (x,T) data into "<< filename3 <<" \n"; 
  
  // write file header
  out3<<"extracted simu data (only one row of particles\n";
  out3<<"file structure:\n";
  out3<<"  x  |  T  "<<endl<<endl;
  for (int k=0;k< simulationData.size();k++) {
  out3<<setprecision(6)
      << simulationData[k][0] <<" "<< simulationData[k][5]<<" "<<"\n";
  }
  // close output file
  out3.close();
  
  cout<<"\n file with extracted simu data (x,T) for plotting successfully written \n";
  
  
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
  // file structur:  x, T_exact
  for(double x_exact=0;x_exact<1.0+dx_exact;x_exact=x_exact+dx_exact){
    double T_exact;  
    if(x_exact<=x_m)      
      T_exact=0.5*T_r*(1-erf((x_m-x_exact)/(2.0*sqrt(alpha*t)+1e-35)));
      //had troublw with erf(abs(x_exact-x_m)... gave wrong results!!!
    
    else 
      T_exact=0.5*T_r*(1+erf((x_exact-x_m)/(2.0*sqrt(alpha*t)+1e-35)));
    
    out<<setprecision(9)
       << ::setw(17)<<x_exact// output x value 
       << ::setw(17)<<T_exact //output corresponding T-value
       <<"\n";
  }
  out.close();// close outputfile
  cout<<"\n file successfully written \n";// user output
  
  return 0;
}
