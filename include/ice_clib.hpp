#ifndef ICE_CLIB_HPP_
#define ICE_CLIB_HPP_

extern "C"
{
int ice_clib_init(void);
int ice_clib_create_publisher(void);
int ice_clib_create_subscriber(void);
int ice_clib_publish(void);
int ice_clib_take(void);
}

#endif // ICE_CLIB_HPP_