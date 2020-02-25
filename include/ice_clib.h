#ifndef ICE_CLIB_H_
#define ICE_CLIB_H_

#ifdef __cplusplus
extern "C"
{
#endif

int ice_clib_init(void);
int ice_clib_create_publisher(void);
int ice_clib_create_subscriber(void);
int ice_clib_publish(void);
int ice_clib_take(void);

#ifdef __cplusplus
}
#endif

#endif // ICE_CLIB_H_