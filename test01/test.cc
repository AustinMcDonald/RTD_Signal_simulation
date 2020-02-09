#include <iostream>
#include "Qpix/XorShift256.h"
#include "Qpix/Random.h"
#include <fstream>

//using namespace std;
//using namespace Qpix;
int main()
{
    std::ofstream myfile;
    //myfile.open ("XorShift256_raw.txt");
    //myfile.open ("XorShift256_uni.txt");
    myfile.open ("XorShift256_nor.txt");    

    //double rnd  = next();
    for(int i=0;i<10;++i)
    {
        //double rnd  = next();
        //if ( (int)(rnd * 1000) % 2 == 0){rnd -= 0.5;}
        //myfile << rnd <<std::endl;
        //std::cout<< rnd <<std::endl;
        //Qpix::RandomUniform() 
        std::cout<< Qpix::RandomUniform()  <<std::endl;

    }

    std::cout<< "break"  <<std::endl;

    for(int i=0;i<10;++i)
    {
        std::cout<< Qpix::RandomUniform()  <<std::endl;

    }

    std::cout<< "break"  <<std::endl;
    std::cout<< "break"  <<std::endl;
    std::cout<< "break"  <<std::endl;

    for(int i=0;i<10;++i)
    {
        std::cout<< Qpix::RandomNormal(5,2)  <<std::endl;

    } 

    for(int i=0;i<100000;++i)
    {
        myfile << Qpix::RandomNormal(5,2) <<std::endl;

    } 

    myfile.close();

    return 0;
}