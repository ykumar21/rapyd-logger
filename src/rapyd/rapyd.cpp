#include <iostream> 
#include "Logger.h"
#include "Message.h"

int main(int argc, char** argv) {
    const char* log_message = "Hi!";
    Message< const char*  > message = Message< const char*  >::create(log_message);
}


