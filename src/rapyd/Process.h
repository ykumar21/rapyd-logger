#ifndef PROCESS_H
#define PROCESS_H

#include <optional> // For optional<?>
#include <stdio.h> 

typedef const char* c_str;

#define RDBUF_SIZE 80 /* read buffer size */ 


/* Process for logging */ 
class Process {
private:
    c_str   process_name;
    int     fd[2];
    pid_t   childpid;   
    char    rd_buf[RDBUF_SIZE];
    char    *buf_p=rd_buf, *buf_end = &rd_buf[RDBUF_SIZE-1]; /* buffer pointers  */
     

    /* Create fifo pipe */ 
    std::optional<c_str> create_fifo_pipe();

    /* Flush the read buffer */ 
    void flush_rdbuf();
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
    void read_from_pipe();

    /* write data to pipe */ 
    void write_to_pipe(c_str);
};

#endif