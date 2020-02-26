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
    ice_pub->_pub = new iox::popo::Publisher({service, event, instance});

    return ice_pub;
}

struct ice_subscriber* ice_clib_create_subscriber(char *service, char *instance, char *event)
{
    struct ice_subscriber *ice_sub;

    ice_sub = (struct ice_subscriber *)malloc(sizeof(struct ice_subscriber));
    ice_sub->_sub = new iox::popo::Subscriber({service, event, instance});

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

int ice_clib_publish(void)
{
    return -1;
}

int ice_clib_take(void)
{
    return -1;
}

} // extern "C"