/**
 * @file LoggerLevel.h
 * @author Yashwardhann Kumar
 * @brief Custom Logger Level with Annotations
 * @version 0.1
 * @date 2022-08-19
 * 
 * Enable for custom logger level with annotations (old version)
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef LOGGER_LEVEL_H
#define LOGGER_LEVEL_H

namespace LoggerLevel_ {
    #define SOME_ENUM(DO) \
    DO(Info) \
    DO(Warn) \
    DO(Critical)

    #define MAKE_ENUM(VAR) VAR,
    enum Level {
        SOME_ENUM(MAKE_ENUM)
    };

    #define MAKE_STRINGS(VAR) #VAR,
    static const char* const LoggerLevelAnnotations[] = {
        SOME_ENUM(MAKE_STRINGS)
    };

    static const char* get_level_annotation(Level level) {
        return LoggerLevelAnnotations[level];
    } 
};


#endif 
