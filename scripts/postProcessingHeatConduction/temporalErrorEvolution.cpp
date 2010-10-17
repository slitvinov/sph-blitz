
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
  // vector that will contain the calculated error data for all instants
  vector < vector < double > > TimeAndErrorNormsAllInstants;
  
  // user input: output time interval of simulation:
  cout<<" please enter output time interval (as specified in .tcl file)"<<endl;
  double timeInterval;
  cin>>timeInterval;

  // initialize file counter
  double fileCounter=0;
  
  
  // while loop over all output intervall values
  for(;;) {
    
    // little passage to find and create good inputfile-name
    
    // assemble input file name
    stringstream number;//string for number (time stamp)
    stringstream number2;//string for second time stamp if first one not o.k.
    stringstream number3;//string for second time stamp if second one not o.k.
    // calculate number (time stamp) for file name
    // needs to be casted to int as otherwise numbers over1,000,000 
    // have the format 1e+6 which is not ok for the file name
    number << setw(12) << setfill('0') <<(int)(fileCounter*timeInterval*1000000);
    const string inputfile = "../../src/outdata/prtl" + number.str() + ".dat";
    cout<<endl<<"trying "<<inputfile<<endl;
    
    // create and open inputfile
    ifstream fin(inputfile.c_str(), ios::in);
    // test if inputfile opened, if not try different filename
    if (!fin) {
      // this is as sometimes filenames are...999 instead of ..0000
      // because time value is truncated (not  for timestamp of file name...
      number2 << setw(12) << setfill('0') <<(int)(fileCounter*timeInterval*1000000-1);
      const string inputfile2 = "../../src/outdata/prtl" + number2.str() + ".dat";
      cout<<endl<<"trying "<<inputfile2<<endl;
      // assign a new filename to the streaming object
      fin.open(inputfile2.c_str(), ifstream::in);
      // test if inputfile opened, if not try different filename
      if (!fin) {
	// this is as sometimes, when entering e.g.0.8673, program 
	// stores 0.867299999... and therefore constructs the wrong filename:
	number3 << setw(12) << setfill('0') <<(int)(fileCounter*timeInterval*1000000+1);
	const string inputfile3 = "../../src/outdata/prtl" + number3.str() + ".dat";
	cout<<endl<<"trying "<<inputfile3<<endl;
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
    
    //time of current input file 
    const double time =fileCounter*timeInterval;
    cout << "time of currently read file is in s " << time << "\n";
        
    string garbage; // string for first 2 lines of inout file
    
    // data structure for an image of file content
    vector <vector <double> > simulationData;//data structure for an image of file content
    
    // first particles y value (see README, to ensure that only 1 row
    // of particles is read as particle distribution is 2D)
    double first_prtl_y;
    
    vector<double> row(n_col,0);// vector to save a whole row
    // throw away first 2 lines of input file (contain no data, only text)
    // row_counter (counts rows of inputfile, its only purpose is to identify 1sr row) 
    int counter=0;
    getline(fin,garbage);
    getline(fin,garbage);
    // read rest of file
    while(!fin.eof()){
      // read one row (problem reads one row more than eof)
      for (int i=0; i<n_col;i++){
	fin>> row[i];
      }
      // save first particles y (see README, to ensure that only 1 row
      // of particles is read, as particle distribution is 2D)
      if(counter==0)
	first_prtl_y=row[1];
      counter++;
      
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
	T=0.5*T_r*(1-erf((x_m-x)/(2.0*sqrt(alpha*time)+1e-35)));
      else
	T=0.5*T_r*(1+erf((x-x_m)/(2.0*sqrt(alpha*time)+1e-35)));
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
    
    
    
    // write couple (time,L_1,L_2,L_inf) in one variable
    vector < double  > TimeAndErrorNormsOneInstant(4,0); //initialize with zero
    TimeAndErrorNormsOneInstant[0]=time;
    TimeAndErrorNormsOneInstant[1]=L_1Norm;
    TimeAndErrorNormsOneInstant[2]=L_2Norm;
    TimeAndErrorNormsOneInstant[3]=L_infNorm;
    
    // add couple (time,L_1,L_2,L_inf) to gobal variable
    // for all couple (time,L_1,L_2,L_inf)
    TimeAndErrorNormsAllInstants.push_back(TimeAndErrorNormsOneInstant);
    
    //increment file-counter
    fileCounter++;    
  }
  // end of loop over all input files
  
  // output the results in files
  
  // output file: global errors (norms)
  
  // assemble filename
  const string filename = "../../results/ResultsInProgress/tempErrEvolution.dat";
  
  // create and open outputfile
  ofstream out(filename.c_str());
  if (!out){
    cout<<"Initialtion: Cannot create "<<filename <<"! \n";
    exit(1);
  }
  else cout<<"\n writing norm error data into "<< filename <<" \n"; 
  
  // write file header
  out<<"temporal evolution of norm errors\n\n";
  out<<" t  |  L1  |  L2  |  L_oo"<<endl<<endl;
  //write data
  for (int i=0;i<TimeAndErrorNormsAllInstants.size();i++)
    out<<setprecision(6)
       << TimeAndErrorNormsAllInstants[i][0]<<" "
       << TimeAndErrorNormsAllInstants[i][1]<<" "
       << TimeAndErrorNormsAllInstants[i][2]<<" "
       << TimeAndErrorNormsAllInstants[i][3]<<endl;
  
  // close output file
  out.close();
  
  cout<<"\n file <<tempErrEvolution.dat>> successfully written \n";
  return 0;
}
