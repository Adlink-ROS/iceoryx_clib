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

#ifndef ICE_CLIB_H_
#define ICE_CLIB_H_

#ifdef __cplusplus
extern "C"
{
#endif

typedef void (*SUB_CALLBACK)(const void *, void *);

struct ice_publisher;
struct ice_subscriber;

enum DebugLevel
{
    DebugOff = 0,
    DebugFatal,
    DebugError,
    DebugWarn,
    DebugInfo,
    DebugDebug,
    DebugVerbose
};

void ice_clib_setDebugLevel(enum DebugLevel debuglevel);
void ice_clib_init(char *name);
struct ice_publisher* ice_clib_create_publisher(char *service, char *instance, char *event);
struct ice_subscriber* ice_clib_create_subscriber(char *service, char *instance, char *event);
void ice_clib_release_publisher(struct ice_publisher* handler);
void ice_clib_release_subscriber(struct ice_subscriber* handler);
void ice_clib_offer(struct ice_publisher* ice_pub);
void ice_clib_stopOffer(struct ice_publisher* ice_pub);
void* ice_clib_allocateChunk(struct ice_publisher* ice_pub, unsigned int size);
void ice_clib_sendChunk(struct ice_publisher* ice_pub, const void* const payload);
int ice_clib_hasSubscriber(struct ice_publisher* ice_pub);
void ice_clib_subscribe(struct ice_subscriber* ice_sub, unsigned int cacheSize);
void ice_clib_unsubscribe(struct ice_subscriber* ice_sub);
int ice_clib_getChunk(struct ice_subscriber* ice_sub, const void** chunk);
void ice_clib_releaseChunk(struct ice_subscriber* ice_sub, const void* chunk);
void ice_clib_setRecvHandler(struct ice_subscriber* ice_sub, SUB_CALLBACK r_callback, void *arg);
void ice_clib_unsetRecvHandler(struct ice_subscriber* ice_sub);

#ifdef __cplusplus
}
#endif

#endif // ICE_CLIB_H_