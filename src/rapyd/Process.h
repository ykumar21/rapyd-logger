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

    /* Create fifo pipe */ 
    std::optional<c_str> create_fifo_pipe();
public:
    /* default constructor */ 
    Process(const char* process_name);

    /* register process for logging */ 
    void _register();

    /* print buffer for debug */
    void print_buf(char *, char *);

    /* Getters and setters */
    const char* get_process_name() { return process_name; }

    int* get_fd() { return this->fd; }
    
    void set_fd(int *fd) { fprintf(stderr, "Dont set fd.. Call create_fifo_pipe"); }
    
    pid_t get_childpid() { return this->childpid; }
    
    void set_childpid() { fprintf(stderr, "Dont set pid.. call create_fifo_pipe"); }

    /* read data from pipe */ 
    void read_from_pipe(int);

    /* write data to pipe */ 
    void write_to_pipe(int, c_str);
};

#endif