#ifndef PIPE_H 
#define PIPE_H 

#include <sys/types.h>

typedef const char* c_str;

class Pipe {
private: 
    c_str   fifo_path;  /* Path to fifo */
    int     fd[2];      /* File descriptors for fifo */
    pid_t   childpid;   /* PID of child proc */
public: 
    bool create_fifo();
    void read_from_pipe(char *, char *, char *);
    void write_to_pipe();
};

#endif 