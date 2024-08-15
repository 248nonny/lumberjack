#pragma once
// include config header
#include "lumberjack_config.h"

#define ON 1

// Holy fucking spaghetti code
// In my defense it's 3am and I just wanted it to work lmao
#define LCLOG(level, ...) \
  LUMBERJACK_LOG_ ## level (__FILE__, __LINE__, __func__, __VA_ARGS__)

#define LOGGING_FN(level, ...) \
  lumberjack::lumberjack_cut_log((lumberjack::lvl)level,__VA_ARGS__)

#if LUMBERJACK_COMPILE_NONE
  #define LUMBERJACK_LOG_ERR(...)
  #define LUMBERJACK_LOG_WRN(...)
  #define LUMBERJACK_LOG_INFO(...)
#else

  #define LUMBERJACK_LOG_ERR(...) \
    LOGGING_FN(2, __VA_ARGS__)


  #if LUMBERJACK_COMPILE_WARNINGS

    #define LUMBERJACK_LOG_WRN(...) \
      LOGGING_FN(1, __VA_ARGS__)

  #else

    #define LUMBERJACK_LOG_WRN(...)

  #endif

  #if LUMBERJACK_COMPILE_INFO

    #define LUMBERJACK_LOG_INFO(...) \
      LOGGING_FN(0, __VA_ARGS__)

  #else

    #define LUMBERJACK_LOG_INFO(...)

  #endif
#endif

namespace lumberjack {

// This enum represents the types of log messages: 
enum lvl {
  INFO,
  WRN,
  ERR
};


int init(int argc, char *argv[]);
int lumberjack_cut_log(
  lvl           level,
  const char *  filepath,
  int           linenumber,
  const char *  functionname,
  const char *  fmt,
  ...
);


void terminate();

#ifdef DEBUG
// void 
#endif

}
