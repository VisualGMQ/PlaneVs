#include "app.hpp"
#include "game_body.hpp"

int main(int argc, char** argv) {
    App app;
    Log("app created");
    app.SetTitle("PlaneVS");

    // executable body must create after app
    GameBody body;
    Log("exec body created");

    app.SetExecBody(&body);
    app.Run();
    return 0;
}
