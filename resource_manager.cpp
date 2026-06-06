#include <map>
#include <string>
#include <raylib.h>
#include "resource_manager.hpp"


ResourceManager::ResourceManager() {
    textures = std::map<std::string, Texture2D>(); // Texture cache
}

ResourceManager::~ResourceManager() {
    for (auto& [path, texture] : textures) {
        UnloadTexture(texture);  // unload everything at the end
    }
}

Texture2D& ResourceManager::GetTexture(const std::string& path) {
    if (textures.find(path) == textures.end()) {
        textures[path] = LoadTexture(path.c_str());  // load only if not cached
    }
    return textures[path];  // return existing one
} 