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