# Challenge2

The aim of this challenge is to take two folders from the command line and copy all files and subdirectories from the first folder to the second. It also takes an optional files extension and when copying files it excludes all files with that extension. An example result is given below:  
Original folder:    
```
\home\user\project
|--main
|    |--main.cpp
|    |--test
|    |    |--test.cpp
|    |    +--testfunc.h
|    +--include
|         +--header.h
+--other
     +--readme.txt
```
Invocation:  
```
./Challenge2 \home\user\project \home\user\project-copy .h
```
Destination folder:  
```
\home\user\project-copy
|--main
|    |--main.cpp
|    |--test
|    |    +-test.cpp
|    +--include
+--other
     +--readme.txt
```
