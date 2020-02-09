//g++ -std=c++11 readAr39.cc -o ar39 `root-config --cflags --glibs`
#include <TFile.h>
//#include <TH1F.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
//#include <TTreeReaderArray.h>
//#include <TCanvas.h>

#include <boost/range/combine.hpp>

#include <iostream>
#include <vector>

#include "Qpix/Random.h"

#include <ctime>


using namespace std;
int main() 
{  
   clock_t time_req;
   time_req = clock();


   // Create a histogram for the values we read.
   //TH1F *myHist = new TH1F("h1", "h1 title", 100, -4, 4);
   // Open the file containing the tree.
   TFile *myFile = TFile::Open("/Users/austinmcdonald/projects/Q-pix/RTD_Signal_simulation/MC_data/Ar39_test/ar39_events.root");
   // Create a TTreeReader for the tree, for instance by passing the
   // TTree's name and the TDirectory / TFile it is in.
   TTreeReader myReader("anatree/anatree", myFile);

   //This reads the vector
   TTreeReaderValue<std::vector<double>> idesenergy(myReader, "ides_energy");

   //This reads the vector
   TTreeReaderValue<std::vector<double>> idesx(myReader, "ides_voxel_x");
   TTreeReaderValue<std::vector<double>> idesy(myReader, "ides_voxel_y");
   TTreeReaderValue<std::vector<double>> idesz(myReader, "ides_voxel_z");
   
   // this reads the event number. 
   //TTreeReaderValue<int> ievent(myReader, "event");
   
   //This reads the PDG (electron is 11)
   TTreeReaderValue<std::vector<int>> iPDG(myReader, "PDG");


   double Wvalue, E_vel, DiffusionL, DiffusionT;
   Wvalue = 23.6; // in eV
   E_vel = 0.1648; //cm/mus
   DiffusionL = 6.8223/1e6;  //cm**2/mus
   DiffusionT = 13.1586/1e6; //cm**2/mus


   myReader.SetEntry(1);
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
      /* temp.push_back(x);
      temp.push_back(y);
      temp.push_back(z);
      temp.push_back(e);
         
      Event_Vector.push_back(temp);
         */
      //qw+=1;
   }


   /* for (int i = 0; i < qw; i++) 
   { 
      for (int j = 0; j < 3; j++)
      { 
         std::cout<< Event_Vector[i][j]<< " "; 
      } 
      std::cout<< "\n"; 
   }  */


   /* int qwe = 0;
   for (auto it = begin (Event_Vector); it != end (Event_Vector); ++it) 
   {
    it->doSomething ();
   } */


   std::cout << "done" << std::endl;

   time_req = clock() - time_req;
   double time = (float)time_req/CLOCKS_PER_SEC;
   std::cout<< "The operation took "<<time<<" Seconds"<<std::endl;
   return 0;
}