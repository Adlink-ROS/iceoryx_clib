// Copyright 2020 ADLINK Technology. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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