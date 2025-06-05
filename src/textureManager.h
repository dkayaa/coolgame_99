#ifndef TEXTUREMANAGER_H 
#define TEXTUREMANAGER_H 

#include <mutex>
#include <map>
#include <string>
#include <SDL3_image/SDL_image.h>

//singleton class to load and store textures. 
class TextureManager{ 
private: 
    static TextureManager* texture_manager_;
    static std::mutex mutex_;
    std::map<std::string, SDL_Texture*> textures_;
protected: 
    TextureManager(){};
    ~TextureManager(){};
public: 
    TextureManager(TextureManager& other) = delete; //delete copy ctor 
    void operator=(TextureManager& other) = delete; //delete assignment operator

    static TextureManager* getInstance(void);
    bool addTexture(std::string filename_, std::string key_, SDL_Renderer *renderer_);
    bool addTexture(std::string filename_, std::string key_);

    SDL_Texture* getTexture(std::string key_);
};

#endif 