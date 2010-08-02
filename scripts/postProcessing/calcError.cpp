
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

  const int n_col=8;//number of columns in smulation output file
  double buffer;
  int counter=0;
  vector<double> row(8,0);
  vector< vector<double> > exactData;

  //in the first part the particles ensembles with same x coordinate are formed and their IDs stored

  //reading the exact data file exact*.dat;
  ifstream fin("../../results/ResultsInProgress/exact*.dat", ios::in);
  if (!fin)
  {
    cout<<"Cannot open exactxxxxxxxx.dat \n" ;
    exit(1);
  }
  else cout<<"\n reading sorted0000000exactxxxxxxxx.dat \n"; 

  //read in file

  while(!fin.eof())
  {
       
    //read one row
    for (int i=0; i<n_col&&!fin.eof();i++)//problem: reads always one more than eof
	{ fin>>buffer;
	  row[i]=buffer; 
	}
    //append row to exactData
    exactData.push_back(row);
	
      
        
  }  
  fin.close();

  // build the ID ensembles of all particles having the same x (the allgorithm takes advantage of the fact that the x-values are allready sorted (by the shell script))

  vector < vector <int> > allID_Couples;
  int i=0;
  while(i<matrix.size()-1)
    {
      vector<int>ID_Couple(1, matrix[i][6]);
     
      while(matrix[i+1][0]==matrix[i][0])
	{
	  
	  ID_Couple.push_back(matrix[i+1][6]);
	  
	  if(i<matrix.size()-1)
	  i++;
	 
	  if(i==matrix.size()-1)//to avoid segmentation fault when verifying condition in while loop (matrix[i+1]....)
	    break;
	}
     
      allID_Couples.push_back(ID_Couple);
      if(i<matrix.size()-1)
      i++;
      
    }
