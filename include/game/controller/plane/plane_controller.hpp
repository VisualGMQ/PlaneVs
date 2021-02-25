#ifndef PLANE_CONTROLLER_HPP
#define PLANE_CONTROLLER_HPP
#include "game/plane.hpp"
#include "game/controller/controller.hpp"

class PlaneController: public Controller {
 public:
    void SetPlane(Plane* plane) { _plane = plane; }
    Plane* GetPlane() { return _plane; }
    virtual ~PlaneController() = default;

 private:
    Plane* _plane = nullptr;
};

#endif

