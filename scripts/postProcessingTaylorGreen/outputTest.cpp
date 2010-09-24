

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

  const string outputfile = "decayAnalysis.dat";
  const int flag=1;
  const double drei=3.422342;
  const int vier=4;
  
  // create and open outputfile
  ofstream out(outputfile.c_str());
  if (!out){
    cout<<"Initialtion: Cannot create "<<outputfile <<"! \n";
    exit(1);
  }
  else cout<<"\n writing the velocity decay data into "<< outputfile <<" \n"; 
  
  //write data into file (4 columns) (time|exact Max Velocity| simu Max Velocity|rel. Error)
  stringstream conditionalOutputSS;
  string conditionalOutput;
  if (flag==1)
    conditionalOutputSS<< drei;
  else 
    conditionalOutputSS<<"4";
  conditionalOutput=conditionalOutputSS.str();
    out<<setprecision(9)
       << ::setw(17)<<"1"
       << ::setw(17)<<"2" //y coordinate (no relevance), just to maintain file structure
       << ::setw(17) <<conditionalOutput
       <<"\n";
  
  out.close();// close outputfile
  cout<<"\n file successfully written \n";// user output
 
  return 0;
}
