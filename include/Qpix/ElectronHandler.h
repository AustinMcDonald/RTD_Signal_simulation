
#include <iostream>
#include <vector>
#include <math.h>

#include "Qpix/Random.h"


namespace Qpix
{
    bool sortcol( const std::vector<double>& v1,const std::vector<double>& v2 );

    std::vector< std::vector<double>> DiffuserTest(double Wvalue,double E_vel,double DiffusionL,double DiffusionT,
                                                                        const std::vector<std::vector<double>>& eventt2);

}