#include <stdio.h>
#include <unistd.h>
#include "ice_clib.h"

int main()
{
    printf("This is example publisher.\n");
    ice_clib_init("/publisher-bare-metal");
    struct ice_publisher* pub = ice_clib_create_publisher("Radar", "FrontLeft", "Counter");
    ice_clib_offer(pub);
    for (int i = 0; i < 10; i++)
    {
        int *sample = ice_clib_allocateChunk(pub, sizeof(int));
        *sample = i;
        printf("Sending: %d\n", *sample);
        ice_clib_sendChunk(pub, sample);
        sleep(1);
    }
    ice_clib_stopOffer(pub);
    ice_clib_release_publisher(pub);
    return 0;
}