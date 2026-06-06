#pragma once

#include <map>
#include <string>
#include <raylib.h>

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();
    Texture2D& GetTexture(const std::string& path);

private:
    std::map<std::string, Texture2D> textures;
};