#ifndef TWINSHADOW_STRING_H
#define TWINSHADOW_STRING_H

char *strrtok_r(char *str, const char delim, char *lastptr);
char *strrtok(char *str, const char delim);
void strstrip(char *str, const int count);
void memshift(int32_t offset, void *ptr, const size_t count, size_t size);
void strshift(int32_t offset, char *str, const size_t count);
char *ts_strndup(const char *src, size_t len);
char *ts_strdup(const char *src);

#endif /* TWINSHADOW_STRING_H */
