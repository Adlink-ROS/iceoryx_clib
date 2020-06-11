# Introduction

The library provides C function interface for iceoryx.

# Build

You can build iceoryx_clib with colcon.

```
mkdir -p ~/ice_clib_ws/src
cd ice_clib_ws/src
git clone https://github.com/eclipse/iceoryx.git
git clone git@bitbucket.org:ROScube/iceoryx_clib.git
cd ~/ice_clib_ws
colcon build
```

# Run example

* Build code
```
cd ~/ice_clib_ws
source install/local_setup.bash
cd src/iceoryx_clib/example
mkdir build && cd build
cmake ..
make
```

* Run
```
# Run the following 3 commands in different terminals
RouDi
ice_clib_pub
ice_clib_sub
```

You can view the example code in [example folder](example).

# Debug

Iceoryx provides a good debug tools: iceoryx_introspection_client.
You can view the status of RouDi and all the publishers/subscribers.
For more detail, refer to https://github.com/eclipse/iceoryx/tree/master/iceoryx_examples/icecrystal.

```
build/iceoryx_introspection/iceoryx_introspection_client
```
