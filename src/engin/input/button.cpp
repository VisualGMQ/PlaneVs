#include "engin/input/button.hpp"
using input::ButtonState;

ButtonState input::UpdateButtonState(bool is_press, const ButtonState& state) {
    if (is_press) {
        if (state == BUTTON_PRESSED) {
            return BUTTON_PRESSING;
        } else if (state == BUTTON_RELEASING ||
                   state == BUTTON_RELEASED) {
            return BUTTON_PRESSED;
        } else {
            return BUTTON_PRESSING;
        }
    } else {
        if (state == BUTTON_RELEASED) {
            return BUTTON_RELEASING;
        } else if (state == BUTTON_PRESSED ||
                   state == BUTTON_PRESSING) {
            return BUTTON_RELEASED;
        } else {
            return BUTTON_RELEASING;
        }
    }
}
