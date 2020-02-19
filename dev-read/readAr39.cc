//g++ -std=c++11 readAr39.cc -o ar39 `root-config --cflags --glibs`
//#include <TFile.h>
//#include <TH1F.h>
//#include <TTreeReader.h>
//#include <TTreeReaderValue.h>
//#include <TTreeReaderArray.h>
//#include <TCanvas.h>

//#include <boost/range/combine.hpp>

#include <iostream>
#include <vector>

#include "Qpix/Random.h"
#include "Qpix/ReadG4txt.h"
#include <ctime>

#include <iostream>
#include <fstream>
#include <vector>

#include <math.h>

bool sortcol( const std::vector<double>& v1, 
               const std::vector<double>& v2 ) { 
 return v1[2] < v2[2]; 
}

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

   /* std::cout << "test" << std::endl;
   for (int i = 0; i < eventt2.size(); i++) 
   { 
      for (int j = 0; j < eventt2[i].size(); j++)
      {
         std::cout << eventt2[i][j]  << " ";   
      }
      std::cout << std::endl; 
      }
   std::cout << "test over" << std::endl;
   std::cout << "\n" << std::endl; */

   std::vector< std::vector<double> > Electron_Event_Vector;
   int qw=0;
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

   sort(Electron_Event_Vector.begin(), Electron_Event_Vector.end(),sortcol);

   
   
   std::cout<< "Number of electrons made " << qw << std::endl;
   
   std::cout<< "Total energy  " << Etot << std::endl;
   
   /* for (int i = 0; i < qw; i++) 
   { 
      for (int j = 0; j < 3; j++)
      { 
         //std::cout<< Event_Vector[i][j]<< " "; 
      } 
      //std::cout<< "\n"; 
   }  */

   


   /* //myReader.SetEntry(1);
   int qw=0;
   std::vector< std::vector<double> > Event_Vector;

   for (auto tup : boost::combine(*idesx,*idesy,*idesz,*idesenergy)) 
   {    
      double x,y,z,e;
      double new_x, new_y, new_z, Nelectron;
      boost::tie(x,y,z,e) = tup;
      //cout << x << ", "<< y << ", "<< z << ", "<< e << std::endl;
      //cout << qw << std::endl;
      //vector<double> temp;


      // this works and is fast but need to sort before this step so split it into 2 vectrs 
      Nelectron = round(e*1e6/Wvalue);
      for (int i = 0; i < Nelectron; i++) 
      {

         double T_drift = x/E_vel;
         double sigma_L, sigma_T;
         sigma_T = sqrt(2*DiffusionT*T_drift);
         sigma_L = sqrt(2*DiffusionL*T_drift);
         new_x = Qpix::RandomNormal(x,sigma_L);
         new_y = Qpix::RandomNormal(y,sigma_L);
         new_z = Qpix::RandomNormal(z,sigma_L);

         vector<double> temp;
         temp.push_back(new_x);
         temp.push_back(new_y);
         temp.push_back(new_z/E_vel);
         //temp.push_back(e);
            
         Event_Vector.push_back(temp);

         qw+=1;
      }
   }

   sort(Event_Vector.begin(), Event_Vector.end(),sortcol);

   for (int i = 0; i < qw; i++) 
   { 
      for (int j = 0; j < 3; j++)
      { 
         //std::cout<< Event_Vector[i][j]<< " "; 
      } 
      //std::cout<< "\n"; 
   }  */


   //int qwe = 0;

   /* for (auto it1 = begin (Event_Vector); it1 != end (Event_Vector); ++it1) 
   {
      for (auto it2 = (*it1).begin(); it2 != (*it1).end(); ++ it2 )
      {
         //std::cout << (*it2) << " "; // print the strings
      }
      //std::cout<< "\n";  
   } */

   std::cout << "done" << std::endl;

   time_req = clock() - time_req;
   double time = (float)time_req/CLOCKS_PER_SEC;
   std::cout<< "The operation took "<<time<<" Seconds"<<std::endl;
   return 0;
}