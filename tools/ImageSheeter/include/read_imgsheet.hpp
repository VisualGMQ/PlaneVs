#ifndef READ_IMGSHEET_HPP
#define READ_IMGSHEET_HPP
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <sstream>
using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::getline;
using std::stringstream;
namespace fs = std::filesystem;

struct ImageInfoInSheeter {
    string name;    // image name 
    // position of image
    int x;
    int y;
    // size of image
    int w;
    int h;
};

struct SheeterInfo {
    vector<ImageInfoInSheeter> img_infoes;
    string img_filename;
};

static SheeterInfo ReadImageSheeter(string info_filename) {
    fs::path info_path = info_filename;
    fs::path parent_path = info_path.parent_path();
    ifstream file(info_filename);
    stringstream ss;
    SheeterInfo ret;
    if (file.fail()) {
        cout << "[Error]: " + info_filename + " can't open" << endl;
        return ret;
    }
    ImageInfoInSheeter img_info;
    getline(file, ret.img_filename);
    ret.img_filename = (parent_path/fs::path(ret.img_filename)).string();
    while (!file.eof()) {
        ImageInfoInSheeter info;
        file >> info.name >> info.x >> info.y >> info.w >> info.h;
        if (!info.name.empty())
            ret.img_infoes.push_back(info);
    }
    file.close();
    return ret;
}

#endif
