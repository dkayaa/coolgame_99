#ifndef APP_H
#define APP_H

#include "peripherals.h"
#include <mutex>
#include "defines.h"

namespace WorldObjects
{
    class GameEntity;
    class OGTile;
}

namespace PEngine
{
    class BodyTwo;
    class VectorTwo;
}

class Map;

struct Time
{
    Uint64 nanosecs;
    Uint64 dt;
    float dt_f;
    static Uint64 threshold;
};

// App Singleton Class
class App
{
private:
    typedef void (*ObjectInitFunc)(int *, int *, int *, PEngine::BodyTwo **, PEngine::BodyTwo ***, PEngine::BodyTwo ***, PEngine::BodyTwo ***, int *, int *);
    // typedef void (*ObjectSortFunc)(PEngine::BodyTwo **, int);

    static App *app;
    static std::mutex mutex;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Time time;

    // old crap..
    Mouse mouse;

    ObjectInitFunc objectInitFunc_ = nullptr;
    PEngine::BodyTwo **objects_ = nullptr;
    PEngine::BodyTwo **map_ = nullptr;
    PEngine::BodyTwo **enemies_ = nullptr;
    PEngine::BodyTwo *player_ = nullptr;
    int n_obj_ = 0;
    int n_enemies_ = 0;
    int n_map_tiles_ = 0;

    int map_width_ = 0;
    int map_height_ = 0;

    WorldObjects::GameEntity **reset_entities_ = nullptr;
    int n_reset_entities = 0;
    int max_reset_entities = 100;

    // These are hardcoded in FlexLevel and need to be changed..
    int x_offset_ = 100;
    int y_offset_ = 100;
    int block_width_ = 40;
    // occupancy grid.
    WorldObjects::OGTile *occupancy_grid_ = nullptr;
    int n_occupancy_grid_cells_ = 0;

protected:
    App()
    {
        time.nanosecs = SDL_GetTicksNS();
        time.dt_f = 0.0;
        time.dt = 0;
    };
    ~App() {};

public:
    App(App &other) = delete;
    void operator=(App &other) = delete;

    static App *getInstance(void);

    Mouse *getMouse_Addr(void);
    SDL_Window *getWindow(void);
    SDL_Renderer *getRenderer(void);
    SDL_Window **getWindow_addr(void);
    SDL_Renderer **getRenderer_addr(void);
    Time *getTime_addr(void);
    void updateTime(void);

    void setWindow(SDL_Window *w);
    void setRenderer(SDL_Renderer *r);
    void setObjectInitFunc(ObjectInitFunc f);
    void init(void);

    // discritisation
    void initOG(void);
    void populateOG(void);
    WorldObjects::OGTile *getOGrid(void);
    int getNOGrid(void);

    void cacheEntityForReset(WorldObjects::GameEntity *e);
    void resetEntities(void);
    // void sortObjects(void);
    PEngine::BodyTwo **getObjects(void);
    PEngine::BodyTwo **getMap(void);
    PEngine::BodyTwo **getEnemies(void);
    int getNObj(void);
    int getNMapTiles(void);
    int getMapWidth(void);
    int getMapHeight(void);
    int getBlockWidth(void);

    int getNEnemies(void);
    PEngine::BodyTwo *getPlayer(void);
    void updateObjects(void);

    bool isTimePastThreshold(void);
    void resetTime(void);
};

#endif
