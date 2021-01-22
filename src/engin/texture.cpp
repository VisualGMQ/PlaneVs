#include "engin/texture.hpp"
#include <iostream>

Texture::Texture() {
    createTexture();
}

Texture::Texture(string filename): Texture() {
    Load(filename);
}

void Texture::Load(const string filename) {
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (!surface) {
        Log("can't load image %s", filename.c_str());
        invalid();
    } else {
        _size.w = surface->w;
        _size.h = surface->h;
        valid();
        bufferTextureData(surface);
    }
    SDL_FreeSurface(surface);
}

Size Texture::GetSize() const {
    return _size;
}

void Texture::createTexture() {
    glGenTextures(1, &_texture);
    Assertm("texture create failed", _texture != 0);
}

void Texture::bufferTextureData(SDL_Surface* surface) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _size.w, _size.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Draw(GLProgram& program, ShapeInfo shape_info, ColorInfo color_info) {
    mat4 model = calcPositionInfo(shape_info.position.x, shape_info.position.y),
         trans = calcRotateScaleInfo(shape_info.scale.x, shape_info.scale.y, shape_info.degree);
    program.UniformInt1("tex", 0);
    program.UniformMat4("view", model);
    program.UniformMat4("rotscale", trans);
    program.UniformFloat4("color", color_info.color.r, color_info.color.g, color_info.color.b, color_info.color.a);
    program.UniformFloat3("keycolor", color_info.key_color.r, color_info.key_color.g, color_info.key_color.b);

    glBindTexture(GL_TEXTURE_2D, _texture);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
}

mat4 Texture::calcPositionInfo(float x, float y) {
    mat4 model = mat4(1.0f);
    model = glm::translate(model, vec3(x, y, 0));
    return model;
}

mat4 Texture::calcRotateScaleInfo(float scalex, float scaley, float angle_degree) {
    mat4 trans = mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(angle_degree), vec3(0, 0, 1));
    trans = glm::scale(trans, vec3(_size.w*scalex, _size.h*scaley, 0));
    return trans;
}
