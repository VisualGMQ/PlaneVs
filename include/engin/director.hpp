#ifndef DIRECTOR_HPP
#define DIRECTOR_HPP
#include <vector>
#include <map>

#include "base/config.hpp"
#include "engin/stage.hpp"
#include "engin/input/input.hpp"

using std::vector;

enum GameStatus {
    PLAYING,
    PAUSING,
    STOPPING
};

class Director final {
 public:
    static void Init();
    static Director* GetInstance() {
        if (!director)
            Loge("static Director::GetInstance", "Director not init, please call Director::Init() first");
        return director;
    }

    GameStatus GetGameStatus() const { return _status; }
    void SetGameStatus(GameStatus status) { _status = status; }
    void Exit();
    void Update();
    void SetRenderTargetToDefault();
    void RenderClear(const icolor&);
    void RenderPresent();
    void SetStage(Stage* stage);
    SDL_Window* GetWindow() { return _window; }
    SDL_Renderer* GetRender() { return _render; }
    bool ShouldExit() const;
    void StageDestroy();
    void Destroy();

 private:
    GameStatus _status = STOPPING;
    Stage* _stage = nullptr;
    SDL_Window* _window = nullptr;
    SDL_Renderer* _render = nullptr;
    SDL_Texture* _canva = nullptr;

    static Director* director;

    Director() = default;
};

#endif

