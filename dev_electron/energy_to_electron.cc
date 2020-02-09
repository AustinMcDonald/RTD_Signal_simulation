//g++ -std=c++11 energy_to_electron.cc  -o ele `root-config --cflags --glibs`
//#include "Qpix/Random.h"

#include <iostream>
#include <vector>
#include <cmath>

int main() 
{
   const int n = 5; 
   const int m = 5;
   int arry[n][m] = {}; 

   for (int i = 0; i < n; i++) 
   { 
      for (int j = 0; j < m; j++)
      { 
         std::cout<< arry[i][j]<< " "; 
      } 
      std::cout<< "\n"; 
   }


   
   return 0;
}