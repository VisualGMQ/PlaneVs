#ifndef MOUSE_HPP
#define MOUSE_HPP
#include <SDL.h>
#include <glm/glm.hpp>

#include "engin/input/device.hpp"
using glm::ivec2;

enum MouseButtonStatue {
    MOUSE_BUTTON_RELEASE,
    MOUSE_BUTTON_PRESS
};

enum MouseButton {
    MOUSE_BUTTON_LEFT = SDL_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT = SDL_BUTTON_RIGHT
};

class Mouse final: public Device {
 public:
    static Mouse* GetInstance();

    void ReceiveEvent(SDL_Event& event) override;
    ivec2 GetPosition() const { return _position; }
    ivec2 GetMotion() const { return _motion; }
    MouseButtonStatue GetButtonStatue(MouseButton button);

 private:
    MouseButtonStatue _lbutton_status = MOUSE_BUTTON_RELEASE;
    MouseButtonStatue _rbutton_status = MOUSE_BUTTON_RELEASE;
    ivec2 _position = ivec2(0);
    ivec2 _motion = ivec2(0);

    Mouse() = default;
    static Mouse _instance;
};


#endif

