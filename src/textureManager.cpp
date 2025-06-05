#include <mutex>
#include <map>
#include <string>
#include <iostream> 
#include <SDL3_image/SDL_image.h>
#include "textureManager.h"
#include "app.h"

TextureManager* TextureManager::texture_manager_{nullptr};
std::mutex TextureManager::mutex_;

TextureManager* TextureManager::getInstance(void) { 
        std::lock_guard<std::mutex> lock(mutex_);
        if (texture_manager_ == nullptr)
        {
            texture_manager_ = new TextureManager();
        }
        return texture_manager_;
}

bool TextureManager::addTexture(std::string key_, std::string filename_, SDL_Renderer *renderer_){ \
    if(textures_.contains(key_)){ 
        std::cout<<"addTexture: key alr exists "<<key_<<std::endl;
        return false; 
    }

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename_.c_str());
    auto texture = IMG_LoadTexture(renderer_, filename_.c_str());
    const auto [it_text_, success] = textures_.insert({key_, texture});
    return success;
}

bool TextureManager::addTexture(std::string key_, std::string filename_){ \
    auto app = App::getInstance();
    return addTexture(key_, filename_, app->getRenderer());
}

SDL_Texture* TextureManager::getTexture(std::string key_){ 
    if(!textures_.contains(key_)){ 
        std::cout<<"getTexture: key dne "<<key_<<std::endl;
        return nullptr; 
    }
    return textures_[key_];
}