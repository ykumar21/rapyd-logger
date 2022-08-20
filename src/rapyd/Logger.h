#ifndef LOGGER_H 
#define LOGGER_H

#include "Message.h"

/* Allowed level types */ 
enum LoggerLevel {
    Info, 
    Warn, 
    Debug, 
    Critical
};

class Logger {
private: 
    int max_queue_size;
    static LoggerLevel log_level; 
    inline static bool append_line_feed = true;
public:  
    void linefeed(bool opt);

    template <typename T, typename... Args>
    static void Info(Message<T>, Args...);

    template <typename T, typename... Args>
    static void Debug(T, Args...);

    template <typename T> 
    void log(T, LoggerLevel);
};

template <typename T, typename... Args> 
void Logger::Info(Message<T> message, Args... args) {
    T* data_ptr = message.get_data();
    if (data_ptr != nullptr) {
        printf("[INFO]\t");
        printf(*data_ptr, args...);
        if (append_line_feed) printf("\n");
    }
}

template <typename T> 
void Logger::log(T data, LoggerLevel log_level) {
    Message<T> message(data, log_level);
}

#endif
