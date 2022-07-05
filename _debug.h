#ifndef DEBUG_H
#define DEBUG_H
/* uncomment buat debug */
// #define DEBUG
/* ~~~~~~~~~~~~~~~~~~~~~*/
#define msg(x)
#ifdef DEBUG
#undef msg
#define msg(x) printf("\033[0;31m");printf("debug: %s\n",x); printf("\033[0m")
#endif

#endif