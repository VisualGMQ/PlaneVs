#ifndef PLANE_CONTROLLER_HPP
#define PLANE_CONTROLLER_HPP
#include "game/controller/controller.hpp"

class PlaneController: public Controller {
 public:
    PlaneController();
    void SetPlane(Plane* plane) { _plane = plane; }

 private:
    Plane* _plane = nullptr;
};

#endif

