#include <time.h>

typedef struct __attribute__ ((__packed__)) t_bitfield
{
    unsigned x:1;
} bitfield;

double timestamp(void);