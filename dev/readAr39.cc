
//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <math.h>

#include "Qpix/Random.h"
#include "Qpix/ReadG4txt.h"
#include "Qpix/ElectronHandler.h"

#include <ctime>

struct HIT 
    {
        double  x_pos;
        double  y_pos;
        double  z_pos;
    };

bool compare(HIT one, HIT two)
{
    return (one.z_pos < two.z_pos);
}

std::vector<HIT> DiffuserTest2(double Wvalue,double E_vel,double DiffusionL,double DiffusionT,
                                                                         std::vector<std::vector<double>> eventt2)
    {
        std::vector<HIT> Electron_Event_Vector;
        //Electron_Event_Vector.push_back(HIT());

        int event_SIZE = eventt2.size();
        int indexer = 0;
        for (int i = 0; i < event_SIZE; i++)
        {
            double x,y,z,e;
            double new_x, new_y, new_z, Nelectron;
            x = eventt2[i][0];
            y = eventt2[i][1];
            z = eventt2[i][2];
            e = eventt2[i][3];

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

                Electron_Event_Vector.push_back(HIT());
                Electron_Event_Vector[indexer].x_pos = new_x;
                Electron_Event_Vector[indexer].y_pos = new_y;
                Electron_Event_Vector[indexer].z_pos = new_z;
                
                indexer += 1;
            }
        }

        sort(Electron_Event_Vector.begin(), Electron_Event_Vector.end(), compare);
        return Electron_Event_Vector;
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


    std::vector<HIT> Electron_Event_Vector;
    //Electron_Event_Vector.push_back(HIT());
    //Electron_Event_Vector = DiffuserTest2( Wvalue, E_vel, DiffusionL, DiffusionT, eventt2);

    int event_SIZE = eventt2.size();
    int indexer = 0;
    for (int i = 0; i < event_SIZE; i++)
    {
        double x,y,z,e;
        double new_x, new_y, new_z, Nelectron;
        x = eventt2[i][0]+50;
        y = eventt2[i][1]+50;
        z = eventt2[i][2]+50;
        e = eventt2[i][3];

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

            if (T_drift<0)
            {
                std::cout << T_drift << " " << sigma_T << std::endl;

            }
            Electron_Event_Vector.push_back(HIT());
            Electron_Event_Vector[indexer].x_pos = new_x;
            Electron_Event_Vector[indexer].y_pos = new_y;
            Electron_Event_Vector[indexer].z_pos = new_z;
            
            indexer += 1;
        }

    }

   sort(Electron_Event_Vector.begin(), Electron_Event_Vector.end(), compare);


   /* for (int i = 0; i < Electron_Event_Vector.size(); i++) 
   { 
      std::cout<< Electron_Event_Vector[i].x_pos << " "; 
      std::cout<< Electron_Event_Vector[i].y_pos << " "; 
      std::cout<< Electron_Event_Vector[i].z_pos << " "; 
      std::cout<< "\n"; 
   }  */



   // this should be a diffuser function
   //std::vector< std::vector<double>> Electron_Event_Vector;

   //std::vector<HIT> Electron_Event_Vector;
  // Electron_Event_Vector = Qpix::DiffuserTest2( Wvalue, E_vel, DiffusionL, DiffusionT, eventt2);
   
   std::cout << "lenth of the event " << Electron_Event_Vector.size() << std::endl;

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