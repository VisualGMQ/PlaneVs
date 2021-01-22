#include "engin/gl_gfxbuf.hpp"

GLGfxBufManager::GLGfxBuf* GLGfxBufManager::Create() {
    GLGfxBuf* buf = new GLGfxBuf;
    _gfxbufs.push_back(buf);
    return buf;
}

void GLGfxBufManager::FreeById(IdType id) {
    for (auto it = _gfxbufs.begin(); it != _gfxbufs.end(); it++) {
        if ((*it)->GetId() == id) {
            delete *it;
            _gfxbufs.erase(it);
            return;
        }
    }
}

GLGfxBufManager::GLGfxBuf* GLGfxBufManager::GetById(IdType id) {
    for (GLGfxBuf* buf : _gfxbufs) {
        if (buf->GetId() == id)
            return buf;
    }
    Log("you required a non-exist id %u", id);
    return nullptr;
}

void GLGfxBufManager::Destroy() {
    for (GLGfxBuf* buf : _gfxbufs)
        delete buf;
}

vector<GLGfxBufManager::GLGfxBuf*> GLGfxBufManager::_gfxbufs;
