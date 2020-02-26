#include <stdio.h>
#include "ice_clib.h"

int main() {
    printf("This is example publisher.\n");
    ice_clib_init("/publisher-bare-metal");
    struct ice_publisher* pub = ice_clib_create_publisher("Radar", "FrontLeft", "Counter");
    ice_clib_release_publisher(pub);
    return 0;
}