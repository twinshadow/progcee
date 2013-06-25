#ifndef TWINSHADOW_STRING_H
#define TWINSHADOW_STRING_H

char *strrtok_r(char *str, const char delim, char *lastptr);
char *strrtok(char *str, const char delim);
void strstrip(char *str, const int count);
void strshift(int offset, char *str, const int count);
char *ts_strndup(const char *src, size_t len);
char *ts_strdup(const char *src);

#endif /* TWINSHADOW_STRING_H */
