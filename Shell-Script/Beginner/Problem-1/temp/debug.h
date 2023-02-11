#ifndef DEBUG_H
#define DEBUG_H
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ICS_RED "\x1B[1;31m"
#define ICS_GRE "\x1B[1;32m"
#define ICS_YEL "\x1B[1;33m"
#define ICS_BLU "\x1B[1;34m"
#define ICS_MAG "\x1B[0;35m"
#define ICS_NRM "\x1B[0m"
#define ICS_FATAL ICS_RED "FATAL: " ICS_NR
#define ICS_ERROR ICS_RED "ERROR: " ICS_NRM
#define ICS_WARN ICS_YEL "WARNING: " ICS_NRM
#define ICS_INFO ICS_BLU "INFO: " ICS_NRM
#define ICS_SUC ICS_GRE "SUCCESS: " ICS_NRM
#define ICS_IMPLICIT ICS_MAG "IMPLICIT LIST: " ICS_NRM
#define ICS_EXPLICIT ICS_MAG "EXPLICIT LIST: " ICS_NRM

#ifdef COLOR
#define KNRM "\x1B[0m"
#define KRED "\x1B[1;31m"
#define KGRN "\x1B[1;32m"
#define KYEL "\x1B[1;33m"
#define KBLU "\x1B[1;34m"
#define KMAG "\x1B[1;35m"
#define KCYN "\x1B[1;36m"
#define KWHT "\x1B[1;37m"
#define KBWN "\x1B[0;33m"
#else
/* Color was either not defined or Terminal did not support */
#define KNRM
#define KRED
#define KGRN
#define KYEL
#define KBLU
#define KMAG
#define KCYN
#define KWHT
#define KBWN
#endif

#define PERRORF(S) \
    perror(S);     \
    assert(false)
#define fatal(S, ...)                                      \
    fprintf(stderr, KRED "FATAL: " KNRM S, ##__VA_ARGS__); \
    assert(false)
#define error(S, ...) fprintf(stderr, KRED "ERROR: " KNRM S, ##__VA_ARGS__)

#ifdef DEBUG
#define debug(S, ...)                                                       \
    fprintf(stdout, KMAG "DEBUG: " KNRM S, ##__VA_ARGS__)
#define warn(S, ...)                                                       \
    fprintf(stderr, KYEL "WARN: %s:%s:%d " KNRM S, __FILE__, __FUNCTION__, \
            __LINE__, ##__VA_ARGS__)
#define info(S, ...)                                                       \
    fprintf(stdout, KBLU "INFO: %s:%s:%d " KNRM S, __FILE__, __FUNCTION__, \
            __LINE__, ##__VA_ARGS__)
#define success(S, ...)                                                       \
    fprintf(stdout, KGRN "SUCCESS: %s:%s:%d " KNRM S, __FILE__, __FUNCTION__, \
            __LINE__, ##__VA_ARGS__)
#else
#define debug(S, ...)
#define warn(S, ...) fprintf(stderr, KYEL "WARN: " KNRM S, ##__VA_ARGS__)
#define info(S, ...) fprintf(stdout, KBLU "INFO: " KNRM S, ##__VA_ARGS__)
#define success(S, ...) fprintf(stdout, KGRN "SUCCESS: " KNRM S, ##__VA_ARGS__)
#endif

#endif /* DEBUG_H */
