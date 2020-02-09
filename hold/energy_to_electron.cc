//g++ -std=c++11 energy_to_electron.cc  -o ele `root-config --cflags --glibs`
#include <iostream>
#include <vector>
#include <cmath>
#include <random>

using namespace std;
#include <chrono> 
using namespace std::chrono;
int main() 
{auto start = high_resolution_clock::now();
   double Wvalue, E_vel, DiffusionL, DiffusionT;
   Wvalue = 23.6; // in eV
   E_vel = 0.1648; //cm/mus
   DiffusionL = 6.8223/1e6;  //cm**2/mus
   DiffusionT = 13.1586/1e6; //cm**2/mus


   double xpos=500, ypos=20, zpos=10, eng =500000;
   double Nelectron;

   Nelectron = round(eng/Wvalue);
   cout << "Nelectron " << Nelectron << endl;

   // this generates a nice random number
   random_device rd;
   mt19937 mt(rd());
   uniform_real_distribution<double> dist(-1.0, 1.0);

   double T_drift = xpos/E_vel;
   double sigma_L, sigma_T;
   sigma_T = sqrt(2*DiffusionT*T_drift);
   sigma_L = sqrt(2*DiffusionL*T_drift);


   normal_distribution<double> dist_norm_L(xpos  , sigma_L);
   normal_distribution<double> dist_norm_Ty(ypos , sigma_T);
   normal_distribution<double> dist_norm_Tz(zpos , sigma_T);
   double newx,newy,newz;
   for (int i=0; i<Nelectron; ++i)
   {
      newx = dist_norm_L(mt);
      newy = dist_norm_Ty(mt);
      newz = dist_norm_Tz(mt);
      cout << newx << ", " << newy << ", " << newz << endl;
   }
   

   auto stop = high_resolution_clock::now();
   auto duration = duration_cast<microseconds>(stop - start); 
   cout << "Total time " << duration.count()/1e6 << endl; 
   cout << "Time per loop " << duration.count()/Nelectron << endl;
   
   cout << "done" << endl;



   
   return 0;
}