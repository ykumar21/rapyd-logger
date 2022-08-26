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

#define FIFO_PERM_RECO

#ifdef FIFO_PERM_RECO 
#define FIFO_PERM 0760 /* rwxrw---- */
#endif

#ifdef FIFO_PERM_USER
#define FIFO_PERM 0666 /* rw-rw-rw- */
#endif



Process::Process(c_str process_name) {
    this->process_name = process_name;
}

void Process::print_buf(char *buf, char *buf_p) {
    char *buf_trav = buf;
    while ( buf_trav != buf_p ) {
        std::cout << *buf_trav;
        ++buf_trav;
    }
}

void Process::flush_rdbuf() {
    /* move buffer pointer to first position */ 
    buf_p = rd_buf;
}

void Process::read_from_pipe() {
    int     chr, file = fd[0];
    FILE    *rd_stream;
    
    printf("buf p: %p, buf end: %p\n", buf_p, buf_end);

    rd_stream = fdopen( file, "r" );
    while ((chr = fgetc(rd_stream)) != EOF) {
        if (buf_p <= buf_end) {
            *buf_p = (char) chr; ++buf_p;
        } else {
            printf("Buffer full!\n");
            flush_rdbuf();
            break;
        }
    }
    print_buf(rd_buf, buf_p);
    fclose(rd_stream);
}

void Process::write_to_pipe(c_str message) {
    FILE    *wr_stream;
    int     file = fd[1];

    wr_stream = fdopen( file, "w" );
    fprintf(wr_stream, "%s\n", message);
    fclose(wr_stream);
}

std::optional<c_str> Process::create_fifo_pipe() 
{
    int     ret;
    FILE    *rd_stream, *wr_stream;
    c_str   pipe_fpath;
    pid_t   childpid;
    
    // FIFO file path
    pipe_fpath = "./tmp/pipe/nw1";

    // Create file(FIFO)
    ret = mkfifo(pipe_fpath, FIFO_PERM);
    
    printf("----- FD ------\n");
    printf("\tRead: %d\n", fd[0]);
    printf("\tWrite: %d\n", fd[1]);

    if (ret != 0) {
        fprintf(stderr, "Unable to create fifo; errorno=%d\n", errno);
        exit(1); /* Print error message and return */ 
    }

    while (true) {
        /* blocking call to open fifo in read only */ 
        fd[0] = open(pipe_fpath, O_RDONLY);
        read_from_pipe();
    }
    // if (childpid == static_cast<pid_t>(0)) {
    //     /* This is the child process
    //        Close other end first.  */
    //     printf("=== CHILD ===\n");
    //     /* close output side of pipe */
    //     close(fd[1]); 
    //     read_from_pipe();
    // } else if (childpid < static_cast<pid_t>( 0 )) {
    //     perror("fork error");
    //     exit(1);
    // } else {
    //     /* This is the parent process. */ 
    //       printf("=== %s ===\n", this->process_name);
    //     /* close input side of pipe */ 
    //     close(fd[0]);
    //     write_to_pipe("Hey!");
    // }

    return pipe_fpath;
}


void Process::_register() {
    std::cout << "Registered process " << process_name << '\n';
    /* create pipe or fallback to default pipe */ 
    const char* pipe_fpath = create_fifo_pipe().value_or(DEFAULT_PIPE);
}