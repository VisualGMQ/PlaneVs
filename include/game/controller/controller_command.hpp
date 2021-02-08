#ifndef CONTROLLER_COMMAND_HPP
#define CONTROLLER_COMMAND_HPP
#include "game/plane.hpp"

class ControllerCommand {
 public:
    virtual void Execute(Plane* plane) = 0;
    virtual ~ControllerCommand() = default;
};

#endif

