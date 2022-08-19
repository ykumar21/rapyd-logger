
# Rapyd: Async Interprocess Logger For C++  
Logging library for C++ based on C++20 

## Features
- Collect logs from different processes 
- Wait free queues for lower latency
- Custom logging targets and handlers
- Modern logging formatting

## Installation
Clone the repository and compile the source files. 
You can edit the Makefile for different compilers and compile options (defaulted to clang++). 

Note: C++20 is required for the logger to work so don't change CXX_STANDARD variable in CMake

```sh
$ git clone https://github.com/ykumar21/rapyd_logger
$ cd rapyd_logger
$ make 
```

## How To Run
Running Rapyd is easy. 
Once, the source files have been compiled, run the rapyd executable as a seperate process. 
```sh
$ make run
```

Once done, Rapyd is ready to log. Simply, register a different process with Rapyd to start logging. 

Step 1: Include Rapyd header
```c++
#include "rapyd/rapyd.h"
```
Step 2: Register Process
```c++
Rapyd::Register("MAIN_THREAD");
```
Step 3: Call the Rapyd Logger
```c++
Rapyd::Info("Hello World!");

int* ptr = malloc(sizeof(int));
Rapyd::Critical("Oh no! Pointer p points to -> %p", ptr);
```



## License

MIT

**Happy Hacking!**
