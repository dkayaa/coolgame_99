#include "peripherals.h"
#include <SDL3_image/SDL_image.h>
#include "app.h"
#include "PEngine/BodyTwo.h"
#include "PEngine/VectorTwo.h"
#include "WorldObjects/GameEntity.h"
#include "peripherals.h"
#include <iostream>
#include <cmath>
#include "PEngine/Collisions.h"
#include "defines.h"

App *App::app{nullptr};
std::mutex App::mutex;

Uint64 Time::threshold = DT_THRESHOLD_DEFAULT;

App *App::getInstance(void)
{
    std::lock_guard<std::mutex> lock(mutex);
    if (app == nullptr)
    {
        app = new App();
    }
    return app;
}

Mouse *App::getMouse_Addr(void)
{
    return &mouse;
}

void App::setWindow(SDL_Window *w)
{
    window = w;
}

void App::setRenderer(SDL_Renderer *r)
{
    renderer = r;
}

SDL_Window *App::getWindow(void)
{
    return window;
}

SDL_Renderer *App::getRenderer(void)
{
    return renderer;
}

SDL_Window **App::getWindow_addr(void)
{
    return &window;
}

SDL_Renderer **App::getRenderer_addr(void)
{
    return &renderer;
}

void App::updateTime(void)
{
    Uint64 nanosecs_ = SDL_GetTicksNS();
    time.dt += (nanosecs_ - time.nanosecs);
    time.nanosecs = nanosecs_;
    time.dt_f = time.dt / pow(10, 9);
    // std::cout<<time.nanosecs<<" "<<time.dt<<" "<<time.dt_f<<std::endl;
}

void App::resetTime(void)
{
    time.dt = 0;
    time.dt_f = 0.0;
}

bool App::isTimePastThreshold(void)
{
    if (time.dt > time.threshold)
    {
        return true;
    }
    return false;
}

Time *App::getTime_addr(void)
{
    return &time;
}

void App::setObjectInitFunc(ObjectInitFunc f)
{
    objectInitFunc_ = f;
}

void App::init(void)
{
    objectInitFunc_(&n_obj_, &n_enemies_, &n_map_tiles_, &player_, &objects_, &enemies_, &map_, &map_width_, &map_height_);
}

PEngine::BodyTwo **App::getObjects(void)
{
    return objects_;
}

PEngine::BodyTwo **App::getMap(void)
{
    return map_;
}

PEngine::BodyTwo **App::getEnemies(void)
{
    return enemies_;
}

int App::getNObj(void)
{
    return n_obj_;
}

int App::getNMapTiles(void)
{
    return n_map_tiles_;
}
int App::getMapWidth(void)
{
    return map_width_;
}
int App::getMapHeight(void)
{
    return map_height_;
}
int App::getBlockWidth(void)
{
    return block_width_;
}
int App::getNEnemies(void)
{
    return n_enemies_;
}

PEngine::BodyTwo *App::getPlayer(void)
{
    return player_;
}

// this might be redundant
void App::updateObjects(void)
{
    auto n = getNObj();
    auto o = getObjects();
    auto dt = time.dt_f;
    for (int i = 0; i < n; i++)
    {
        auto v = (*o[i]).getV();

        (*o[i]).Move((*o[i]).getV() * dt);
        if (PEngine::VectorTwo::Length(v) > 0)
        {
            // std::cout<<(v*dt).getX()<<" "<<(v*dt).getY()<<" "<<dt<<std::endl;
            // std::cout<<v<<std::endl;
            // std::cout<<(*o[i]).getPos().getX()<<" "<<(*o[i]).getPos().getY()<<std::endl;
        }
    }
}
void App::cacheEntityForReset(WorldObjects::GameEntity *e)
{
    if (n_reset_entities >= max_reset_entities)
    {
        return;
    }
    if (reset_entities_ == nullptr)
    {
        reset_entities_ = (WorldObjects::GameEntity **)malloc(sizeof(WorldObjects::GameEntity *) * (max_reset_entities));
    }
    reset_entities_[n_reset_entities] = e;
    n_reset_entities++;
}
void App::resetEntities(void)
{
    for (int i = 0; i < n_reset_entities; i++)
    {
        reset_entities_[i]->Reset();
    }
    n_reset_entities = 0;
}