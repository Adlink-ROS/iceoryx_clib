#include "iceoryx_posh/popo/publisher.hpp"
#include "iceoryx_posh/popo/subscriber.hpp"
#include "iceoryx_posh/runtime/posh_runtime.hpp"
#include "ice_clib.h"

extern "C"
{

struct ice_publisher
{
    iox::popo::Publisher * _pub;
};

struct ice_subscriber
{
    iox::popo::Subscriber * _sub;
};

void ice_clib_init(char *name)
{
    // Create the runtime for registering with the RouDi daemon
    iox::runtime::PoshRuntime::getInstance(name);
}

struct ice_publisher* ice_clib_create_publisher(char *service, char *instance, char *event)
{
    struct ice_publisher *ice_pub;

    ice_pub = (struct ice_publisher *)malloc(sizeof(struct ice_publisher));
    ice_pub->_pub = new iox::popo::Publisher({service, instance, event});

    return ice_pub;
}

struct ice_subscriber* ice_clib_create_subscriber(char *service, char *instance, char *event)
{
    struct ice_subscriber *ice_sub;

    ice_sub = (struct ice_subscriber *)malloc(sizeof(struct ice_subscriber));
    ice_sub->_sub = new iox::popo::Subscriber({service, instance, event});

    return ice_sub;
}

void ice_clib_release_publisher(struct ice_publisher* handler)
{
    if (handler != NULL)
    {
        if (handler->_pub != NULL)
        {
            delete handler->_pub;
        }
        free(handler);
    }
}

void ice_clib_release_subscriber(struct ice_subscriber* handler)
{
    if (handler != NULL)
    {
        if (handler->_sub != NULL)
        {
            delete handler->_sub;
        }
        free(handler);
    }
}

void ice_clib_offer(struct ice_publisher* ice_pub)
{
    ice_pub->_pub->offer();
}

void ice_clib_stopOffer(struct ice_publisher* ice_pub)
{
    ice_pub->_pub->stopOffer();
}

void* ice_clib_allocateChunk(struct ice_publisher* ice_pub, unsigned int size)
{
    return ice_pub->_pub->allocateChunk(size);
}

void ice_clib_sendChunk(struct ice_publisher* ice_pub, const void* const payload)
{
    ice_pub->_pub->sendChunk(payload);
}

void ice_clib_subscribe(struct ice_subscriber* ice_sub, unsigned int cacheSize)
{
    ice_sub->_sub->subscribe(cacheSize);
}

void ice_clib_unsubscribe(struct ice_subscriber* ice_sub)
{
    ice_sub->_sub->unsubscribe();
}

int ice_clib_getChunk(struct ice_subscriber* ice_sub, const void** chunk)
{
    if (iox::popo::SubscriptionState::SUBSCRIBED != ice_sub->_sub->getSubscriptionState())
    {
        // Waiting for publisher
        return -1;
    }
    if (!ice_sub->_sub->getChunk(chunk))
    {
        return -1;
    }
    return 0;
}

void ice_clib_releaseChunk(struct ice_subscriber* ice_sub, const void* chunk)
{
    ice_sub->_sub->releaseChunk(chunk);
}

} // extern "C"