#ifndef DEVICE_HPP
#define DEVICE_HPP
#include <SDL.h>

class Device {
 public:
    virtual void ReceiveEvent(SDL_Event& event) = 0;
    virtual ~Device() = default;
};

#endif

