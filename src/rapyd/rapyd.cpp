#include <iostream> 
#include "Logger.h"
#include "Message.h"
#include "Process.h"

typedef const char* c_str;

namespace Rapyd {
    Process Register(const char* process_name) {
        Process proc(process_name);
        proc._register();
        return proc;
    }

    void Write(Process p) {
        p.write_to_pipe("Hey!");
    }

};

int main(int argc, char** argv) {
    c_str log_message = "Hi!";
    Message<c_str> message = Message<c_str>::create(log_message);
    Process proc = Rapyd::Register("MAIN_THREAD");
    Rapyd::Write(proc);
}


