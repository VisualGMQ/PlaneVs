#ifndef WELCOME_STAGE_HPP
#define WELCOME_STAGE_HPP
#include "engin/sprite.hpp"
#include "engin/sprite_sheet_cache.hpp"
#include "engin/stage.hpp"
#include "engin/bgm.hpp"
#include "engin/input/input.hpp"
#include "engin/director.hpp"
#include "game/charger.hpp"
#include "game/plane.hpp"
#include "game/controller/keyboard_controller.hpp"
using glm::mat4;
using std::to_string;

class WelcomeStage final: public Stage {
 public:
     WelcomeStage() = default;
     void Init() override;
     void Step() override;
     void Destroy() override;
     void EventHandle(SDL_Event&) override {}
     virtual ~WelcomeStage() = default;

 private:
     Plane* _enemy = nullptr;
     Plane* _plane = nullptr;
     SpriteSheetCache* _cache = nullptr;
};

#endif

