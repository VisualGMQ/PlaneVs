#ifndef CONTROLLER_COMMAND_HPP
#define CONTROLLER_COMMAND_HPP
#include "game/plane.hpp"

class ControllerCommand {
 public:
    virtual void Execute() = 0;
    virtual ~ControllerCommand() = default;
};

#endif

