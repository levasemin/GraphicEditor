#pragma once

#include "Texture.h"
#include <iostream>
#include <string>
#include <sstream>
#include <map>

class TextureManager
{
private:
    TextureManager(){}
    TextureManager(const TextureManager &source) = default;
    TextureManager &operator=(const TextureManager &source) = default;
    
public:

    struct texture
    {
        std::string path;
        Texture texture;
    };

    enum Icon
    {
        RightArrow,
        LeftArrow,
        UpArrow,
        DownArrow,
        Swap
    };

    std::vector<texture> textures_ = 
    {
        {"RightArrow.png", Texture(Color::White)}, 
        {"LeftArrow.png", Texture(Color::White)},
        {"UpArrow.png", Texture(Color::White)},
        {"DownArrow.png", Texture(Color::White)},
        {"Swap.png", Texture(Color::White)}
    };

    
    void load_textures(std::string path)
    {
        std::stringstream skin;
        std::stringstream skinNameStream;
        skinNameStream << path.c_str() << "/";
        
        for (size_t i = 0; i < textures_.size(); i++) 
        {
            textures_[i].texture.loadFromFile((skinNameStream.str() + textures_[i].path).c_str());
        }
    }
    
    static TextureManager& getInstance()
    {
        static TextureManager instance;
        return instance;
    }

    Texture &operator[](int icon)
    {
        return textures_[icon].texture;
    }
};