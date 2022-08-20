#ifndef PROCESS_H
#define PROCESS_H

/* Process for logging */ 
class Process {
private:
    const char* process_name; 
    void create_fifo_pipe();
public:
    Process(const char* process_name);
    const char* get_process_name() {
        return process_name;
    }
    void _register();

};

#endif