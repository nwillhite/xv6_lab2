#ifndef __TYPES_H
#define __TYPES_H

typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint pde_t;
typedef struct {
          uint locked;
        } lock_t;
typedef struct Semaphore Semaphore;
typedef struct spinlock spinlock;

#endif //__TYPES_H
