#include "Qpix/XorShift256.h"
#include <math.h>

namespace Qpix
{
    double RandomUniform() 
    {
        double XorShift  = next();
        if ( (int)(XorShift * 1000) % 2 == 0){XorShift -= 0.5;}
        return XorShift; 
    }


    double RandomNormal(double m, double s)	/* normal random variate generator */
    {				        /* mean m, standard deviation s */
        double x1, x2, w, y1;
        static double y2;
        static int use_last = 0;

        if (use_last)		        /* use value from previous call */
        {
            y1 = y2;
            use_last = 0;
        }
        else
        {
            do {
                x1 = 2.0 * RandomUniform()  - 1.0;
                x2 = 2.0 * RandomUniform()  - 1.0;
                w = x1 * x1 + x2 * x2;
            } while ( w >= 1.0 );

            w = sqrt( (-2.0 * log( w ) ) / w );
            y1 = x1 * w;
            y2 = x2 * w;
            use_last = 1;
        }

        return( m + y1 * s );
    }

}