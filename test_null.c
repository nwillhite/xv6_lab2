#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    int a = 1;
    int b, c, *p;
    p = &a;  //p points to a
    printf(1, "Printing p = &a: %d\n", *p);
    b = *p;  //dereferences a valid pointer
    printf(1, "Printing b = *p: %d\n", b);
    p = 0;
    c = *p;  //dereferences a NULL pointer -- not good!
    printf(1, "Null dereference: c = *p: %d\n", c);
    int *p2 = 0;
    printf(1, "Print new int *p2: %p\n", p2);
    exit();
}
