#include <iostream>
#include <string>
#include <map>

#include <SDL.h>
#include <SDL_image.h>
#include <filesystem>
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::to_string;
namespace fs = std::filesystem;

void AppInit();
void AppQuit();
void ShowHelp();

class CommandParser {
 public:
    CommandParser(int argc, char** argv) {
        parse(argc, argv);
    }

    string Get(string name) {
        auto it = _parameters.find(name);
        if (it == _parameters.end())             
            return string();
        return it->second;
    }

 private:
    map<string, string> _parameters;

    void parse(int argc, char** argv) {
        if (argc == 1) {
            ShowHelp();
            exit(1);
        }
        _parameters["filename"] = argv[1];
        int idx = 2;
        while (idx < argc) {
            string name = argv[idx++];
            if (idx >= argc) {
                cout << "error:" << name << "don't have any parameters" << endl;
                exit(1);
            }
            _parameters[name] = argv[idx++];
        }
    }

};

void ProcessImage(string filename, string output, int row, int col, int padding);

int main(int argc, char** argv) {
    AppInit();
    CommandParser parser(argc, argv);
    string filename = parser.Get("filename"),
           output_dir = parser.Get("-o");
    int row = 0, col = 0, padding = 0;
#define STRING2INT(s, var) if (!s.empty()) { var = atoi(s.c_str()); }
    STRING2INT(parser.Get("--row"), row)
    STRING2INT(parser.Get("--col"), col)
    STRING2INT(parser.Get("--padding"), padding)
#undef STRING2INT

    if (parser.Get("filename").empty() ||
        parser.Get("-o").empty()       ||
        parser.Get("--row").empty()    ||
        parser.Get("--col").empty()) {
        ShowHelp();
        return 1;
    }
    printf("input: %s, row=%d, col=%d, padding=%d, output_dir=%s\n", filename.c_str(), row, col, padding, output_dir.c_str());
    ProcessImage(filename, output_dir, row, col, padding);
    AppQuit();
    return 0;
}

void AppInit() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF);
}

void AppQuit() {
    IMG_Quit();
    SDL_Quit();
}

void ShowHelp() {
    cout << "usage: spritesheet_unpacker filename [options]" << endl
        << "-o output\t\t\t output path, must be a directory" << endl
        << "--row row\t\t\t row of sheet" << endl
        << "--col col\t\t\t col of sheet" << endl
        << "--padding pixel\t\t\t pixels of padding." << endl;
}

void ProcessImage(string filename, string output, int row, int col, int padding) {
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (!surface) {
        cout << filename << " not exists" << endl;
        return;
    }
    if (row <= 0 || col <= 0) {
        cout << "row or col must > 0" << endl;
        return;
    }
    fs::path output_dir = output;
    if (!fs::exists(output_dir)) {
        if (!fs::create_directory(output_dir)) {
            cout << "error: create output dir " << output << " failed" << endl;
            exit(1);
        }
    }

    int w = surface->w/col,
        h = surface->h/row;
    SDL_Rect rect = {0, 0, w-2*padding, h-2*padding};
    SDL_Surface* save_surface = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    if (!save_surface) {
        cout << "error: surface create failed" << endl;
        exit(2);
    }
    SDL_SetSurfaceBlendMode(save_surface, SDL_BLENDMODE_BLEND);

    fs::path file_path = filename;
    filename = file_path.filename();
    filename = filename.substr(0, filename.rfind('.'));
    string extension = file_path.extension();

    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            rect.x = w*i + padding;
            rect.y = h*j + padding;
            SDL_BlitSurface(surface, &rect, save_surface, nullptr);
            fs::path png_filename = filename+to_string(i+1)+"x"+to_string(j+1)+extension;
            fs::path file_path = output_dir/png_filename;
            IMG_SavePNG(save_surface, file_path.string().c_str());
        }
    }
    SDL_FreeSurface(save_surface);
    SDL_FreeSurface(surface);
}
