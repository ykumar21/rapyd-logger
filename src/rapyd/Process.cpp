#include "Process.h"
#include <iostream> // For printing...
#include <optional> // For optional<?>...
#include <cstring> // For strerror...
#include <sys/types.h> // For types...
#include <sys/stat.h> // For FIFO unix named pipes...
#include <fcntl.h> // For open...
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef const char* c_str;

#define DEFAULT_PIPE "PTH_TO_DEFAULT_PIPE"

#define FIFO_PERM_ALL

#ifdef FIFO_PERM_ALL
    #define FIFO_PERM 0777
#endif
#ifdef FIFO_PERM_USER
    #define FIFO_PERM 066
#endif

Process::Process(c_str process_name) {
    this->process_name = process_name;
}

void Process::read_from_pipe(int fd) {
    int     chr;
    FILE    *rd_stream;
    
    rd_stream = fdopen( fd, "r" );
    while ((chr = fgetc(rd_stream)) != EOF) 
        putchar(chr);
        
    fclose(rd_stream);
}

void Process::write_to_pipe(int fd) {
    FILE    *wr_stream;

    wr_stream = fdopen( fd, "w" );
    fprintf(wr_stream, "hello world\n");
    fprintf(wr_stream, "goodbye, world\n");
    fclose(wr_stream);
}

std::optional<c_str> Process::create_fifo_pipe() 
{
    int     ret, fd[2];
    FILE    *rd_stream, *wr_stream;
    c_str   pipe_fpath;
    pid_t   childpid;
    
    // FIFO file path
    pipe_fpath = "./tmp/pipe/nw";

    // Create file(FIFO)
    ret = pipe(fd); 
    if (ret != 0) {
        fprintf(stderr, "Unable to create fifo; errorno=%d\n", errno);
        exit(1); /* Print error message and return */ 
    }

    printf("Created pipe %s\n", pipe_fpath);
    childpid = fork();
    
    if (childpid == static_cast<pid_t>(0)) {
        /* This is the child process
           Close other end first.  */
        printf("Closing input side of pipe\n");
        /* close output side of pipe */
        close(fd[1]); 
        read_from_pipe(fd[0]);
    } else if (childpid < static_cast<pid_t>( 0 )) {
        perror("fork error");
        exit(1);
    } else {
        /* This is the parent process. */ 
        printf("Closing output side of pipe\n");
        /* close input side of pipe */ 
        close(fd[0]);
        write_to_pipe(fd[1]);
    }

    return pipe_fpath;
}


void Process::_register() {
    std::cout << "Registered process " << process_name << '\n';

    /* create pipe or fallback to default pipe */ 
    const char* pipe_fpath = create_fifo_pipe().value_or(DEFAULT_PIPE);
    printf("Pipe using: %s\n", pipe_fpath);
}