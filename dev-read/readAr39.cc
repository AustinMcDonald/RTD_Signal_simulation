
//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <math.h>

#include "Qpix/Random.h"
#include "Qpix/ReadG4txt.h"
#include "Qpix/ElectronHandler.h"

#include <ctime>


int main() 
{  
   clock_t time_req;
   time_req = clock();


   double Wvalue, E_vel, DiffusionL, DiffusionT;
   Wvalue = 23.6; // in eV
   E_vel = 0.1648; //cm/mus
   DiffusionL = 6.8223/1e6;  //cm**2/mus
   DiffusionT = 13.1586/1e6; //cm**2/mus

   // here x,y,z are in mm and edep is in MeV
   std::vector<std::vector<double>> RawDataVector2;
   std::vector<int> EventLengths2;
   Qpix::DataFileParser2("test.txt", RawDataVector2, EventLengths2);
   int Event = 5;
   std::vector<std::vector<double>> eventt2;
   eventt2 =  Qpix::GetEventVector(Event ,  EventLengths2,  RawDataVector2);


   // this should be a diffuser function
   std::vector< std::vector<double>> Electron_Event_Vector;
   Electron_Event_Vector = Qpix::DiffuserTest( Wvalue, E_vel, DiffusionL, DiffusionT, eventt2);
   


   /* for (int i = 0; i < Electron_Event_Vector.size(); i++) 
   { 
      for (int j = 0; j < Electron_Event_Vector[i].size(); j++)
      { 
         std::cout<< Electron_Event_Vector[i][j]<< " "; 
      } 
      std::cout<< "\n"; 
   }  */

   



   std::cout << "done" << std::endl;

   time_req = clock() - time_req;
   double time = (float)time_req/CLOCKS_PER_SEC;
   std::cout<< "The operation took "<<time<<" Seconds"<<std::endl;
   return 0;
}