#ifndef MAIN_UTILS_H
#define MAIN_UTILS_H

#define E_CHAR	'\0'

#define TYPE_CHAR			0x0001
#define TYPE_SHORT			0x0002
#define TYPE_INT			0x0003
#define TYPE_LONG			0x0004
#define TYPE_FLOAT			0x0005
#define TYPE_DOUBLE			0x0006
#define TYPE_TEXT			0x0007

int *main_random_integer_buffer(int n, int s, int e);

#define ARRAY_SIZE(b) (sizeof(b) / sizeof(b[0]))

#endif // MAIN_UTILS_H