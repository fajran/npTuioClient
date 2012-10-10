#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdio.h>

#define D(format, args...) { \
  FILE* f = fopen("/tmp/npTuioClient.log", "a"); \
  fprintf(f, format "\n", ## args); \
  fflush(f); \
  fclose(f); \
}

#endif

