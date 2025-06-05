#ifndef DRAWER_H
#define DRAWER_H
#include <string>
#include <assert.h>
#include <iostream>
#include <SDL3_image/SDL_image.h>
#include <stdlib.h>
#include "defines.h"
#include "PEngine/VectorTwo.h"
#include "PEngine/BodyTwo.h"

using namespace PEngine;

namespace WorldObjects
{
    class GameEntity;
}

class Drawer
{
private:
    int maxObjects = 1000;
    int numObjects = 0;
    // Entity** objects;
    BodyTwo **objects;

    SDL_Renderer **r;
    static Drawer *drawer;
    static std::mutex mutex;

protected:
    Drawer();
    ~Drawer();

public:
    static Drawer *getInstance(void);
    void setMax(int m);
    void initObjectArr(void);
    void clearObjects(void);

    void blitPointOffsetScale(PEngine::BodyTwo *body, double xo, double yo, double s);
    void blitCircleOffsetScale(PEngine::BodyTwo *cir, double xo, double yo, double s);
    void blitRectOffsetScale(PEngine::BodyTwo *rect, double xo, double yo, double s);
    void blitLineOffsetScale(PEngine::VectorTwo start, PEngine::VectorTwo end, double xo, double yo, double s);

    void blitPoint(PEngine::BodyTwo *body);
    void blitCircle(PEngine::BodyTwo *cir);
    void blitRect(PEngine::BodyTwo *rect);
    void blitLine(PEngine::VectorTwo start, PEngine::VectorTwo end);
    void blitLine(float x1, float y1, float x2, float y2);
    void blitLines(SDL_FPoint *points, int count);
    void blitTexture(SDL_Texture *texture, float x, float y);
    // void addObject(Entity* e);
    void addObject(PEngine::BodyTwo *o);
    void drawObjects(void);
    void drawCachedObjectsOffsetScale(double xo = 0.0, double yo = 0.0, double scale = 1.0);
    void drawObjectsOffsetScale(WorldObjects::GameEntity *entities, int n_entities, double xo = 0.0, double yo = 0.0, double scale = 1.0);
    void setRenderer(SDL_Renderer **r_);
    void prepareScene(void);
    void presentScene(void);
    void getRGBAFromColour(PEngine::ShapeColour colour, int *r, int *g, int *b, int *a);

    // helpers
    static void DrawCircleOffsetScale(SDL_Renderer *renderer, PEngine::BodyTwo *c, double xo, double yo, double s);
    static void DrawCircle(SDL_Renderer *renderer, PEngine::BodyTwo *c);
    static void DrawCircle(SDL_Renderer *renderer, double centreX, double centreY, double radius, int n);
};

#endif