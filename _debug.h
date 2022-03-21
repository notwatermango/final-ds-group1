#ifndef DEBUG_H
#define DEBUG_H
/* uncomment buat debug */
// #define DEBUG
/* ~~~~~~~~~~~~~~~~~~~~~*/
#define msg(x)
#ifdef DEBUG
#undef msg
#define msg(x) puts(x)
#endif

#endif