#include "filters.h"
#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H
image_t* open_img(char* filename);
char** printdir(char* dir);
char* concat(const char* nameFile);
extern const char* path;
#endif