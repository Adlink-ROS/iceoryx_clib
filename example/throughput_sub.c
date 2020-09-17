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
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include "ice_clib.h"

#define DEFAULT_SIZE 1024

void *chunk_ptr;
int chunk_size;
unsigned int received_data = 0;
struct timeval last_time, now_time;
unsigned int last_recv, now_recv;

void recv_callback(const void *chunk, void *arg)
{
    unsigned int *sample = (unsigned int *)chunk;
    if (chunk_size < *sample) {
        chunk_size = *sample;
        chunk_ptr = realloc(chunk_ptr, *sample);
    }
    memcpy(chunk_ptr, chunk, *sample);
    received_data+=*sample;
}

int main(int argc, void *argv[])
{
    printf("Subscriber for iceoryx throughput test.\n");
    chunk_size = DEFAULT_SIZE;
    chunk_ptr = malloc(chunk_size);

    ice_clib_init("/throughput-sub");
    struct ice_subscriber* sub = ice_clib_create_subscriber("Iceoryx", "Test", "Throughput");
    ice_clib_setRecvHandler(sub, recv_callback, NULL);
    ice_clib_subscribe(sub, 0);
    while (1)
    {
        last_recv = received_data;
        gettimeofday(&last_time, NULL);
        sleep(1);
        now_recv = received_data;
        gettimeofday(&now_time, NULL);
        printf("Throughput: %lu KB/sec\n", (now_recv-last_recv)/((now_time.tv_sec-last_time.tv_sec)*1024));
    }
    ice_clib_unsubscribe(sub);
    ice_clib_release_subscriber(sub);
    free(chunk_ptr);
    return 0;
}