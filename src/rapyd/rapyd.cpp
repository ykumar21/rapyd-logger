#include <iostream> 
#include "Logger.h"
#include "Message.h"
#include "Process.h"

typedef const char* c_str;

namespace Rapyd {
    void Register(const char* process_name) {
        Process p(process_name);
        p._register();
    }

    void Write(Process *p) {
        if (p == nullptr) exit(1);
        p->write_to_pipe(1, "Hey!");
    }

};

int main(int argc, char** argv) {
    c_str log_message = "Hi!";
    Message<c_str> message = Message<c_str>::create(log_message);
    Rapyd::Register("MAIN_THREAD");
}


