
//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <math.h>

#include "Qpix/Random.h"
#include "Qpix/ReadG4txt.h"
#include "Qpix/ElectronHandler.h"

#include <ctime>

//#include <iostream>
//#include <fstream>


int main() 
{  
   clock_t time_req;
   time_req = clock();


   double Wvalue, E_vel, DiffusionL, DiffusionT;
   Wvalue = 23.6; // in eV
   //E_vel = 0.1648; //cm/mus
   E_vel = 1.648; //mm/mus
   DiffusionL = 682.23/1e6;  //mm**2/mus
   DiffusionT = 1315.86/1e6; //mm**2/mus

   // here x,y,z are in mm and edep is in MeV
   std::vector<std::vector<double>> RawDataVector2;
   std::vector<int> EventLengths2;
   Qpix::DataFileParser2("test.txt", RawDataVector2, EventLengths2);
   int Event = 0;
   std::vector<std::vector<double>> eventt2;
   eventt2 =  Qpix::GetEventVector(Event ,  EventLengths2,  RawDataVector2);

   std::vector<Qpix::HIT> Electron_Event_Vector;
   Electron_Event_Vector = Qpix::DiffuserTest2( Wvalue, E_vel, DiffusionL, DiffusionT, eventt2);


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

   
   std::vector<std::vector<int>> data2d(N_Pix, std::vector<int>(N_Pix));
   for (int i = 0; i < N_Pix; i++)
      for (int j = 0; j < N_Pix; j++)
         data2d[i][j] = 0;


   int Reset = 3000;
   int Event_Length = Electron_Event_Vector.size();
   std::cout << "Event_Length  " << Event_Length << std::endl;


   std::ofstream testdata;
   testdata.open ("exampledata.txt");
  
   int GlobalTime = 0;

   for (int i = 0; i < Event_Length; i++)
   {
      int Pix_Xloc, Pix_Yloc, Pix_time;
      Pix_Xloc = (int) ceil(Electron_Event_Vector[i].x_pos/4);
      Pix_Yloc = (int) ceil(Electron_Event_Vector[i].y_pos/4);
      Pix_time = (int) ceil(Electron_Event_Vector[i].z_pos/E_vel);
      //std::cout << Pix_time << std::endl;

      while (GlobalTime < Pix_time)
      {
         //std::cout << "Global "<< Pix_time << std::endl;
         int CT = 0;
         for (int i = 0; i < N_Pix; i++) 
         { 
            for (int j = 0; j < N_Pix; j++)
            { 
               
               data2d[i][j]+=(int)Qpix::RandomNormal(200,20);
               CT+=1;
               //std::cout<< data2d[i][j]<< " "; 
               if (data2d[i][j] >= Reset)
               {
                  //std::cout << "Threshold crossed" <<
                  //   " "<< i << " " << j << " " << GlobalTime << std::endl;

                  testdata << i << " " << j << " " << GlobalTime << std::endl;
                  data2d[i][j] = 0;
               }

            } 
         } 

         GlobalTime+=1;
      }

      

      data2d[Pix_Xloc][Pix_Yloc]+=1;
      if (data2d[Pix_Xloc][Pix_Yloc] >= Reset)
      {
         //std::cout << "Threshold crossed" <<
         //    " "<< Pix_Xloc << " " << Pix_Yloc << " " << Electron_Event_Vector[i].z_pos << std::endl;

         testdata << Pix_Xloc << " " << Pix_Yloc << " " << Electron_Event_Vector[i].z_pos << std::endl;
         data2d[Pix_Xloc][Pix_Yloc] = 0;
      }

   }

   while (GlobalTime < 100)
   {
      int CT = 0;
      for (int i = 0; i < N_Pix; i++) 
      { 
         for (int j = 0; j < N_Pix; j++)
         { 
            
            data2d[i][j]+=(int)Qpix::RandomNormal(200,20);
            CT+=1;
            if (data2d[i][j] >= Reset)
            {
               //std::cout << "Threshold crossed" <<
               //   " "<< i << " " << j << " " << GlobalTime << std::endl;

               testdata << i << " " << j << " " << GlobalTime << std::endl;
               data2d[i][j] = 0;
            }

         } 
      } 

      GlobalTime+=1;
   }

   testdata.close();



   // print the data vector

   /* for (int i = 0; i < N_Pix; i++) 
   { 
      for (int j = 0; j < N_Pix; j++)
      { 
         std::cout<< data2d[i][j]<< " "; 
      } 
      std::cout<< "\n"; 
   }  */






   std::cout << "done" << std::endl;

   time_req = clock() - time_req;
   double time = (float)time_req/CLOCKS_PER_SEC;
   std::cout<< "The operation took "<<time<<" Seconds"<<std::endl;
   return 0;
}