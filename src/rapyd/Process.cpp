#include "Process.h"
#include <iostream> // For printing...
#include <cstring> // For strerror
#include <sys/types.h> // For FIFO unix named pipes
#include <sys/stat.h> // For FIFO unix named pipes

Process::Process(const char* process_name) {
    this->process_name = process_name;
}

void Process::create_fifo_pipe() {
    // FIFO file path
    char* fifo = "./tmp/pipe/new";

    // Create file(FIFO)
    int ret = mkfifo(fifo, 0666);

    std::cout << "Mkfifo ret " << ret << std::endl;
    std::cout << "errno " << errno << std::endl;
    std::cout << "errno msg " << std::strerror(errno) << std::endl;
}


void Process::_register() {
    std::cout << "Registered process " << process_name << '\n';
    create_fifo_pipe();
}