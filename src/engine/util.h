#ifndef __UTIL_H
#define __UTIL_H

#include <stdio.h>
#include <stdlib.h>

#define ERROR_EXIT(...) {fprintf(stderr, __VA_ARGS__); exit(EXIT_FAILURE);}

#endif // __UTIL_H
