#ifndef PROCESS_H
#define PROCESS_H

#include <optional> // For optional<?>
#include <stdio.h> 

typedef const char* c_str;

/* Process for logging */ 
class Process {
private:
    c_str   process_name;
    int     fd[2];
    pid_t   childpid;    

    std::optional<const char*> create_fifo_pipe();
    void read_from_pipe(int);
    void write_to_pipe(int);
public:
    Process(const char* process_name);
    const char* get_process_name() {
        return process_name;
    }
    void _register();

    int* get_fd() {
        return this->fd;
    }

    void set_fd(int *fd) {
        fprintf(stderr, "Dont set fd.. Call create_fifo_pipe");
    }

    pid_t get_childpid() {
        return this->childpid;
    }

    void set_childpid() {
        fprintf(stderr, "Dont set pid.. call create_fifo_pipe");
    }
};

#endif