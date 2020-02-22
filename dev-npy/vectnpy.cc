// Taken from http://www.cplusplus.com/doc/tutorial/files/

// reading a text file

//g++ -std=c++11 vectnpy.cc 

//g++ -std=c++11 vectnpy.cc -o vect -I/usr/local/Cellar/hdf5/1.10.6/include/ -L/usr/local/Cellar/hdf5/1.10.6/lib/ -lhdf5_cpp -lhdf5
#include <iostream>
#include <fstream>
#include <string>

#include <vector>


struct HIT 
{
  double  x_pos;
  double  y_pos;
  double  z_pos;
};

int main () 
{
  std::vector<HIT> hit_vect;

  hit_vect.push_back(HIT());

  hit_vect[0].x_pos = 0.0;
  hit_vect[0].y_pos = 0.0;
  hit_vect[0].z_pos = 0.0;

  hit_vect.push_back(HIT());

  hit_vect[1].x_pos = 1.0;
  hit_vect[1].y_pos = 1.0;
  hit_vect[1].z_pos = 1.0;

  hit_vect.push_back(HIT());

  hit_vect[2].x_pos = 2.0;
  hit_vect[2].y_pos = 2.0;
  hit_vect[2].z_pos = 2.0;

  std::cout << "print" << std::endl;

  for (int i = 0; i < hit_vect.size(); i++) 
   { 
      std::cout<< hit_vect[i].x_pos << " "; 
      std::cout<< hit_vect[i].y_pos << " "; 
      std::cout<< hit_vect[i].z_pos << " "; 
      std::cout<< "\n"; 
   } 

  std::cout << hit_vect.size() << std::endl;

  std::cout << hit_vect[0].x_pos << std::endl;


  std::cout << "THE END" << std::endl;








  




  return 0;
}