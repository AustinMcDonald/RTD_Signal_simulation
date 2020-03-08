#include "Qpix/Random.h"
#include "Qpix/ReadG4txt.h"
#include "Qpix/ElectronHandler.h"


#include <ctime>


std::vector<double> Make_Gaussian_Noise(double mu, double sigma, int Noise_Vector_Size)
{
   std::vector<double> Gaussian_Noise;
   for (int i = 0; i < Noise_Vector_Size; i++)
   {  // should be 200 and 20 per mus making it a gaussian of 20 every 100ns
      Gaussian_Noise.push_back((int)Qpix::RandomNormal(mu, sigma));
   }
   return Gaussian_Noise;
}

std::vector<std::vector<int>> Make_Readout_plane(int Readout_Dim, int Pix_Size)
{
   int N_Pix = Readout_Dim/Pix_Size;
   // check if the pixel is a whole number
   if( N_Pix*Pix_Size == Readout_Dim )
   {
      std::cout << "Making a " << N_Pix << " by " << N_Pix << " readout" << std::endl;
      std::cout << "with a " << Pix_Size << " mm pixel pitch " << std::endl;
   }
   else
   {
      std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
      std::cout << "you have failed" << std::endl;
      std::cout << "readout and pixel dimensions do not match" << std::endl;
      std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   std::vector<std::vector<int>> readout(N_Pix, std::vector<int>(N_Pix));
   for (int i = 0; i < N_Pix; i++)
      for (int j = 0; j < N_Pix; j++)
         readout[i][j] = 0;
   
   return readout;
}


std::vector<std::vector<int>> Find_Unique_Pixels(int Pix_Size, int Event_Length, std::vector<Qpix::HIT> Electron_Event_Vector)
{
   std::vector<std::vector<int>> Pixels_Hit;
   for (int i=0; i<Event_Length; i++)
   {
      int Pix_Xloc, Pix_Yloc;
      Pix_Xloc = (int) ceil(Electron_Event_Vector[i].x_pos/Pix_Size);
      Pix_Yloc = (int) ceil(Electron_Event_Vector[i].y_pos/Pix_Size);
      std::vector<int> tmp = {Pix_Xloc, Pix_Yloc};
      if(std::find(Pixels_Hit.begin(), Pixels_Hit.end(), tmp) != Pixels_Hit.end()){}
      else{Pixels_Hit.push_back( tmp );}
   }
   return Pixels_Hit;
}

      

std::vector<std::vector<double>> Make_Reset_Response(int Reset, int Pix_Size, double E_vel, int Event_Length, 
                                                      int Pixels_Hit_Len, int Noise_Vector_Size, int Start_Time, int End_Time,
                                                      std::vector<double> Gaussian_Noise, std::vector<std::vector<int>> Pixels_Hit,
                                                      std::vector<std::vector<int>> data2d, std::vector<Qpix::HIT> Electron_Event_Vector)
{
   std::vector<std::vector<double>> RTD;
   int Noise_index = 0;
   int GlobalTime = Start_Time;

   for (int i = 0; i < Event_Length; i++)
   {
      int Pix_Xloc, Pix_Yloc;
      Pix_Xloc = (int) ceil(Electron_Event_Vector[i].x_pos/Pix_Size);
      Pix_Yloc = (int) ceil(Electron_Event_Vector[i].y_pos/Pix_Size);
      double Pix_time = Electron_Event_Vector[i].z_pos/E_vel;

      while (GlobalTime < Pix_time)
      {
         for (int curr = 0; curr < Pixels_Hit_Len; curr++) 
         { 
            int X_curr = Pixels_Hit[curr][0];
            int Y_curr = Pixels_Hit[curr][1];
            data2d[X_curr][Y_curr]+=Gaussian_Noise[Noise_index];
            Noise_index += 1;
            if (Noise_index >= Noise_Vector_Size){Noise_index = 0;}
            if (data2d[X_curr][Y_curr] >= Reset)
            {
               data2d[X_curr][Y_curr] = 0;
               std::vector<double> tmp = {(double)X_curr, (double)Y_curr, (double)GlobalTime};
               RTD.push_back(tmp);
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

   while (GlobalTime < End_Time)
   {
      for (int curr = 0; curr < Pixels_Hit_Len; curr++) 
      { 
         int X_curr = Pixels_Hit[curr][0];
         int Y_curr = Pixels_Hit[curr][1];
         data2d[X_curr][Y_curr]+=Gaussian_Noise[Noise_index];
         Noise_index += 1;
         if (Noise_index >= Noise_Vector_Size){Noise_index = 0;}
         if (data2d[X_curr][Y_curr] >= Reset)
         {
            data2d[X_curr][Y_curr] = 0;
            std::vector<double> tmp = {(double)X_curr, (double)Y_curr, (double)GlobalTime};
            RTD.push_back(tmp);
         }
      } 
      GlobalTime+=1;
   }
   return RTD;

}



void Write_Reset_Data(std::string Output_File, int Pixels_Hit_Len, std::vector<std::vector<int>> Pixels_Hit, std::vector<std::vector<double>> RTD)
{
   int RTD_len = RTD.size();
   std::ofstream data_out;
   data_out.open (Output_File);

   for (int curr = 0; curr < Pixels_Hit_Len; curr++) 
   { 
      int X_curr = Pixels_Hit[curr][0];
      int Y_curr = Pixels_Hit[curr][1];

      double Delta_T = 0;
      double resetold=0;
      for (int i = 0; i < RTD_len; i++)
      {
         if ( (RTD[i][0] == X_curr) && (RTD[i][1] == Y_curr) )
         {
            double reset = RTD[i][2];
            Delta_T = reset - resetold;
            data_out << X_curr << ' ' << Y_curr << ' ' << RTD[i][2] << ' ' << Delta_T << std::endl;
            resetold = RTD[i][2];

         }
      }
   }
   data_out.close();

}




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

   std::string Input_File  = "Muon_1GeV.txt";
   std::string Output_File = "exampledata4.txt";

   // Read out plane size in mm
   int Readout_Dim = 1000;
   int Pix_Size = 4;

   int Reset = 6000;

   std::cout << "*********************************************" << std::endl;
   std::cout << "Making the readout plane" << std::endl;
   std::vector<std::vector<int>> data2d;
   data2d = Make_Readout_plane(Readout_Dim, Pix_Size);


   std::cout << "*********************************************" << std::endl;
   std::cout << "Making the noise vector" << std::endl;
   std::vector<double> Gaussian_Noise;
   int Noise_Vector_Size = 10000;
   Gaussian_Noise = Make_Gaussian_Noise(200, 30, Noise_Vector_Size);
   //int Noise_index = 0;


   std::cout << "*********************************************" << std::endl;
   std::cout << "Loading the G4 data" << std::endl;
   // here x,y,z are in mm and edep is in MeV
   std::vector<std::vector<double>> Raw_Data_Vector;
   std::vector<int> Event_Lengths;
   Qpix::DataFileParser2(Input_File, Raw_Data_Vector, Event_Lengths);

   int Event = 0;
   std::vector<std::vector<double>> Specific_Event;
   Specific_Event =  Qpix::GetEventVector(Event ,  Event_Lengths,  Raw_Data_Vector);

   std::cout << "*********************************************" << std::endl;
   std::cout << "Making the diffused electron cloud" << std::endl;
   std::vector<Qpix::HIT> Electron_Event_Vector;
   Electron_Event_Vector = Qpix::Diffuser( Wvalue, E_vel, DiffusionL, DiffusionT, Specific_Event);

   int Event_Length = Electron_Event_Vector.size();
   std::cout << "The cloud contains " << Event_Length << " electrons" << std::endl;

   

   // vect of hit pixels 
   std::vector<std::vector<int>> Pixels_Hit;
   Pixels_Hit = Find_Unique_Pixels(Pix_Size, Event_Length, Electron_Event_Vector);

   int Pixels_Hit_Len = Pixels_Hit.size();
   std::cout << "Which hit "<< Pixels_Hit_Len << " unique pixels" << std::endl;


   std::cout << "*********************************************" << std::endl;
   std::cout << "Starting the Qpix response" << std::endl;
   std::vector<std::vector<double>> RTD;
   int Start_Time = 0, End_Time = 1000;
   RTD = Make_Reset_Response(Reset, Pix_Size, E_vel, Event_Length, Pixels_Hit_Len, Noise_Vector_Size, Start_Time, End_Time,
                               Gaussian_Noise, Pixels_Hit, data2d, Electron_Event_Vector);


   std::cout << "*********************************************" << std::endl;
   std::cout << "Writing the output file" << std::endl;
   Write_Reset_Data( Output_File, Pixels_Hit_Len, Pixels_Hit, RTD);

   

   std::cout << "done" << std::endl;

   time_req = clock() - time_req;
   double time = (float)time_req/CLOCKS_PER_SEC;
   std::cout<< "The operation took "<<time<<" Seconds"<<std::endl;
   return 0;
}
