#include <stdio.h>
#include "ice_clib.h"

int main()
{
    printf("This is example subscriber.\n");
    ice_clib_init("/subscriber-bare-metal");
    struct ice_subscriber* sub = ice_clib_create_subscriber("Radar", "FrontLeft", "Counter");
    ice_clib_subscribe(sub, 10);
    const void* chunk = NULL;
    while (1)
    {
        if (ice_clib_getChunk(sub, &chunk) == -1)
            continue;
        int *sample = (int *)chunk;
        printf("Receiving: %d\n", *sample);
        ice_clib_releaseChunk(sub, chunk);
    }
    ice_clib_unsubscribe(sub);
    ice_clib_release_subscriber(sub);
    return 0;
}