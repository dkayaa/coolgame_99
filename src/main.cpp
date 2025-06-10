/*
 * This example code creates an SDL window and renderer, and then clears the
 * window to a different color every frame, so you'll effectively get a window
 * that's smoothly fading between colors.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */

#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
// #include "defines.h"
#include "classes.h"
#include "drawer.h"
#include "textureManager.h"
#include "peripherals.h"
#include "app.h"
#include "PEngine/VectorTwo.h"
#include "PEngine/BodyTwo.h"
#include "PEngine/Collisions.h"
#include "helpers.h"
#include "WorldObjects/GameEntity.h"

/* We will use this renderer to draw into this window every frame. */

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    // auto cm = CollisionManager::getInstance();

    SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/clear", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    auto app = App::getInstance();
    auto drawer = Drawer::getInstance();

    (*app).setWindow(window);
    (*app).setRenderer(renderer);
    (*app).setObjectInitFunc(LevelInstances::FlexLevel);
    //(*app).setObjectSortFunc(ObjectSorters::BasicSort);
    auto tm = TextureManager::getInstance();
    tm->addTexture(PEngine::ClassType::FLOOR, "/Users/deniz_kaya/Projects/Git-Local/coolgame_99/assets/img/Floor/Floor.png");
    tm->addTexture(PEngine::ClassType::WALL, "/Users/deniz_kaya/Projects/Git-Local/coolgame_99/assets/img/Wall/Wall.png");

    (*drawer).setMax(1000);
    (*drawer).initObjectArr();
    (*drawer).setRenderer((*app).getRenderer_addr());

    (*app).init();

    return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    auto kb = Keyboard::getInstance();
    auto app = App::getInstance();
    switch (event->type)
    {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
        break;
    case SDL_EVENT_KEY_UP:
        (*kb).doKeyUp(&(event->key));
        break;
    case SDL_EVENT_KEY_DOWN:
        (*kb).doKeyDown(&(event->key));
        break;
    }

    return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    auto app = App::getInstance();
    auto drawer = Drawer::getInstance();
    auto kb = Keyboard::getInstance();

    (*app).resetEntities();
    (*app).updateTime();
    if (!(*app).isTimePastThreshold())
    {
        return SDL_APP_CONTINUE;
    }

    (*drawer).clearObjects();
    (*drawer).prepareScene();

    double dx = 0.0;
    double dy = 0.0;
    if ((*kb).isPressed(Keyboard::Key::UP))
    {
        dy = -1.0;
    }
    if ((*kb).isPressed(Keyboard::Key::DOWN))
    {
        dy = 1.0;
    }
    if ((*kb).isPressed(Keyboard::Key::RIGHT))
    {
        dx = 1.0;
    }
    if ((*kb).isPressed(Keyboard::Key::LEFT))
    {
        dx = -1.0;
    }

    auto p = (*app).getPlayer();

    if (dx != 0 || dy != 0)
    {
        (*p).setV(VectorTwo::Normalise(VectorTwo(dx, dy)) * 120.0);
    }
    else
    {
        (*p).setV(VectorTwo(dx, dy));
    }

    auto dt = (*app).getTime_addr()->dt_f;
    (*p).Move((*p).getV() * dt);

    //(*app).sortObjects();
    auto o = (*app).getObjects();

    for (int i = 0; i < (*app).getNObj(); i++)
    {
        if (o[i]->getClassType() == PEngine::ClassType::ENEMY || o[i]->getClassType() == PEngine::ClassType::PLAYER)
        {
            auto m = (*app).getMap();
            WorldObjects::GameEntity *e1;
            WorldObjects::GameEntity *nt;
            e1 = (WorldObjects::GameEntity *)o[i];
            MapHelpers::ComputeNearestTile(e1, ((WorldObjects::GameEntity **)m), (*app).getBlockWidth(), (*app).getMapHeight(), (*app).getMapWidth(), &nt);
            (*app).cacheEntityForReset(e1);
            (*app).cacheEntityForReset(nt);
        }
        (*drawer).addObject(o[i]);

        //  we should set j = i + 1 for efficiency, but it screws the circle/rect collisions.
        //  need to figure out why.
        for (int j = 0; j < (*app).getNObj(); j++)
        {
            if (i == j)
            {
                continue;
            }

            double mag = 0;
            VectorTwo n;
            if (Collisions::intersectBodies(o[i], o[j], &n, &mag))
            {
                if (o[i]->canMove() && o[j]->canMove())
                {
                    (*o[i]).Move(-n * mag / 2);
                    (*o[j]).Move(n * mag / 2);
                }
                else if (o[i]->canMove())
                {
                    (*o[i]).Move(-n * mag);
                }
                else if (o[j]->canMove())
                {
                    (*o[j]).Move(n * mag);
                }
            }
        }
    }

    MapHelpers::BoundedBreadthFirstSearch((WorldObjects::GameEntity *)p, 5);

    for (int i = 0; i < (*app).getNObj(); i++)
    {
        o[i]->Step(dt);
    }

    (*drawer).drawCachedObjectsOffsetScale(600.0, 50.0, 1.0);
    //(*drawer).drawObjectsOffsetScale((WorldObjects::GameEntity *)(*app).getOGrid(), (*app).getNOGrid(), 750, 380, 0.5);
    (*drawer).presentScene();

    (*app).resetTime();

    return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    auto app = App::getInstance();
    /* SDL will clean up the window/renderer for us. */
}