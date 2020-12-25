#include "app.hpp"
#include "game_body.hpp"

int main() {
    App app;
    Log("app created");
    
    // executable body must create after app
    GameBody body;
    Log("exec body created");

    app.SetExecBody(&body);
    app.Run();
    return 0;
}
