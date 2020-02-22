#include <iostream>
#include <vector>
#include <math.h>

#include "Qpix/Random.h"



namespace Qpix
{
    // this sorting need to be the column in the drift direction
    bool sortcol( const std::vector<double>& v1,const std::vector<double>& v2 ) 
    { 
        return v1[2] < v2[2]; 
    }


    std::vector< std::vector<double>> DiffuserTest(double Wvalue,double E_vel,double DiffusionL,double DiffusionT,
                                                                        const std::vector<std::vector<double>>& eventt2)
    {
    std::vector< std::vector<double>> Electron_Event_Vector;
    int event_SIZE = eventt2.size();
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

            std::vector<double> temp;
            temp.push_back(new_x);
            temp.push_back(new_y);
            temp.push_back(new_z/E_vel);                
            Electron_Event_Vector.push_back(temp);
        }
    }

    sort(Electron_Event_Vector.begin(), Electron_Event_Vector.end(),sortcol);
    return Electron_Event_Vector;
    }





    

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
                            const std::vector<std::vector<double>>& eventt2) 
    {
        std::vector<HIT> Electron_Event_Vector;

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

}