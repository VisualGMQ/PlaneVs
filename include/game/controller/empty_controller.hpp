#ifndef EMPTY_CONTROLLER_HPP
#define EMPTY_CONTROLLER_HPP
#include "engin/controller.hpp"

class EmptyController: public Controller {
 public:
     void OnUp() override {}
     void OnDown() override {}
     void OnLeft() override {}
     void OnRight() override {}
     void OnShoot() override {}
     void OnBomb() override {}
     void OnBlast() override {}
     void OnEcs() override {}

     virtual ~EmptyController() = default;
};

#endif

