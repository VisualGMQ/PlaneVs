#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SDL.h>

namespace input {

enum ButtonState {
    BUTTON_PRESSED = 1,
    BUTTON_PRESSING = 2,
    BUTTON_RELEASED = 3,
    BUTTON_RELEASING = 4
};

class Button {
 public:
    explicit Button(ButtonState state):_state(state) {}

    bool IsPress() const {
        return IsPressed() || IsPressing();
    }

    bool IsPressing() const {
        return _state == BUTTON_PRESSING;
    }

    bool IsPressed() const {
        return _state == BUTTON_PRESSED;
    }

    bool IsRelease() const {
        return IsReleased() || IsReleasing();
    }

    bool IsReleasing() const {
        return _state == BUTTON_RELEASING;
    }

    bool IsReleased() const {
        return _state == BUTTON_RELEASED;
    }

 private:
    ButtonState _state;
};

ButtonState UpdateButtonState(bool is_press, const ButtonState& state);

}   // namespace input

#endif
