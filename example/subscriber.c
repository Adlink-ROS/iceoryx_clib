#include <stdio.h>
#include "ice_clib.h"

int main() {
    printf("This is example subscriber.\n");
    ice_clib_init();
    ice_clib_create_subscriber();
    ice_clib_take();
    return 0;
}