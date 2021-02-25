#ifndef MOUSE_HPP
#define MOUSE_HPP
#include <SDL.h>
#include <glm/glm.hpp>

#include "engin/input/device.hpp"
#include "engin/input/button.hpp"
using glm::ivec2;

namespace input {

class Mouse final: public Device {
 public:
    static Mouse* GetInstance();

    void ReceiveEvent(SDL_Event& event) override;
    ivec2 GetPosition() const { return _position; }
    ivec2 GetMotion() const { return _motion; }
    input::Button GetLeftButtonState();
    input::Button GetRightButtonState();
    void Update();

 private:
    input::ButtonState _lbutton_state = input::BUTTON_RELEASING;
    input::ButtonState _rbutton_state = input::BUTTON_RELEASING;
    ivec2 _position = ivec2(0);
    ivec2 _motion = ivec2(0);

    Mouse() = default;
    static Mouse _instance;
};

} // namespace input

#endif

