
#include "lumberjack.h"
#include <ctime>
#include <stdio.h>
#include <stdarg.h>

#if (OS_NAME == Windows)
  #include <Windows.h>
#endif

#if (OS_NAME == Unix)
  #include <filesystem>
#endif

namespace lumberjack {


char filename[256] = {};
FILE *logfile = nullptr;

int init(int argc, char *argv[]) {

  // Get current date/time
  std::time_t current_time;
  std::time(&current_time);

  char dt[256] = {};
  strftime(dt, 256, "%y-%m-%d_%H.%M.%S", localtime(&current_time));



  #if(OS_NAME == Windows)
  CreateDirectory("log", NULL);
    sprintf(filename, ".\\log\\%s.log", dt);
  #elif (OS_NAME == Unix)
    // init logging dir if it doesn't exist.
    fs::create_directory("log");
    sprintf(filename, fs::path("log/%s.log").c_str(), dt);
  #endif
  
  printf("filename: %s\n", filename);
  // open logfile
  logfile = fopen(filename, "a");
  
  // print log intro message
  lumberjack_cut_log(lvl::INFO, "init", 0, "init", "Started Lumberjack Logging\n%s\n-------\n\n\n",dt);
  // fprintf(logfile, "Started Lumberjack Logging\n%s\n-------\n\n\n",dt);

  return 1;
}


const char * predicate_expander(lvl level) {
  switch (level) {
    case lvl::INFO:
      return "INFO";
    case lvl::WRN:
      return "WARNING";
    case lvl::ERR:
      return "ERROR";
    default:
      return "";
  }
}

const char * color(lvl level) {
  switch (level) {
    case lvl::INFO:
      return "\e[1;34m";
    case lvl::WRN:
      return "\e[1;33m";
    case lvl::ERR:
      return "\e[1;31m";
    default:
      return "";
  }
}

// Cut log function (a.k.a. log something)
int lumberjack_cut_log(
  lvl           level,
  const char *  filename,
  int           linenumber,
  const char *  functionname,
  const char *  fmt,
  ...
) {

  va_list args;
  va_start(args, fmt);

  char message[256] = {};
  vsprintf(message, fmt, args);

  
  #if(OS_NAME == Unix)

  printf("%s%s\e[m\n%s, line %d, %s():\n%s\n\n",
    color(level),
    predicate_expander(level),
    filename,
    linenumber,
    functionname,
    message
  );

  return fprintf(
    logfile,
    "%s%s\e[m\n%s, line %d, %s():\n%s\n\n",
    color(level),
    predicate_expander(level),
    filename,
    linenumber,
    functionname,
    message
  );
  #endif()

  #if(OS_NAME == Windows)
  printf("%s\n%s, line %d, %s():\n%s\n\n",
      predicate_expander(level),
      filename,
      linenumber,
      functionname,
      message
  );

  return fprintf(
      logfile,
      "%s\n%s, line %d, %s():\n%s\n\n",
      predicate_expander(level),
      filename,
      linenumber,
      functionname,
      message
  );
  #endif
}

void terminate() {
  fclose(logfile);
}


}
