
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
  
  const int n_col=11;// number of columns in inputfile (11 for SPLASH optimized output)
  int fileCounter=0;// to count number of read input-files
  // 2D vector containing energy_content and respective time for all instants
  // format: (t, energy)
  vector < vector < double > > TimeAndEnergyAllInstants;

  // user input: output time interval of simulation:
  cout<<" please enter output time interval (as specified in .tcl file)"<<endl;
  double timeInterval;
  cin>>timeInterval;
  
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
    // 2D vector that will contain the data of the read input-file
    vector <vector < double > >	simulationData;        
    
    // variable to discard the two first lines of input-file
    string garbage;
    // variable to save first particle's y value (see README, to ensure that only 1 row
    // of particles is read, as particle distribution is 2D)
    double first_prtl_y;
    
    vector<double> row(n_col,0);// vector to save a whole row
    // throw away first 2 lines of input file (contain no data, only text)
    // row_counter (counts rows of inputfile, its only purpose is to identify 1sr row) 
    int counter=0;
    // start reading current input-file and discard first two lines
    getline(fin,garbage);
    getline(fin,garbage);
    // read rest of file (actual data)
    while(!fin.eof()){
      // read one row (problem reads one row more than eof)
      for (int i=0; i<n_col;i++){
	fin>> row[i];
      }
      // save first particle's y value (see README, to ensure that only 1 row
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
    
    
    //variable for energy content of this instant
    double energy_content_this_Instant=0;
    for (int i=0;i<simulationData.size();i++) {
      
      energy_content_this_Instant=energy_content_this_Instant+simulationData[i][5];
    }
    // divide energy content by number of particles 
    energy_content_this_Instant= energy_content_this_Instant/simulationData.size();
    // write couple (time, energy) in one variable
    vector < double  > TimeAndEnergyOneInstant(2,0); //initialize with zero
    TimeAndEnergyOneInstant[0]=time;
    TimeAndEnergyOneInstant[1]=energy_content_this_Instant;
    // add couple (t,energy) to gobal variable for all couples (t,e)
    TimeAndEnergyAllInstants.push_back(TimeAndEnergyOneInstant);
    
    //increment file-counter
    fileCounter++;    
  }
  // end of loop over all input files
  
  const string filename= "../../results/ResultsInProgress/energyContentEvolution.dat";
  // create and open outputfile
  ofstream out(filename.c_str());
  if (!out){
    cout<<"Initialtion: Cannot create "<<filename <<"! \n";
    exit(1);
  }
  else cout<<"\n writing energy content data into "<< filename <<" \n";
  
  //writing file header
  out<<" energy content evolution"<<endl;
  out<<" energy content represented by=1/N_i*sum(e_i)"<<endl;
  out<<" file structure: t  |  energy_content"<<endl;
  // output energy content data file
  for (int i=0;i<TimeAndEnergyAllInstants.size();i++) {
    out<<setprecision(6)
       <<TimeAndEnergyAllInstants[i][0]<<"    "
       <<TimeAndEnergyAllInstants[i][1]<<endl;
  }
  
  // close output file
  out.close();
  
  cout<<"\n energy content file successfully written \n";
  
  return 0;
}
