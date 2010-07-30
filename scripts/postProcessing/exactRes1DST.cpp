

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
	  cout<<buffer<<"  ";
	  x_array.push_back(buffer);
	}
      counter++;
        
  }  
  fin.close();
  //remove last element (as last file entry is also written to x_array???)
  x_array.erase(x_array.end()-1);

  //control output for user
  cout<<"\n this is for visual control if the extraction of x values has been succssfull\n";
  cout<<"First value of the array (should correspond to right hand edge particle position)"<<x_array[0]<<"\n";
cout<<"Last value of the array (should correspond to left hand edge particle position)"<<x_array[x_array.size()-1]<<"\n";


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

 const double p_2=0.30313;
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
 //then induced velocity behind shock wave u_p with (7.15) Anderson
 cout<<"\n W: "<<W;
 const double u_p=W*(1-rho_1/rho_2);
 const double u_2=u_p;
 const double u_3=u_p;
 cout<<"\n u_2=u_3= "<<u_3;


 //now iterate the position vector and calculate the missing values for each component (=position)

 //vectors for results
 vector<double> p_array(x_array.size(),0);
 vector<double> rho_array(x_array.size(),0);
 vector<double> u_array(x_array.size(),0);
 vector<double> e_array(x_array.size(),0);

 //therefore here: shock tube is centered around x=0 (thats where diaphragm is)
 //if inputfiledata are calculated for a different diaphragmposition, values of x_array are translated for calculation and retranslated afertwards

 for(int i=0;i<x_array.size();i++)//could also have been done in one single for loop with the actual calculation, but it seems clearer like this....
   {
     //translate positions in a way the shock tube is centered around x=0;
     x_array[i]=x_array[i]-x_dia;
   };
 cout<<"time t: ";
 for(int i=0;i<x_array.size();i++)
   {
     //if position is in area 4 (left hand side before rarefaction)
     if(x_array[i]<=-1*a_4*t)
       {
	 cout<<"\n area 4, "<<x_array[i];
	  p_array[i]=p_4;
	  rho_array[i]=rho_4;
	  u_array[i]=u_4;
	  e_array[i]=e_4;
       }
     //if position inside rarefaction
     else if((x_array[i]>-1*a_4*t)&&(x_array[i]<=(-1*a_3+u_3)*t))
       {
	 cout<<"\n inside rarefaction, "<<x_array[i];
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
	 cout<<"\n area 3, "<<x_array[i];
	 p_array[i]=p_3;
	  rho_array[i]=rho_3;
	  u_array[i]=u_3;
	  e_array[i]=e_3;
       }

     //if position after contact discontinuity before shock (area 2)
     else if((x_array[i]>u_3*t)&&(x_array[i]<=W*t))
       {
	 cout<<"\n area 2, "<<x_array[i];
	  p_array[i]=p_2;
	  rho_array[i]=rho_2;
	  u_array[i]=u_2;
	  e_array[i]=e_2;
       }

     //if position after shock (area 1)
     else if(x_array[i]>W*t)
       {
	 cout<<"\n area 1, "<<x_array[i]; 
	 p_array[i]=p_1;
	  rho_array[i]=rho_1;
	  u_array[i]=u_1;
	  e_array[i]=e_1;
       }
     
   }
 //assemble output file name
stringstream number;

number << setw(8) << setfill('0') <<t*1000000;
const std::string outputfile = "../../results/ResultsInProgress/exact" + number.str() + ".dat";
ofstream out(outputfile.c_str());
 if (!out)
  {
    cout<<"Initialtion: Cannot create "<<outputfile <<"! \n";
    exit(1);
  }
  else cout<<"writing the exact solution into "<< outputfile <<" \n"; 

 for(int i=0;i<x_array.size();i++)
   {
     out<<setprecision(9)
	<< ::setw(17)<<x_array[i]+x_dia//to translate the domain back to its original position 
	     << ::setw(17)<<0.0 
	     << ::setw(17) <<rho_array[i]
	     << ::setw(17)<<p_array[i]
	     << ::setw(17)<<u_array[i]
	     << ::setw(17)<<e_array[i]
             <<"\n";
   }

 out.close();




  cout<<"\n file successfully written, program end";
  return 0;
}
