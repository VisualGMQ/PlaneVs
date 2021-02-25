#include "base/image_sheet.hpp"

ImageInSheet::ImageInSheet(string name, Point position, isize size, isize origin_size) {
    if (name.empty() ||
            (position.x < 0 || position.y < 0) ||
            (size.w <= 0 || size.h <= 0) ||
            (origin_size.w <= 0 || origin_size.h <= 0)) {
        invalid();
    } else {
        _name = name;
        _position = position;
        _size = size;
        _origin_size = origin_size;
        valid();
    }
}

string ImageInSheet::GetName() const {
    return _name;
}

Point ImageInSheet::GetPosition() const {
    return _position;
}

isize ImageInSheet::GetSize() const {
    return _size;
}

isize ImageInSheet::GetOriginSize() const {
    return _origin_size;
}


ImageSheet ImageSheet::ReadFromJson(fs::path filename) {
    return ImageSheet(filename);
}

ImageSheet::ImageSheet(fs::path json_filename) {
    if (!fs::exists(json_filename)) {
        Logw("ImageSheeet::ImageSheetl", "%s not exists", json_filename.string().c_str());
        invalid();
    } else {
        _img_filename = json_filename.string();
        _img_filename.replace(_img_filename.rfind(".")+1, 4, "png");
        _images = readSpriteSheet(json_filename.string());
        valid();
    }
}

string ImageSheet::GetImageFilename() const {
    return _img_filename;
}

const vector<ImageInSheet>& ImageSheet::GetImages() const {
    return _images;
}

vector<ImageInSheet> ImageSheet::readSpriteSheet(string filename) {
    Json::Value root = readJsonFile(filename);
    return parseJsonFile2ImageInfo(root);
}

vector<ImageInSheet> ImageSheet::parseJsonFile2ImageInfo(Json::Value& root) {
    vector<ImageInSheet> ret;
    Json::Value::Members members = root.getMemberNames();
    isize size, origin_size;
    Point position;
    for (auto name : members) {
        Json::Value frame = root[name]["frame"];
        position.x = frame["x"].asInt();
        position.y = frame["y"].asInt();
        size.w = frame["width"].asInt();
        size.h = frame["height"].asInt();
        Json::Value source_size = root[name]["sourceSize"];
        origin_size.w = source_size["width"].asInt();
        origin_size.h = source_size["height"].asInt();

        int idx = name.rfind("/");
        if (idx != name.npos) {
            name = name.substr(idx+1, name.npos);
        }
        ret.push_back(ImageInSheet(name, position, size, origin_size));
    }
    return ret;
}

Json::Value ImageSheet::readJsonFile(string filename) {
    ifstream file(filename);
    Json::Value root;
    if (file.fail()) {
        Logw("ImageSheet::readJsonFile", "%s not exists", filename.c_str());
        return root;
    }
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    Json::CharReaderBuilder builder;
    std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    Json::String error;
    if (!reader->parse(content.c_str(), content.c_str()+content.length(), &root, &error)) {
        Logw("ImageSheet::readJsonFile", "parse json file failed");
        Logw("ImageSheet::readJsonFile", "%s", error.c_str());
    }
    return root;
}
