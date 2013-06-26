#ifndef TWINSHADOW_STRING_H
#define TWINSHADOW_STRING_H

#include <string.h>
#include <stdint.h>

char *ts_strrtok_r(char *str, const char delim, char *lastptr);
char *ts_strrtok(char *str, const char delim);
void ts_strnstrip(char *str, size_t len);
void ts_strstrip(char *str);
void ts_memshift(int32_t offset, void *ptr, size_t len);
void ts_strshift(int32_t offset, char *str);
char *ts_strndup(const char *src, size_t len);
char *ts_strdup(const char *src);
void ts_strnrev(char *str, size_t len);
void ts_strrev(char *str);

#endif /* TWINSHADOW_STRING_H */
