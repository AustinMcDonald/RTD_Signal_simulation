#ifndef PIXELRESPONSE_H_
#define PIXELRESPONSE_H_

#include <iostream>
#include <vector>
#include <fstream>
//#include <math.h>
#include "Qpix/ElectronHandler.h"


namespace Qpix
{

    std::vector<std::vector<int>> Make_Readout_plane(int Readout_Dim, int Pix_Size);

    std::vector<std::vector<int>> Find_Unique_Pixels(int Pix_Size, int Event_Length, std::vector<Qpix::HIT> Electron_Event_Vector);

    std::vector<std::vector<double>> Make_Reset_Response(int Reset, int Pix_Size, double E_vel, int Event_Length, 
                                                        int Pixels_Hit_Len, int Noise_Vector_Size, int Start_Time, int End_Time,
                                                        std::vector<double> Gaussian_Noise, std::vector<std::vector<int>> Pixels_Hit,
                                                        std::vector<std::vector<int>> data2d, std::vector<Qpix::HIT> Electron_Event_Vector);

    void Write_Reset_Data(std::string Output_File, int Pixels_Hit_Len, std::vector<std::vector<int>> Pixels_Hit, std::vector<std::vector<double>> RTD);


}

#endif