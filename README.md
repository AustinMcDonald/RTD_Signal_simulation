well here it is 

to run it first set up the enviorment 
source setup.sh

now to build 
cd Build
cmake ../
make

and move the lib
mv libQpix.a ../Library/.

Now to run the random number example
cd ../test01

make test
./test

