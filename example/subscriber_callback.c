#include <stdio.h>
#include <unistd.h>
#include "ice_clib.h"

void recv_callback(const void *chunk)
{
    int *sample = (int *)chunk;
    printf("Receiving: %d\n", *sample);
}

int main()
{
    printf("This is example subscriber with callback.\n");
    ice_clib_init("/subscriber-callback");
    struct ice_subscriber* sub = ice_clib_create_subscriber("Radar", "FrontLeft", "Counter");
    ice_clib_setRecvHandler(sub, recv_callback);
    ice_clib_subscribe(sub, 10);
    while (1)
    {
        sleep(1);
    }
    ice_clib_unsubscribe(sub);
    ice_clib_release_subscriber(sub);
    return 0;
}