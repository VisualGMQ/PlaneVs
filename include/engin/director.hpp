#ifndef DIRECTOR_HPP
#define DIRECTOR_HPP
#include <vector>
#include <map>

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
    static Director* GetInstance() {
        if (!director)
            director = new Director;
        return director;
    }

    GameStatus GetGameStatus() const { return _status; }
    void SetGameStatus(GameStatus status) { _status = status; }
    void Exit();
    void Update();
    void SetStage(Stage* stage);
    bool ShouldExit() const;
    void Destroy();

 private:
    GameStatus _status = STOPPING;
    Stage* _stage = nullptr;

    static Director* director;

    Director() = default;
};

#endif

