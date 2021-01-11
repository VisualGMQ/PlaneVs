#include "header.hpp"


YesNoMsgBoxRet ShowYesNoMessageBox(string title, string text, string yes_msg, string no_msg) {
    const SDL_MessageBoxButtonData buttons[] = {
        { /* .flags, .buttonid, .text */        0, 0, yes_msg.c_str() },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, no_msg.c_str() }
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   0,   0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255,   0, 255 }
        }
    };

    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        nullptr, /* .window */
        title.c_str(), /* .title */
        text.c_str(), /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
        return YesNoMsgBoxRet::YESNOMSG_ERROR;
    SDL_Log("button id = %d", buttonid);
    if (buttonid == -1)
        return YesNoMsgBoxRet::YESNOMSG_UNKNOWN;
    if (buttonid == 0)
        return YesNoMsgBoxRet::YESNOMSG_YES;
    else if (buttonid == 1)
        return YesNoMsgBoxRet::YESNOMSG_NO;
    return YesNoMsgBoxRet::YESNOMSG_UNKNOWN;

}
