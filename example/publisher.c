#include <stdio.h>
#include "ice_clib.h"

int main() {
    printf("This is example publisher.\n");
    ice_clib_init();
    ice_clib_create_publisher();
    ice_clib_publish();
    return 0;
}