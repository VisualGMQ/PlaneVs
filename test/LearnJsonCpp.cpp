#include <json/json.h>

#include <fstream>
#include <string>
#include <streambuf>
#include <iostream>
using std::ifstream;
using std::ofstream;
using std::string;
using std::istreambuf_iterator;
using std::cout;
using std::endl;

const char* const filename = "test_json.json";

void GenerateJson() {
    Json::Value root;
    root["name"] = "VisualGMQ";
    root["age"] = 18;
    root["male"] = true;
    Json::Value arr;
    arr.append("PlaneVS");
    arr.append("CrazyBlock");
    arr.append("TinyJson");
    root["projects"] = arr;

    ofstream file(filename);
    file << root.toStyledString();
    file.close();
}

void ReadJson() {
    ifstream file(filename);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    Json::Value root(content);
    assert(root["name"] == "VisualGMQ");
    assert(root["age"] == 18);
    assert(root["male"] == true);
    assert(root["projects"][0] == "PlaneVS");
}

int main(int argc, char** argv) {
    return 0;
}

