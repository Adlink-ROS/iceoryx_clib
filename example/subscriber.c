#include <stdio.h>
#include "ice_clib.h"

int main() {
    printf("This is example subscriber.\n");
    ice_clib_init("/subscriber-bare-metal");
    struct ice_subscriber* sub = ice_clib_create_subscriber("Radar", "FrontLeft", "Counter");
    ice_clib_release_subscriber(sub);
    return 0;
}