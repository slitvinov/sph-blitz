

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

int main ()
{
  double supportlength;
  string inputfile;
  int n_col;
  double x_dia;//diaphragm position of simulation shock tube
  vector<double> x_array;
  cout<<"Please enter the name of the input file containing the data for which the exact result should be calculated:\n ";
  cout<<"but this time including the (relative) path:\n";
  cout<<"for 1D particle distribution: ../../src/outdata/prtlxxxxxxxx.dat\n";
  cout<<"for 2D particle distribution: ../../results/ResultsInProgress/averagedxxxxxxxx.dat\n";
  cin>> inputfile;  
  cout<<"\n"<<"please enter the number of columns in the input file:  ";
  cin>>n_col;
  cout<<"\n please enter support length of the simulation: ";
  cin>>supportlength;
  cout<<"\n";

  //format of the inputfile name xxxx/x...x12345678.dat, where 12345678 time in ms

  //extract time from filename:
  size_t length;
  char timeString[20];
    length=inputfile.copy(timeString,8,inputfile.size()-12);
  timeString[length]='\0';
  cout << "time is (string) " << timeString << "\n";
   // convert string into an integer
  stringstream ss(timeString); 
  int time;//time in ms
  double t;//time in s
  ss >> time;
  cout << "time is (int) in ms " << time << "\n";
  t=time/1e6;
  cout << "time is (int) in s " << t << "\n";

  //reading the simulation result data
  ifstream fin(inputfile.c_str(), ios::in);
  if (!fin)
  {
    cout<<"Initialtion: Cannot open "<< inputfile <<"! Restart program and try different file name \n";
    exit(1);
  }
  else cout<<"Starting the extraction of the positons of all particles from "<< inputfile <<" \n"; 


  double buffer;
  int counter=0;

  //very "elegant" way of cutting off first to lines of file
  string garbage;
  getline(fin,garbage);
  getline(fin,garbage);

  while(!fin.eof())
  {
      fin>>buffer;
      if(counter%n_col==0)
	{
	    x_array.push_back(buffer);
	}
      counter++;
        
  }  
  fin.close();
  //remove last element (as last file entry is also written to x_array???)
  x_array.erase(x_array.end()-1);

  //control output for user
  cout<<"\n this is for visual control if the extraction of x values has been successful\n";
  cout<<"First value of the array (should correspond to left hand edge particle position)"<<x_array[0]<<"\n";
cout<<"Last value of the array (should correspond to right hand edge particle position)"<<x_array[x_array.size()-1]<<"\n";


 cout<<"\n please type x coordinate of diaphragm position of the simulation: ";
 cin>>x_dia;

 const double gamma = 1.4;

 const double rho_1=0.125;
 const double p_1=0.1;
 const double u_1=0.0;
 const double e_1=2.0;
 const double a_1=sqrt(gamma*p_1/rho_1);
 cout<<"a_1: "<<a_1;

 const double rho_4=1.0;
 const double p_4=1.0;
 const double u_4=0.0;
 const double e_4=2.5;
 const double a_4=sqrt(gamma*p_4/rho_4);
 cout<<"\n a_4: "<<a_4;
 
//values for exact shock solution: Anderson, Modern compressible flow (third edition) sec: 7.8
//in our case p_4=1 and p_1=0.1 the iterative solution of equation (7.94) anderson for p2 is:

 const double p_2=0.303130178;//obtained with my calculator, did not manage to solve it with maxima
 const double p_3=p_2; //pressure the same over contact discontinuity
 
 //rho_2 with shock relation from state 1
 const double rho_2=rho_1*(1+(gamma+1)/(gamma-1)*(p_2/p_1))/((gamma+1)/(gamma-1)+p_2/p_1);
 cout<<"\n rho_2: "<<rho_2;

 //rho 3 with isentropic relation from state 4 
 const double rho_3=pow((p_3/p_4),1/gamma)*rho_4;
 cout<<"\n rho_3: "<<rho_3;
 //sound speed in area 3
 const double a_3=sqrt(gamma*p_3/rho_3);
 cout<<"\n a_3: "<<a_3;
 //internal energy in 2 and 3
 const double e_2=p_2/(rho_2*(gamma-1));
 const double e_3=p_3/(rho_3*(gamma-1));
 cout<<"\n e_2: "<<e_2;
 cout<<"\n e_3: "<<e_3;

 //velocity behind the wave u_p (=u_2=u_3)
 //first wave velocity of the shock (7.14) Anderson
 const double W=a_1*sqrt((gamma+1)/(2*gamma)*(p_2/p_1-1)+1);
 cout<<"\n shock speed W: "<<W;
 //then induced velocity behind shock wave u_p with (7.15) Anderson
 const double u_p=W*(1-rho_1/rho_2);
 const double u_2=u_p;
 const double u_3=u_p;
 cout<<"\n induced velocity behind shock u_2=u_3= "<<u_3<<"\n";


 //now iterate the position vector and calculate the missing values for each component (=position)

 //vectors for results
 vector<double> p_array(x_array.size(),0);
 vector<double> rho_array(x_array.size(),0);
 vector<double> u_array(x_array.size(),0);
 vector<double> e_array(x_array.size(),0);

 //therefore here: shock tube is centered around x=0 (that is where diaphragm is)
 //if inputfiledata are calculated for a different diaphragm position, values of x_array are translated for calculation and retranslated afertwards

 for(int i=0;i<x_array.size();i++)//could also have been done in one single for-loop with the actual calculation, but it seems clearer like this....
   {
     //translate positions in a way the shock tube is centered around x=0;
     x_array[i]=x_array[i]-x_dia;
   };
 
 //actual calculation of exact schock tube values for each particle position (for-loop over all particles)
 for(int i=0;i<x_array.size();i++)
   {
     //if position is in area 4 (left hand side, before rarefaction)
     if(x_array[i]<=-1*a_4*t)
       {
	  p_array[i]=p_4;
	  rho_array[i]=rho_4;
	  u_array[i]=u_4;
	  e_array[i]=e_4;
       }
     //if position inside rarefaction
     else if((x_array[i]>-1*a_4*t)&&(x_array[i]<=(-1*a_3+u_3)*t))
       {
	 //local variables inside rarefaction
	 double u,rho,p,e;
	 double x=x_array[i];

	 //velocity in rarefaction wave (7.89)
	 u=2/(gamma+1)*(a_4+x/t);

	 //rho in rarefaction wave (7.87)
	 rho=rho_4*pow((1-(gamma-1)/2*(u/a_4)),(2/(gamma-1)));
	 //p in rarefaction wave with isentropic relation
	 p=p_4*pow((rho/rho_4),gamma);
	 //energy with ideal gas and e=c_v*T
	 e=p/(rho*(gamma-1));

	 //writing results in vectors
	 p_array[i]=p;
	 rho_array[i]=rho;
	 u_array[i]=u;
	 e_array[i]=e;
       }

     //if position after rarefaction before contact discontinuity (area 3)
     else if((x_array[i]>(-1*a_3+u_3)*t)&&(x_array[i]<=u_3*t))
       {
	  p_array[i]=p_3;
	  rho_array[i]=rho_3;
	  u_array[i]=u_3;
	  e_array[i]=e_3;
       }

     //if position after contact discontinuity before shock (area 2)
     else if((x_array[i]>u_3*t)&&(x_array[i]<=W*t))
       {
	  p_array[i]=p_2;
	  rho_array[i]=rho_2;
	  u_array[i]=u_2;
	  e_array[i]=e_2;
       }

     //if position after shock (area 1)
     else if(x_array[i]>W*t)
       {
	  p_array[i]=p_1;
	  rho_array[i]=rho_1;
	  u_array[i]=u_1;
	  e_array[i]=e_1;
       }
     
   }
 //assemble output file name for exact solution data
stringstream number;

number << setw(8) << setfill('0') <<t*1000000;
const string outputfile = "../../results/ResultsInProgress/exact" + number.str() + ".dat";
ofstream out(outputfile.c_str());
 if (!out)
  {
    cout<<"Initialtion: Cannot create "<<outputfile <<"! \n";
    exit(1);
  }
  else cout<<"\n writing the exact solution into "<< outputfile <<" \n"; 

 //write data into file (6 columns)
 for(int i=0;i<x_array.size();i++)
   {
     out<<setprecision(9)
	<< ::setw(17)<<x_array[i]+x_dia//to translate the domain back to its original position 
	<< ::setw(17)<<0.0 //y coordinate (no relevance), just to maintain file structure
	<< ::setw(17) <<rho_array[i]
	<< ::setw(17)<<p_array[i]
	<< ::setw(17)<<u_array[i]
	<< ::setw(17)<<e_array[i]
	<<"\n";
   }

 out.close();


 cout<<"\n file successfully written \n";


  //I just append the error calculation program here (initially wanted to create a new file for it but almost everything needed is already here, so:

  //again read simulation result data from file, but this time read everything

  vector <vector <double> > simulationData;
  
ifstream fin3(inputfile.c_str(), ios::in);
 buffer=0;
 vector<double> row(n_col,0);
 getline(fin3,garbage);
  getline(fin3,garbage);

  while(!fin3.eof())
  {
  
    for (int i=0; i<n_col;i++)//problem: reads always one more than eof
	{ fin3>>buffer;
	  row[i]=buffer; 
	}

    simulationData.push_back(row);
        
  }  

  //probably need to remove last row (no need, as we consider only diaphragm +/-0.5)

  fin3.close();


  //relative (NO, now ABSOLUTE) error (as relative nonsense for 0)

  vector <double> error_rho;
  vector <double> error_p;
  vector <double> error_u;
  vector <double> error_e;

  for(int i=0;i<simulationData.size();i++)
    {
      //error only for those that are in +/- 0.5 of diaphragm
      if(x_array[i]>-0.5&&x_array[i]<0.5)
	{
      
	  error_rho.push_back(fabs((rho_array[i]-simulationData[i][2])/*/rho_array[i]*/));
	  error_p.push_back(fabs((p_array[i]-simulationData[i][3])/*/p_array[i]*/));
	  error_u.push_back(fabs((u_array[i]-simulationData[i][4])/*/u_array[i]*/));
	  error_e.push_back(fabs((e_array[i]-simulationData[i][5])/*/e_array[i]*/));
  
	} 
    }

  //averaged relative (NO, CUMMULATED ABSOLUTE) error ()

  double AverRelError_rho=0;
  double AverRelError_p=0;
  double AverRelError_u=0;
  double AverRelError_e=0;
  int count1=0;

  //calculate the cummulated absolute error
  for(int i=0;i<simulationData.size();i++)
   {
     //here as well only for +/- 0.5 diaphragm
     if(x_array[i]>-0.5&&x_array[i]<0.5)
       {
	 AverRelError_rho=AverRelError_rho+error_rho[count1];
	 AverRelError_p=AverRelError_p+error_p[count1];
	 AverRelError_u=AverRelError_u+error_u[count1];
	 AverRelError_e=AverRelError_e+error_e[count1];
	 count1++;
       }
    }
 

 //L_1 norm calculation: sum all errors of rho, u, e 

 //norm calculation in the whole domain x=-0.5 til x=0.5
 double L_1NormRho=0;
 double L_1NormU=0;
 double L_1NormE=0;
 double L_1Norm=0;
 int N_part=0;//number of particles in domain x=-0.5 til x=0.5

 for(int i=0;i<simulationData.size();i++)
   {
     //here as well only for +/- 0.5 diaphragm
     if(x_array[i]>-0.5&&x_array[i]<0.5)
       {
	 N_part++;
	 L_1NormRho=L_1NormRho+fabs(rho_array[i]-simulationData[i][2]);
	 L_1NormU=L_1NormU+fabs(u_array[i]-simulationData[i][4]);
	 L_1NormE=L_1NormE+fabs(e_array[i]-simulationData[i][5]);
       }
    }
 L_1NormRho=L_1NormRho/N_part;
 L_1NormU=L_1NormU/N_part;
 L_1NormE=L_1NormE/N_part;
 L_1Norm=L_1NormRho+L_1NormU+L_1NormE;


//norm calculation in area3 (after rarefaction before contact discontinuity)

// more precisely, to get rid of the smoothing effect and to focus only on the actual after shock value precision, a margin of the size of the supportlength is given at both edges of area 3
 
 double L_1NormRho3=0;
 double L_1NormU3=0;
 double L_1NormE3=0;
 double L_1Norm3=0;
 int N_part3=0;//number of particles in domain x=-0.5 til x=0.5

 for(int i=0;i<simulationData.size();i++)
   {
     //take into account only particles in area 3 including margin (see comment above)
      if((x_array[i]>(-1*a_3+u_3)*t+supportlength)&&(x_array[i]<=u_3*t-supportlength))
       {
	 N_part3++;//count particle
	 //sum all errors
	 L_1NormRho3=L_1NormRho3+fabs(rho_array[i]-simulationData[i][2]);
	 L_1NormU3=L_1NormU3+fabs(u_array[i]-simulationData[i][4]);
	 L_1NormE3=L_1NormE3+fabs(e_array[i]-simulationData[i][5]);
       }
    }
 //divide by the number of particles in area 3
 L_1NormRho3=L_1NormRho3/N_part3;
 L_1NormU3=L_1NormU3/N_part3;
 L_1NormE3=L_1NormE3/N_part3;
 L_1Norm3=L_1NormRho3+L_1NormU3+L_1NormE3;


//norm calculation in area2 (after contact discontinuity, before shock)

// to get rid of the smoothing effect and to focus only on the actual after shock value precision, a margin of the size of the supportlength is given at both edges of area 2
 
 double L_1NormRho2=0;
 double L_1NormU2=0;
 double L_1NormE2=0;
 double L_1Norm2=0;
 int N_part2=0;//number of particles in domain x=-0.5 til x=0.5

 for(int i=0;i<simulationData.size();i++)
   {
     //take into account only particles in area 2 including margin (see comment above)
     if((x_array[i]>u_3*t+supportlength)&&(x_array[i]<=W*t-supportlength))
       {
	 N_part2++;//count particle
	 //sum all errors
	 L_1NormRho2=L_1NormRho2+fabs(rho_array[i]-simulationData[i][2]);
	 L_1NormU2=L_1NormU2+fabs(u_array[i]-simulationData[i][4]);
	 L_1NormE2=L_1NormE2+fabs(e_array[i]-simulationData[i][5]);
       }
    }
 //divide by the number of particles in area 2
 L_1NormRho2=L_1NormRho2/N_part2;
 L_1NormU2=L_1NormU2/N_part2;
 L_1NormE2=L_1NormE2/N_part2;
 L_1Norm2=L_1NormRho2+L_1NormU2+L_1NormE2;





 //output of the results in files
 
 //first output file: relative(no, absloute) error for rho, p, u, e at each particle position
const string filename = "../../results/ResultsInProgress/relError" + number.str() + ".dat";
ofstream out3(filename.c_str());
 if (!out)
  {
    cout<<"Initialtion: Cannot create "<<filename <<"! \n";
    exit(1);
  }
  else cout<<"\n writing relative (NO, ABSOLUTE) error of rho, p, u, e into "<< filename <<" \n"; 

 //file header
 out3<<"relative (NO; ABSOLUTE) error file\n";
 out3<<" x | rho | error rho[-] | p | error p [-] | u | error u[-] | e | error e[-]\n";

 int count2=0;//counter to match the good error vector entries for the corresponding x vector entries

 //write data
 for(int i=0;i<x_array.size();i++)
   {

     if(x_array[i]>-0.5&&x_array[i]<0.5)
	{
	  out3<<setprecision(6)
	      << ::setw(17)<<x_array[i]+x_dia//to translate the domain back to its original position 
	    << ::setw(17)<<rho_array[i]
	      << ::setw(17)<<error_rho[count2]
	      << ::setw(17)<<p_array[i]
	      << ::setw(17)<<error_p[count2]
	      << ::setw(17)<<u_array[i]
	      << ::setw(17)<<error_u[count2]
	      << ::setw(17)<<e_array[i]
	      << ::setw(17)<<error_e[count2]
	      <<"\n";
	  count2++;
	}
   }

 out3.close();

  cout<<"\n relative error file successfully written \n";


 //second output file: integral and mean error values
const string filename2 = "../../results/ResultsInProgress/IntegralAndMeanError" + number.str() + ".dat";
ofstream out4(filename2.c_str());
 if (!out)
  {
    cout<<"Initialtion: Cannot create "<<filename2 <<"! \n";
    exit(1);
  }
  else cout<<"\n writing integral (L_1) and mean error data into "<< filename2 <<" \n"; 

 //write file header
 out4<<"integral and mean error file\n\n\n";

 //write averaged percental error
 out4<<"cummulated absolute (non divided by number of particles) errors:\n\n";
 out4<<" rho error: ";
 out4<<setprecision(6)
     << ::setw(17)<<AverRelError_rho<<"\n";
 out4<<" p error: ";
 out4<<setprecision(6)
     << ::setw(17)<<AverRelError_p<<"\n";
 out4<<" u error: ";
 out4<<setprecision(6)
     << ::setw(17)<<AverRelError_u<<"\n";
 out4<<" e error: ";
 out4<<setprecision(6)
     << ::setw(17)<<AverRelError_e<<"\n";
 
 //write L_1 norm data for whole domain
 out4<<"\n \n L_1 norm errors (in whole domain: diaphragm +/- 0.5)\n\n";

 out4<<" L_1,rho: ";
 out4<<setprecision(6)
     << ::setw(17)<< L_1NormRho<<"\n";
 out4<<" L_1,u: ";
 out4<<setprecision(6)
     << ::setw(17)<< L_1NormU<<"\n";
 out4<<" L_1,e: ";
 out4<<setprecision(6)
     << ::setw(17)<< L_1NormE<<"\n";
 out4<<" L_1,tot: ";
 out4<<setprecision(6)
     << ::setw(17)<< L_1Norm<<"\n";



 //write L_1 norm data for area 3
 out4<<"\n \n L_1 norm errors (in area 3 (after rarefaction before discontinuity))\n\n";

 out4<<" L_1,rho3: ";
 out4<<setprecision(6)
     << ::setw(17)<< L_1NormRho3<<"\n";
 out4<<" L_1,u3: ";
 out4<<setprecision(6)
     << ::setw(17)<< L_1NormU3<<"\n";
 out4<<" L_1,e3: ";
 out4<<setprecision(6)
     << ::setw(17)<< L_1NormE3<<"\n";
 out4<<" L_1,tot3: ";
 out4<<setprecision(6)
     << ::setw(17)<< L_1Norm3<<"\n";

//write L_1 norm data for area 2
 out4<<"\n \n L_1 norm errors (in area 2 (after discontinuity, before shock))\n\n";

 out4<<" L_1,rho2: ";
 out4<<setprecision(6)
     << ::setw(17)<< L_1NormRho2<<"\n";
 out4<<" L_1,u2: ";
 out4<<setprecision(6)
     << ::setw(17)<< L_1NormU2<<"\n";
 out4<<" L_1,e 2 ";
 out4<<setprecision(6)
     << ::setw(17)<< L_1NormE2<<"\n";
 out4<<" L_1,tot2: ";
 out4<<setprecision(6)
     << ::setw(17)<< L_1Norm2<<"\n";

 out4.close();

  cout<<"\n integral and mean error file successfully written \n";



    return 0;
  }