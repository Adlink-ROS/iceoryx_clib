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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "ice_clib.h"

#define DEFAULT_PAYLOAD_SIZE   1024
#define DEFAULT_BURST_SAMPLES  1000
#define DEFAULT_INTERVAL       1

int main(int argc, void *argv[])
{
    unsigned int payload_size = (argc < 2)?DEFAULT_PAYLOAD_SIZE:atoi(argv[1]);
    unsigned int burst_samples = (argc < 3)?DEFAULT_BURST_SAMPLES:atoi(argv[2]);
    unsigned int interval = (argc < 4)?DEFAULT_INTERVAL:atoi(argv[3]);

    printf("Publisher for iceoryx throughput test.\n");
    printf("Payload size is %d\n", payload_size);
    printf("Burst Samples is %d\n", burst_samples);
    printf("Time interval is %d\n", interval);

    void *test_ptr = malloc(payload_size);
    memcpy(test_ptr, &payload_size, sizeof(payload_size));

    ice_clib_init("/throughput-pub");
    struct ice_publisher* pub = ice_clib_create_publisher("Iceoryx", "Test", "Throughput");
    ice_clib_offer(pub);
    while(1) {
        for (int i = 0; i < burst_samples; i++) {
            void *chunk = ice_clib_allocateChunk(pub, payload_size);
            memcpy(chunk, test_ptr, payload_size);
            ice_clib_sendChunk(pub, chunk);
        }
        if (interval) sleep(interval);
    }
    ice_clib_stopOffer(pub);
    ice_clib_release_publisher(pub);

    free(test_ptr);
    return 0;
}