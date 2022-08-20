#include "Process.h"
#include <iostream> // For printing...
#include <optional> // For optional<?>...
#include <cstring> // For strerror...
#include <sys/types.h> // For FIFO unix named pipes...
#include <sys/stat.h> // For FIFO unix named pipes...
#include <fcntl.h> // For open...

#define DEFAULT_PIPE "PTH_TO_DEFAULT_PIPE"


Process::Process(const char* process_name) {
    this->process_name = process_name;
}

std::optional<const char*> Process::create_fifo_pipe() 
{
    int     ret, fd;
    FILE    *rd_stream, *wr_stream;

    // FIFO file path
    const char* pipe_fpath = "./tmp/pipe/new";

    // Create file(FIFO)
    ret = mkfifo(pipe_fpath, 0666);
    if (ret != 0) {
        printf("Unable to create fifo; errorno=%d\n", errno);
        exit(1); /* Print error message and return */ 
    }
    printf("Created pipe %s\n", pipe_fpath);

    /* open pipe for writing only */
    fd = open( pipe_fpath, O_WRONLY | O_NONBLOCK );
    if (fd == -1) {
        printf("Error opening pipe: %s\n", pipe_fpath);
        return {};
    }

    printf( "Pipe: %s open", pipe_fpath );
    
    return pipe_fpath;
}


void Process::_register() {
    std::cout << "Registered process " << process_name << '\n';

    /* create pipe or fallback to default pipe */ 
    const char* pipe_fpath = create_fifo_pipe().value_or(DEFAULT_PIPE);
    printf("Pipe using: %s\n", pipe_fpath);
}