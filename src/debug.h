#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdio.h>

#ifdef DEBUG

#define DF(format, args...) { \
  FILE* f = fopen("/tmp/npTuioClient.log", "a"); \
  fprintf(f, format "\n", ## args); \
  fflush(f); \
  fclose(f); \
}

#define D(format, args...) printf(format "\n", ## args);

#else

#define D(format, args...)

#endif

#endif

