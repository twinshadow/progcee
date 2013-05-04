#ifndef TWINSHADOW_STRING_H
#define TWINSHADOW_STRING_H

char *strrtok_r(char *str, const char delim, char *lastptr);
char *strrtok(char *str, const char delim);
void strstrip(char *str, const int count);
void memshift(int offset, void *str, const int count, size_t size);
void strshift(int offset, char *str, const int count);

#endif /* TWINSHADOW_STRING_H */
