# KandR-GoogleTesting
Google Test the C Answer Book and K&R lessons as an assumed baseline

-----------------------------------------------------------------------------------------------
Install Google Test on Ubuntu
Start by installing the gtest development package:

sudo apt-get install libgtest-dev
Note that this package only install source files. You have to compile the code yourself to create the necessary library files. These source files should be located at /usr/src/gtest. Browse to this folder and use cmake to compile the library:

sudo apt-get install cmake # install cmake
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
 
# copy or symlink libgtest.a and libgtest_main.a to your /usr/lib folder
sudo cp *.a /usr/lib

-----------------------------------------------------------------------------------------------
Sync to github.com/stevemac321/KandR-GoogleTesting

cmake -DCMAKE_BUILD_TYPE=Debug CMakeLists.txt
make
./runTests

Watch my video (todo)

References:
http://code.google.com/p/googletest/wiki/Documentation
https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/
https://stackoverflow.com/questions/48589258/does-gtest-support-file-comparison
http://www.ibm.com/developerworks/aix/library/au-googletestingframework.html
