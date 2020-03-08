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
   //E_vel = 0.1648; //cm/mus
   E_vel = 1.648; //mm/mus
   DiffusionL = 682.23/1e6;  //mm**2/mus
   DiffusionT = 1315.86/1e6; //mm**2/mus

   // here x,y,z are in mm and edep is in MeV
   std::vector<std::vector<double>> RawDataVector2;
   std::vector<int> EventLengths2;
   //Qpix::DataFileParser2("test.txt", RawDataVector2, EventLengths2);
   //Qpix::DataFileParser2("test10MeV.txt", RawDataVector2, EventLengths2);
   Qpix::DataFileParser2("Muon_250MeV.txt", RawDataVector2, EventLengths2);
   //Qpix::DataFileParser2("Ar39.txt", RawDataVector2, EventLengths2);
   int Event = 0;
   std::vector<std::vector<double>> eventt2;
   eventt2 =  Qpix::GetEventVector(Event ,  EventLengths2,  RawDataVector2);

   std::vector<Qpix::HIT> Electron_Event_Vector;
   Electron_Event_Vector = Qpix::DiffuserTest2( Wvalue, E_vel, DiffusionL, DiffusionT, eventt2);


   // Read out plane size in mm
   int Readout_Dim = 1000;
   int Pix_Size = 4;
   int N_Pix;
   N_Pix = Readout_Dim/Pix_Size;
   // Need to check this before the other code runs... but for now well wing it.
   if( N_Pix*Pix_Size == Readout_Dim )
   {
      std::cout << "N_Pix is an integer" << std::endl;
   }

   //std::cout << "making empty data2d" << std::endl;
   std::vector<std::vector<int>> data2d(N_Pix, std::vector<int>(N_Pix));
   for (int i = 0; i < N_Pix; i++)
      for (int j = 0; j < N_Pix; j++)
         data2d[i][j] = 0;

   std::vector<double> Gaussian_Noise;
   for (int i = 0; i < 10000; i++)
   {
      // should be 200 and 20 per mus making it a gaussian of 20 every 100ns
      Gaussian_Noise.push_back((int)Qpix::RandomNormal(200,30));
      //Gaussian_Noise.push_back((int)Qpix::RandomPoisson(20));
   }
   int Noise_index = 0;


   int Reset = 1000;
   int Event_Length = Electron_Event_Vector.size();
   std::cout << "Event_Length  " << Event_Length << std::endl;


   // vect of hit pixels 
   /* std::vector<std::vector<int>> Pixels_Hit;
   for (int i=0; i<Event_Length; i++)
   {
      int Pix_Xloc, Pix_Yloc;
      Pix_Xloc = (int) ceil(Electron_Event_Vector[i].x_pos/4);
      Pix_Yloc = (int) ceil(Electron_Event_Vector[i].y_pos/4);
      std::vector<int> tmp = {Pix_Xloc, Pix_Yloc};
      if(std::find(Pixels_Hit.begin(), Pixels_Hit.end(), tmp) != Pixels_Hit.end()){}
      else{Pixels_Hit.push_back( tmp );}
   }  */

   /* for (int i=0; i<Pixels_Hit.size(); i++)
   {
      std::cout << Pixels_Hit[i][0] << " " << Pixels_Hit[i][1] << std::endl;
   } */



   std::vector<std::vector<double>> RTD;
  
   int GlobalTime = 0;

   for (int i = 0; i < Event_Length; i++)
   {
      int Pix_Xloc, Pix_Yloc;
      Pix_Xloc = (int) ceil(Electron_Event_Vector[i].x_pos/Pix_Size);
      Pix_Yloc = (int) ceil(Electron_Event_Vector[i].y_pos/Pix_Size);
      double Pix_time = Electron_Event_Vector[i].z_pos/E_vel;
      //std::cout << Pix_Xloc << ' ' << Pix_Yloc << ' ' << Pix_time << std::endl;
      while (GlobalTime < Pix_time)
      {
         for (int i = 0; i < N_Pix; i++) 
         { 
            for (int j = 0; j < N_Pix; j++)
            { 
               data2d[i][j]+=Gaussian_Noise[Noise_index];
               Noise_index += 1;
               if (Noise_index >= 10000){Noise_index = 0;}
               if (data2d[i][j] >= Reset)
               {
                  data2d[i][j] = 0;
                  std::vector<double> tmp = {(double)i, (double)j, (double)GlobalTime};
                  RTD.push_back(tmp);
               }

            } 
         } 

         GlobalTime+=1;
      }

      data2d[Pix_Xloc][Pix_Yloc]+=1;
      if (data2d[Pix_Xloc][Pix_Yloc] >= Reset)
      {
         data2d[Pix_Xloc][Pix_Yloc] = 0;
         std::vector<double> tmp = {(double)Pix_Xloc, (double)Pix_Yloc, Pix_time};
         RTD.push_back(tmp);
      }

   }

   while (GlobalTime < 1000)
   {
      for (int i = 0; i < N_Pix; i++) 
      { 
         for (int j = 0; j < N_Pix; j++)
         { 
            
            data2d[i][j]+=Gaussian_Noise[Noise_index];
            Noise_index += 1;
            if (Noise_index >= 10000){Noise_index = 0;}
            if (data2d[i][j] >= Reset)
            {
               data2d[i][j] = 0;
               std::vector<double> tmp = {(double)i, (double)j, (double)GlobalTime};
               RTD.push_back(tmp);
            }

         } 
      } 

      GlobalTime+=1;
   }




   int RTD_len = RTD.size();


   /* std::ofstream testdata2;
   testdata2.open ("exampledata2.txt");
   for (int Xpix = 0; Xpix < N_Pix; Xpix++)
   {
      for (int Ypix = 0; Ypix < N_Pix; Ypix++)
      {
         double Delta_T = 0;
         double resetold=0;
         for (int i = 0; i < RTD_len; i++)
         {

            if ( (RTD[i][0] == Xpix) && (RTD[i][1] == Ypix) )
            {
               double reset = RTD[i][2];
               Delta_T = reset - resetold;
               testdata2 << Xpix << ' ' << Ypix << ' ' << RTD[i][2] << ' ' << Delta_T << std::endl;
               resetold = RTD[i][2];

            }
         }
      }
   }
   testdata2.close(); */
   



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













