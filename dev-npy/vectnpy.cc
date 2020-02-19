// Taken from http://www.cplusplus.com/doc/tutorial/files/

// reading a text file

//g++ -std=c++11 vectnpy.cc -o vect -I/usr/local/Cellar/hdf5/1.10.6/include/ -L/usr/local/Cellar/hdf5/1.10.6/lib/ -lhdf5

//g++ -std=c++11 vectnpy.cc -o vect -I/usr/local/Cellar/hdf5/1.10.6/include/ -L/usr/local/Cellar/hdf5/1.10.6/lib/ -lhdf5_cpp -lhdf5
#include <iostream>
#include <fstream>
#include <string>

#include <vector>
using namespace std;

#include "H5Easy.h"
//#include <H5Cpp.h>
#define dim1 5
#define dim2 3

struct HIT 
{
  double  x_pos;
  double  y_pos;
  double  z_pos;
};

int main () 
{
  vector<HIT> hit_vect;

  hit_vect.push_back(HIT());

  hit_vect[0].x_pos = 0.0;
  hit_vect[0].y_pos = 0.0;
  hit_vect[0].z_pos = 0.0;

  hit_vect.push_back(HIT());

  hit_vect[1].x_pos = 1.0;
  hit_vect[1].y_pos = 1.0;
  hit_vect[1].z_pos = 1.0;

  cout << "print" << endl;

  cout << hit_vect[0].x_pos << endl;


  cout << "making h5" << endl;

  //vector<vector<double> > test(vector<double>(3));
  vector<vector<double> > test;
  test.push_back({0,0,0});
  test.push_back({0,0,0});
  test.push_back({0,0,0});
  for (int i = 0; i < 3; i++) 
  { 
    for (int j = 0; j < 3; j++)
    { 
      cout<< test[i][j]<< " "; 
    } 
    cout<< "\n"; 
  }


  WriteH5 data;
  data.setFileName("myH5File.h5");
  data.setVarName("event0");
  data.writeData(test);
  data.setVarName("event1");
  data.writeData(test);
  // make group
  data.createGroup("/myEvents");
  data.setVarName("/myEvents/event007");
  data.writeData(test);




  return 0;
}