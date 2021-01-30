#include "base/texture.hpp"

vector<Texture*> Texture::_instances;

Texture* Texture::Create(const string filename) {
    Texture* t = new Texture(filename);
    _instances.push_back(t);
    return t;
}

Texture::Texture(string filename) {
    createTexture();
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

isize Texture::GetSize() const {
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

void Texture::Draw(irect* src_rect, irect* dst_rect, icolor* tex_color, icolor* key_color) const {
    Draw(src_rect, dst_rect, 0, FLIP_NONE, tex_color, key_color);
}

void Texture::Draw(irect* src_rect, irect* dst_rect, float degree, FlipEnum flip, icolor* tex_color, icolor* key_color) const {
    irect src_rect_;
    irect dst_rect_;
    if (!src_rect) {
        src_rect_.x = 0;
        src_rect_.y = 0;
        src_rect_.w = GetSize().w;
        src_rect_.h = GetSize().h;
    } else {
        src_rect_ = *src_rect;
    }
    if (!dst_rect) {
        dst_rect_.x = 0;
        dst_rect_.y = 0;
        dst_rect_.w = CanvaSize.w;
        dst_rect_.h = CanvaSize.h;
    } else {
        dst_rect_ = *dst_rect;
    }
    color tex_color_, key_color_;
    if (!tex_color) {
        tex_color_.r = 1;
        tex_color_.g = 1;
        tex_color_.b = 1;
        tex_color_.a = 1;
    } else {
        tex_color_.r = tex_color->r/255.0;
        tex_color_.g = tex_color->g/255.0;
        tex_color_.b = tex_color->b/255.0;
        tex_color_.a = tex_color->a/255.0;
    }
    if (!key_color) {
        key_color_.r = -1;
        key_color_.g = -1;
        key_color_.b = -1;
    } else {
        key_color_.r = key_color->r/255.0;
        key_color_.g = key_color->g/255.0;
        key_color_.b = key_color->b/255.0;
    }
    mat4 model = calcPositionInfo(dst_rect_.x, dst_rect_.y),
         trans = calcRotateScaleInfo(src_rect_, {dst_rect_.w, dst_rect_.h}, degree, flip);
    auto program = GLProgramManager::GetById(TEXTURE_PROGRAM_ID);
    program->UniformInt1("tex", 0);
    program->UniformMat4("view", model);
    program->UniformMat4("rotscale", trans);
    program->UniformFloat4("color", tex_color_.r, tex_color_.g, tex_color_.b, tex_color_.a);
    program->UniformFloat3("keycolor", key_color_.r, key_color_.g, key_color_.b);

    glBindTexture(GL_TEXTURE_2D, _texture);

    program->Use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
}

mat4 Texture::calcPositionInfo(float x, float y) const {
    mat4 model = mat4(1.0f);
    model = glm::translate(model, vec3(x, y, 0));
    return model;
}

mat4 Texture::calcRotateScaleInfo(irect clip_area, isize dst_size, float angle_degree, FlipEnum flip) const {
    if (!IsRectValid(clip_area)) { // invalid means full texture
        clip_area.x = 0;
        clip_area.y = 0;
        clip_area.w = _size.w;
        clip_area.h = _size.h;
    } 
    float w = _size.w,
          h = _size.h;
    float x1 = clip_area.x/w,
          y1 = clip_area.y/h,
          x2 = (clip_area.x+clip_area.w)/w,
          y2 = (clip_area.y+clip_area.h)/h;
    GLfloat dataes[] = {
    //  image_x image_y tex_x tex_y
        -0.5,   -0.5,   x1,   y1,
         0.5,   -0.5,   x2,   y1,
        -0.5,    0.5,   x1,   y2,
         0.5,    0.5,   x2,   y2
    };
    auto gfx_buf = GLGfxBufManager::GetById(SYSTEM_GFXBUF_ID);
    glBindBuffer(GL_ARRAY_BUFFER, gfx_buf->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(dataes), dataes, GL_STATIC_DRAW);
    glBindVertexArray(gfx_buf->vao);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), static_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gfx_buf->ebo);
    GLuint indices[] = {
        0, 1, 2,
        1, 2, 3
    };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    mat4 trans = mat4(1.0f);
    short sign_x = 1, sign_y = 1;
    if (flip == FLIP_VERTICAL) {
        sign_y = -1;
    } else if (flip == FLIP_HORIZENTAL) {
        sign_x = -1;
    } else if (flip == FLIP_BOTH){
        sign_x = -1;
        sign_y = -1;
    }
    trans = glm::rotate(trans, glm::radians(angle_degree), vec3(0, 0, 1));
    trans = glm::scale(trans, vec3(sign_x*dst_size.w, sign_y*dst_size.h, 0));
    return trans;
}

Texture::~Texture() {
    glDeleteTextures(1, &_texture);
}
