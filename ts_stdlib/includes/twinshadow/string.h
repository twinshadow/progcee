#ifndef TWINSHADOW_STRING_H
#define TWINSHADOW_STRING_H

char *strrtok_r(char *str, const char delim, char *lastptr);
char *strrtok(char *str, const char delim);
void strstrip(char *str, const int count);
void strshift(int offset, void *str, const int count, size_t size);

#endif /* TWINSHADOW_STRING_H */
