/*
MIT License

Copyright (c) 2021 - 2025 Aryan Baburajan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <utils/stb_image.h>

#include "core/asset.h"
#include "core/log.h"
#include "renderer/texture.h"

namespace dt {
texture_t::texture_t(unsigned char *data, int _width, int _height, int _noChannels) : width(_width), height(_height), no_channels(_noChannels) {
    glGenTextures(1, &id);
    GLenum format;
    if (no_channels == 1)
        format = GL_RED;
    else if (no_channels == 3)
        format = GL_RGB;
    else if (no_channels == 4)
        format = GL_RGBA;
    else
        format = GL_RGB;

    if (width % 4 == 0)
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    else
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    LOG("loaded texture of size {}x{} with id {}", width, height, id);
}

std::shared_ptr<texture_t> texture_t::load(const std::filesystem::path &path) {
    static std::unordered_map<std::string, std::shared_ptr<texture_t>> cache;

    std::string key = path.string();
    auto it = cache.find(key);
    if (it != cache.end()) {
        return it->second;
    }

    stbi_set_flip_vertically_on_load(true);

    int width, height, no_channels;
    unsigned char *data = stbi_load(key.c_str(), &width, &height, &no_channels, 0);

    if (!data) {
        ERROR("failed to load texture: {}", key);
        return nullptr;
    }

    auto tex = std::make_shared<texture_t>(data, width, height, no_channels);
    stbi_image_free(data);

    cache[key] = tex;
    return tex;
}
} // namespace dt