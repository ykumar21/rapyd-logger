#include <iostream> 
#include "Logger.h"
#include "Message.h"
#include "Process.h"

namespace Rapyd {
    void Register(const char* process_name) {
        Process p(process_name);
        p._register();
    }
};

int main(int argc, char** argv) {
    const char* log_message = "Hi!";
    Message< const char*  > message = Message< const char*  >::create(log_message);

    Rapyd::Register("MAIN_THREAD");
}


