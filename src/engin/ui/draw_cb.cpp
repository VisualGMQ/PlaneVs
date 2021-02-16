#include "engin/ui/ui.hpp"
using imgui::uistate;
using imgui::gText;
using imgui::gRender;
using imgui::IDType;
using imgui::EventType;

void imgui::DefaultButtonDrawCb(IDType id, EventType evt, string text, int x, int y, int w, int h, void* param) {
    SDL_Color fill_color = {225, 255, 225, 255},
              hover_color = {150, 150, 150, 255},
              click_color = {100, 100, 100, 255},
              board_color = {0, 0, 0, 255},
              font_color = {0, 0, 0, 255},
              click_font_color = {255, 255, 255, 255};
    SDL_Color* c = &fill_color;
    SDL_Rect rect = {x, y, w, h};
    gText->SetColor(font_color.r, font_color.g, font_color.b, font_color.a);
    gText->SetText(text.c_str());
    if (evt == imgui::EVENT_MOUSELEFT_PRESSING || evt == imgui::EVENT_BUTTON_CLICK) {
        c = &click_color;
        gText->SetColor(click_font_color.r, click_font_color.g, click_font_color.b, click_font_color.a);
    }
    if (evt == imgui::EVENT_HOVER) {
        c = &hover_color;
    }
    SDL_SetRenderDrawColor(gRender, c->r, c->g, c->b, c->a);
    SDL_RenderFillRect(gRender, &rect);
    SDL_SetRenderDrawColor(gRender, board_color.r, board_color.g, board_color.b, board_color.a);
    SDL_RenderDrawRect(gRender, &rect);
    gText->Draw(x+w/2, y+h/2);
}

void imgui::DefaultScrollbarDrawCb(IDType id, imgui::ScrollbarDirection direction, EventType event, int x, int y, int len, int min, int max, int value, int button_len, void* param) {
    const int actual_len = len - button_len;
    int button_offset = static_cast<float>(value)/(max-min)*actual_len;
    int button_width = ScrollbarWidth;
    
    const SDL_Color scroll_color = {225, 225, 225, 255};
    const SDL_Color board_color = {0, 0, 0, 255};
    const SDL_Color button_color = {150, 150, 150, 255};
    const SDL_Color button_hightlight_color = {180, 180, 180, 255};
    const SDL_Color* button_draw_color = &button_color,
                    *scroll_draw_color = &scroll_color;

    SDL_Rect scroll_rect = {x, y, 0, 0},
             button_rect;
    if (direction == SCROLLBAR_VERTICAL) {
        scroll_rect.w = ScrollbarWidth;
        scroll_rect.h = len;
        button_rect.w = button_width;
        button_rect.x = x;
        button_rect.y = button_offset+y;
        button_rect.h = button_len;
    } else {
        scroll_rect.w = len;
        scroll_rect.h = ScrollbarWidth;
        button_rect.h = button_width;
        button_rect.x = button_offset+x;
        button_rect.y = y;
        button_rect.w = button_len;
    }
    
    if (event == EVENT_SCROLLBAR_DRAG) {
        button_draw_color = &button_hightlight_color;
    }

    SDL_SetRenderDrawColor(gRender, scroll_draw_color->r, scroll_draw_color->g, scroll_draw_color->b, scroll_draw_color->a);
    SDL_RenderFillRect(gRender, &scroll_rect);
 
    SDL_SetRenderDrawColor(gRender, button_draw_color->r, button_draw_color->g, button_draw_color->b, button_draw_color->a);
    SDL_RenderFillRect(gRender, &button_rect);
    SDL_SetRenderDrawColor(gRender, button_color.r, button_color.g, button_color.b, button_color.a);
    SDL_RenderDrawRect(gRender, &button_rect);

    SDL_SetRenderDrawColor(gRender, board_color.r, board_color.g, board_color.b, board_color.a);
    SDL_RenderDrawRect(gRender, &scroll_rect);
}

void imgui::DefaultCheckboxDrawCb(IDType id, EventType event, int x, int y, int boarder_len, bool is_checked, void* param) {
    const SDL_Color boarder_color = {0, 0, 0, 255},
                    content_color = {225, 225, 225, 255},
                    button_color = {100, 100, 100, 255};
    const int padding = boarder_len*0.1;

    SDL_Rect rect = {x, y, boarder_len, boarder_len};
    SDL_SetRenderDrawColor(gRender, content_color.r, content_color.g, content_color.b, content_color.a);
    SDL_RenderFillRect(gRender, &rect);
    if (is_checked) {
        SDL_Rect button_rect = {x+padding, y+padding, boarder_len-padding*2, boarder_len-padding*2};
        SDL_SetRenderDrawColor(gRender, button_color.r, button_color.g, button_color.b, button_color.a);
        SDL_RenderFillRect(gRender, &button_rect);
    }
    SDL_SetRenderDrawColor(gRender, boarder_color.r, boarder_color.g, boarder_color.b, boarder_color.a);
    SDL_RenderDrawRect(gRender, &rect);
}

void imgui::DefaultLabelDrawCb(IDType id, EventType evt, int x, int y, const icolor& color, Font* font, const string& text, void* param) {
    if (!font) {
        return;
    }
    isize size = font->GetSizeByText(text);
    font->Draw(gRender, x+size.w/2, y+size.h/2, color, {1, 1}, text.c_str());
}

void imgui::DefaultInputboxDrawCb(IDType id, EventType event, int x, int y, int w, int h, Font* font, const string& text, void* param) {
    if (!font)
        return;
    const SDL_Color bg_color = {200, 200, 200, 255};
    const SDL_Color boarder_color = {0, 0, 0, 255};
    const icolor font_color = {0, 0, 0, 255};
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(gRender, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
    SDL_RenderFillRect(gRender, &rect);
    isize font_size = font->GetSizeByText(text);
    font->Draw(gRender, x+font_size.w/2+2, y+h/2, font_color, {1, 1}, text.c_str());
    SDL_SetRenderDrawColor(gRender, boarder_color.r, boarder_color.g, boarder_color.b, boarder_color.a);
    SDL_RenderDrawRect(gRender, &rect);
    if (uistate.active_item == id) {
        SDL_SetRenderDrawColor(gRender, 0, 0, 0, 255);
        SDL_RenderDrawLine(gRender, x+5+font_size.w, y+5, x+5+font_size.w, y+h-5);
    }
}
