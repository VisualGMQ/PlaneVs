// Read SpriteSheet from [SpriteSheetPacker](https://github.com/amakaseev/sprite-sheet-packer)

#ifndef READ_SHEET_HPP
#define READ_SHEET_HPP
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <streambuf>

#include <json/json.h>
#include <glm/glm.hpp>

#include "base/header.hpp"
#include "base/validable.hpp"
using std::ifstream;
using std::string;
using std::vector;
using std::istreambuf_iterator;
namespace fs = std::filesystem;


using Point = glm::ivec2;

class ImageInSheet final : public Validable{
 public:
     ImageInSheet(string name, Point position, Size size, Size origin_size);
     string GetName() const;
     Point GetPosition() const;
     Size GetSize() const;
     Size GetOriginSize() const;
 private:
     Point _position;
     Size _size;
     Size _origin_size;
     string _name;
};

class ImageSheet final : public Validable {
 public:
     static ImageSheet ReadFromJson(fs::path filename);
     string GetImageFilename() const;
     const vector<ImageInSheet>& GetImages() const;
 private:
     vector<ImageInSheet> _images;
     string _img_filename;

     ImageSheet(fs::path);
     vector<ImageInSheet> readSpriteSheet(string filename);
     Json::Value readJsonFile(string filename);
     vector<ImageInSheet> parseJsonFile2ImageInfo(Json::Value& root);
};

#endif

