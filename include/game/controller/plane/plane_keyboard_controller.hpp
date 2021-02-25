#ifndef PLANE_KEYBOARD_CONTROLLER_HPP
#define PLANE_KEYBOARD_CONTROLLER_HPP
#include <list>

#include "game/controller/plane/plane_controller.hpp"
using std::list;

class PlaneKeyboardController: public PlaneController {
 public:
    static PlaneKeyboardController* Create(Plane* plane, SDL_KeyCode up, SDL_KeyCode down, SDL_KeyCode left, SDL_KeyCode right, SDL_KeyCode fire, SDL_KeyCode bomb, SDL_KeyCode blast) {
        _controllers.emplace_back(up, down, left, right, fire, bomb, blast);
        _controllers.back().SetPlane(plane);
        return &_controllers.back();
    }

    PlaneKeyboardController(SDL_KeyCode up, SDL_KeyCode down, SDL_KeyCode left, SDL_KeyCode right, SDL_KeyCode fire, SDL_KeyCode bomb, SDL_KeyCode blast):_up(up),_down(down),_left(left),_right(right),_fire(fire),_bomb(bomb),_blast(blast) {}
    virtual ~PlaneKeyboardController() = default;

 protected:
    void Up() override;
    void Down() override;
    void Left() override;
    void Right() override;
    void Fire() override;
    void Bomb() override;
    void Blast() override;

 private:
    SDL_KeyCode _up = SDLK_UNKNOWN;
    SDL_KeyCode _left = SDLK_UNKNOWN;
    SDL_KeyCode _down = SDLK_UNKNOWN;
    SDL_KeyCode _right = SDLK_UNKNOWN;
    SDL_KeyCode _fire = SDLK_UNKNOWN;
    SDL_KeyCode _bomb = SDLK_UNKNOWN;
    SDL_KeyCode _blast = SDLK_UNKNOWN;

    static list<PlaneKeyboardController> _controllers;
};

#endif

