#include <iostream> 
#include "Logger.h"
#include "Message.h"
#include "Process.h"

typedef const char* c_str;

class Rapyd {
private:   
    
public:
    static Process Register(c_str proc_name) {
        printf("Registering %s...\n", proc_name);
        Process proc(proc_name);
        proc._register();
        return proc;
    }

    static void Write(Process p) {
        p.write_to_pipe("Hey!");
    }
};

int main(int argc, char** argv) {
    c_str log_message = "Hi!";
    Message<c_str> message = Message<c_str>::create(log_message);
    Process proc = Rapyd::Register("MAIN_THREAD");
    Rapyd::Write(proc);
}


