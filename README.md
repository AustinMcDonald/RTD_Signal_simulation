# Q-Pix RTD signal simulation

Simulatin to get the response of qpix in LAr

### Installing

make a build directory 

```
mkdir Build
cd Build
cmake ../
make 
```

Now move the joined libary to the Library folder

```
mv libQpix.a ../Library/.

```


Now the random number example can be ran
```
cd ../test01
make test
./test
```

This generates 2 files that you can plot with the python notebook in the test01 directory
