#ifndef ICE_CLIB_H_
#define ICE_CLIB_H_

#ifdef __cplusplus
extern "C"
{
#endif

struct ice_publisher;
struct ice_subscriber;

void ice_clib_init(char *name);
struct ice_publisher* ice_clib_create_publisher(char *service, char *instance, char *event);
struct ice_subscriber* ice_clib_create_subscriber(char *service, char *instance, char *event);
void ice_clib_release_publisher(struct ice_publisher* handler);
void ice_clib_release_subscriber(struct ice_subscriber* handler);
int ice_clib_publish(void);
int ice_clib_take(void);

#ifdef __cplusplus
}
#endif

#endif // ICE_CLIB_H_