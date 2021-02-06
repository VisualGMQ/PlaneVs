#include "engin/app.hpp"
#include "game/welcome_stage.hpp"

int main(int argc, char** argv) {
    WelcomeStage stage;

    App app(&stage);
    Logi("main", "app created");
    app.SetTitle("PlaneVS");

    app.Run();
    return 0;
}
