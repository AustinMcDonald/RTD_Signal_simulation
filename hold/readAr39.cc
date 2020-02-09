//g++ -std=c++11 readAr39.cc -o ar39 `root-config --cflags --glibs`
#include <TFile.h>
#include <TH1F.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TCanvas.h>

#include <boost/range/combine.hpp>

#include <iostream>
#include <vector>

using namespace std;
int main() 
{
   // Create a histogram for the values we read.
   TH1F *myHist = new TH1F("h1", "h1 title", 100, -4, 4);
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

   myReader.SetEntry(1);
   double eng = 0;
   for (auto tup : boost::combine(*idesx,*idesy,*idesz,*idesenergy)) {    // <---
        double x,y,z,e;
        boost::tie(x,y,z,e) = tup;
        eng+=e;
        cout << x << ", "<< y << ", "<< z << ", "<< e << std::endl;
    }
    
   std::cout<<eng<<endl;

   /* int itr = 0;
   while (myReader.Next()) 
   {  //std::cout<<itr<<std::endl;
      //if (itr==0)
      //{
      for (auto&& value : *iPDG){std::cout << value << std::endl;}
      
      //std::cout<<*ievent;
      //}
      itr += 1;

   } */

   std::cout << "done" << std::endl;
   return 0;
}