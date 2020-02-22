
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
   //std::vector< std::vector<double>> Electron_Event_Vector;

   std::vector<Qpix::HIT> Electron_Event_Vector;
   Electron_Event_Vector = Qpix::DiffuserTest2( Wvalue, E_vel, DiffusionL, DiffusionT, eventt2);

   for (int i = 0; i < Electron_Event_Vector.size(); i++) 
   { 
      std::cout<< Electron_Event_Vector[i].x_pos << " "; 
      std::cout<< Electron_Event_Vector[i].y_pos << " "; 
      std::cout<< Electron_Event_Vector[i].z_pos << " "; 
      std::cout<< "\n"; 
   } 
   
   









   // Read out plane size in mm
   int Readout_Dim = 100;
   int Pix_Size = 4;
   int N_Pix;
   N_Pix = Readout_Dim/Pix_Size;
   // Need to check this before the other code runs... but for now well wing it.
   if( N_Pix*Pix_Size == Readout_Dim )
   {
      std::cout << "N_Pix is an integer" << std::endl;
   }



   // initilizing a 2d vector 
   int ROW,COL;
   ROW = 10;
   COL = 10;
   std::vector<std::vector<int>> array2d(ROW, std::vector<int>(COL));

   /* for (int i = 0; i < ROW; i++)
      for (int j = 0; j < COL; j++)
         array2d[i][j] = 1; */

   for (int i = 0; i < ROW; i++) 
   { 
      for (int j = 0; j < COL; j++)
      { 
         std::cout<< array2d[i][j]<< " "; 
      } 
      std::cout<< "\n"; 
   } 

   //making a test data set and printing
   std::vector<std::vector<int>> Testvect(20, std::vector<int>(2));
   for (int i = 0; i < 20; i++)
      for (int j = 0; j < 2; j++)
         Testvect[i][j] = 5;

   for (int i = 0; i < 20; i++) 
   { 
      for (int j = 0; j < 2; j++)
      { 
         std::cout<< Testvect[i][j]<< " "; 
      } 
      std::cout<< "\n"; 
   } 

   // fill the array
   for (int i = 0; i < 20; i++)
   {
      int Pix_Xloc, Pix_Yloc;
      Pix_Xloc = Testvect[i][0];
      Pix_Yloc = Testvect[i][1];

      array2d[Pix_Xloc][Pix_Yloc]+=1;
      if (array2d[Pix_Xloc][Pix_Yloc] >= 7)
      {
         std::cout << "Threshold crossed" << std::endl;
         array2d[Pix_Xloc][Pix_Yloc] = 0;
      }

   }


   //print the array

   for (int i = 0; i < ROW; i++) 
   { 
      for (int j = 0; j < COL; j++)
      { 
         std::cout<< array2d[i][j]<< " "; 
      } 
      std::cout<< "\n"; 
   } 







   std::cout << "done" << std::endl;

   time_req = clock() - time_req;
   double time = (float)time_req/CLOCKS_PER_SEC;
   std::cout<< "The operation took "<<time<<" Seconds"<<std::endl;
   return 0;
}