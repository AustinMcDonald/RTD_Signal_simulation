
#include <iostream>
#include <vector>

#include "Qpix/Random.h"
#include "Qpix/ReadG4txt.h"
#include "Qpix/ElectronHandler.h"

#include <ctime>

#include <fstream>

#include <math.h>

/* bool sortcol( const std::vector<double>& v1, 
               const std::vector<double>& v2 ) { 
 return v1[2] < v2[2]; 
}

std::vector< std::vector<double>> DiffuserTest(double Wvalue,double E_vel,double DiffusionL,double DiffusionT,
                                                                      const std::vector<std::vector<double>>& eventt2)
{
   std::vector< std::vector<double>> Electron_Event_Vector;
   int event_SIZE = eventt2.size();
   //int qw=0;
   //double Etot = 0;
   for (int i = 0; i < event_SIZE; i++)
   {
      double x,y,z,e;
      double new_x, new_y, new_z, Nelectron;
      x = eventt2[i][0];
      y = eventt2[i][1];
      z = eventt2[i][2];
      e = eventt2[i][3];
      //Etot+=e;


      Nelectron = round(e*1e6/Wvalue);
      for (int i = 0; i < Nelectron; i++) 
      {

         double T_drift = x/E_vel;
         double sigma_L, sigma_T;
         sigma_T = sqrt(2*DiffusionT*T_drift);
         sigma_L = sqrt(2*DiffusionL*T_drift);
         new_x = Qpix::RandomNormal(x,sigma_L);
         new_y = Qpix::RandomNormal(y,sigma_T);
         new_z = Qpix::RandomNormal(z,sigma_T);

         std::vector<double> temp;
         temp.push_back(new_x);
         temp.push_back(new_y);
         temp.push_back(new_z/E_vel);
         //temp.push_back(e);
            
         Electron_Event_Vector.push_back(temp);

         //qw+=1;
      }
   }

   sort(Electron_Event_Vector.begin(), Electron_Event_Vector.end(),sortcol);
   return Electron_Event_Vector;
} */

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
   /* int qw=0;
   double Etot = 0;
   for (int i = 0; i < eventt2.size(); i++)
   {
      double x,y,z,e;
      double new_x, new_y, new_z, Nelectron;
      x = eventt2[i][0];
      y = eventt2[i][1];
      z = eventt2[i][2];
      e = eventt2[i][3];
      Etot+=e;


      Nelectron = round(e*1e6/Wvalue);
      for (int i = 0; i < Nelectron; i++) 
      {

         double T_drift = x/E_vel;
         double sigma_L, sigma_T;
         sigma_T = sqrt(2*DiffusionT*T_drift);
         sigma_L = sqrt(2*DiffusionL*T_drift);
         new_x = Qpix::RandomNormal(x,sigma_L);
         new_y = Qpix::RandomNormal(y,sigma_T);
         new_z = Qpix::RandomNormal(z,sigma_T);

         std::vector<double> temp;
         temp.push_back(new_x);
         temp.push_back(new_y);
         temp.push_back(new_z/E_vel);
         //temp.push_back(e);
            
         Electron_Event_Vector.push_back(temp);

         qw+=1;
      }
   }

   sort(Electron_Event_Vector.begin(), Electron_Event_Vector.end(),sortcol); */
   
   //std::cout<< "Number of electrons made " << qw << std::endl;
   
   //std::cout<< "Total energy  " << Etot << std::endl;
   

   
   for (int i = 0; i < Electron_Event_Vector.size(); i++) 
   { 
      for (int j = 0; j < Electron_Event_Vector[i].size(); j++)
      { 
         std::cout<< Electron_Event_Vector[i][j]<< " "; 
      } 
      std::cout<< "\n"; 
   } 

   



   std::cout << "done" << std::endl;

   time_req = clock() - time_req;
   double time = (float)time_req/CLOCKS_PER_SEC;
   std::cout<< "The operation took "<<time<<" Seconds"<<std::endl;
   return 0;
}