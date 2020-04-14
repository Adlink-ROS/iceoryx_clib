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
    void setSubCallback(SUB_CALLBACK r_callback, void *arg)
    {
        m_callback = r_callback;
        callback_arg = arg;
        _sub->setReceiveHandler(std::bind(&ice_subscriber::receiveHandler, this));
    }
private:
    SUB_CALLBACK m_callback;
    void *callback_arg;
    void receiveHandler()
    {
        const void* chunk = nullptr;

        while (_sub->getChunk(&chunk))
        {
            if (m_callback != NULL)
                m_callback(chunk, callback_arg);
            _sub->releaseChunk(chunk);
        }
    }
};

void ice_clib_init(char *name)
{
    // Create the runtime for registering with the RouDi daemon
    iox::runtime::PoshRuntime::getInstance(name);
}

struct ice_publisher* ice_clib_create_publisher(char *service, char *instance, char *event)
{
    struct ice_publisher *ice_pub;
    // CY_TODO: Maybe there is a better way to initialize the variable.
    iox::cxx::CString100 c_service;
    iox::cxx::CString100 c_instance;
    iox::cxx::CString100 c_event;
    c_service.unsafe_assign(service);
    c_instance.unsafe_assign(instance);
    c_event.unsafe_assign(event);

    ice_pub = (struct ice_publisher *)malloc(sizeof(struct ice_publisher));
    ice_pub->_pub = new iox::popo::Publisher({c_service, c_instance, c_event});

    return ice_pub;
}

struct ice_subscriber* ice_clib_create_subscriber(char *service, char *instance, char *event)
{
    struct ice_subscriber *ice_sub;
    // CY_TODO: Maybe there is a better way to initialize the variable.
    iox::cxx::CString100 c_service;
    iox::cxx::CString100 c_instance;
    iox::cxx::CString100 c_event;
    c_service.unsafe_assign(service);
    c_instance.unsafe_assign(instance);
    c_event.unsafe_assign(event);

    ice_sub = (struct ice_subscriber *)malloc(sizeof(struct ice_subscriber));
    ice_sub->_sub = new iox::popo::Subscriber({c_service, c_instance, c_event});

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
    // We need to enable this to avoid the data lost.
    // CY_TODO: Should this option be set in another function?
    ice_pub->_pub->enableDoDeliverOnSubscription();
}

void ice_clib_stopOffer(struct ice_publisher* ice_pub)
{
    ice_pub->_pub->stopOffer();
}

void* ice_clib_allocateChunk(struct ice_publisher* ice_pub, unsigned int size)
{
    return ice_pub->_pub->allocateChunk(size, true);
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

void ice_clib_setRecvHandler(struct ice_subscriber* ice_sub, SUB_CALLBACK r_callback, void *arg)
{
    ice_sub->setSubCallback(r_callback, arg);
}

void ice_clib_unsetRecvHandler(struct ice_subscriber* ice_sub)
{
    ice_sub->_sub->unsetReceiveHandler();
}

} // extern "C"