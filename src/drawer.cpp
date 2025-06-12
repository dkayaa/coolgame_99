#include "drawer.h"
#include <string>
#include <assert.h>
#include <iostream>
#include <SDL3_image/SDL_image.h>
#include <stdlib.h>
#include "defines.h"
#include <mutex>
#include <cmath>
#include <math.h>
#include "PEngine/VectorTwo.h"
#include "PEngine/BodyTwo.h"
#include "WorldObjects/Floor.h"
#include "WorldObjects/GameEntity.h"
#include "textureManager.h"
#include <iostream>

using namespace PEngine;
typedef void (*VertexTransformFunc)(float, float, float *, float *);

Drawer *Drawer::drawer{nullptr};
std::mutex Drawer::mutex;
VertexTransformFunc Drawer::default_transform_ = VertexTransformers::IsoTransform;

namespace
{
    static int drawComparator(const void *a, const void *b)
    {
        PEngine::BodyTwo **o1;
        PEngine::BodyTwo **o2;

        o1 = (PEngine::BodyTwo **)a;
        o2 = (PEngine::BodyTwo **)b;
        double d1 = sqrt(pow((*o1)->getPos().getX(), 2) + pow((*o1)->getPos().getY(), 2));
        double d2 = sqrt(pow((*o2)->getPos().getX(), 2) + pow((*o2)->getPos().getY(), 2));

        if ((*o1)->getClassType() == PEngine::WALL || (*o1)->getClassType() == PEngine::FLOOR || (*o1)->getClassType() == PEngine::GOAL)
        {
            d1 = sqrt(pow((*o1)->getPos().getX() - (*o1)->getL() * 0.5, 2) + pow((*o1)->getPos().getY() - (*o1)->getW() * 0.5, 2));
        }
        if ((*o2)->getClassType() == PEngine::WALL || (*o2)->getClassType() == PEngine::FLOOR || (*o2)->getClassType() == PEngine::GOAL)
        {
            d2 = sqrt(pow((*o2)->getPos().getX() - (*o2)->getL() * 0.5, 2) + pow((*o2)->getPos().getY() - (*o2)->getW() * 0.5, 2));
        }

        return (d1 - d2);
    }
}

Drawer::Drawer() {};

Drawer::~Drawer()
{
    free(objects);
}

Drawer *Drawer::getInstance(void)
{
    std::lock_guard<std::mutex> lock(mutex);
    if (drawer == nullptr)
    {
        drawer = new Drawer();
    }
    return drawer;
}

void Drawer::setMax(int m)
{
    maxObjects = m;
}

void Drawer::initObjectArr(void)
{
    if (objects != NULL)
    {
        return;
    }
    // objects = (Entity**)malloc(sizeof(Entity*)*maxObjects);
    objects = (BodyTwo **)malloc(sizeof(BodyTwo *) * maxObjects);
    assert(objects != NULL);
}
void Drawer::clearObjects(void)
{
    // memset(objects, 0, sizeof(Entity*) * numObjects);
    memset(objects, 0, sizeof(BodyTwo *) * numObjects);

    numObjects = 0;
}

void Drawer::getRGBAFromColour(PEngine::ShapeColour colour, int *r, int *g, int *b, int *a)
{
    (*a) = 255;
    switch (colour)
    {
    case PEngine::ShapeColour::WHITE:
        (*r) = 255;
        (*g) = 255;
        (*b) = 255;
        break;
    case PEngine::ShapeColour::RED:
        (*r) = 255;
        (*g) = 0;
        (*b) = 0;
        break;
    case PEngine::ShapeColour::BLUE:
        (*r) = 0;
        (*g) = 0;
        (*b) = 255;
        break;
    case PEngine::ShapeColour::GREEN:
        (*r) = 0;
        (*g) = 255;
        (*b) = 0;
        break;
    case PEngine::ShapeColour::BLACK:
        (*r) = 0;
        (*g) = 0;
        (*b) = 0;
        break;
    }
}

void Drawer::blitPointOffsetScale(PEngine::BodyTwo *body, double xo, double yo, double s, VertexTransformFunc f)
{
    int red, green, blue, alpha;
    getRGBAFromColour(body->getColour(), &red, &green, &blue, &alpha);
    SDL_SetRenderDrawColor(*r, red, green, blue, alpha);

    SDL_FPoint p;

    f(body->getPos().getX(), body->getPos().getY(), &p.x, &p.y);
    p.x = (p.x) * s + xo;
    p.y = (p.y) * s + yo;
    SDL_RenderPoint(*r, p.x, p.y);
}

void Drawer::blitRectOffsetScale(PEngine::BodyTwo *rect, double xo, double yo, double s, VertexTransformFunc f)
{
    int red, green, blue, alpha;

    // SDL rectangle, origin is the upper left vertex.
    // SDL_FRect frect = {
    //    (float)((rect->getPos().getX() - rect->getW() * 0.5) * s + xo),
    //    (float)((rect->getPos().getY() - rect->getL() * 0.5) * s + yo),
    //    (float)(rect->getL() * s),
    //    (float)(rect->getW() * s)};

    // getRGBAFromColour(rect->getFillColour(), &red, &green, &blue, &alpha);
    // SDL_SetRenderDrawColor(*r, red, green, blue, alpha);
    // SDL_RenderFillRect(*r, &frect);

    getRGBAFromColour(rect->getColour(), &red, &green, &blue, &alpha);
    SDL_SetRenderDrawColor(*r, red, green, blue, alpha);
    // SDL_RenderRect(*r, &frect);

    int n = rect->getNVert();
    VectorTwo *verts = rect->getCachedVerts();

    SDL_FPoint points[n + 1];

    for (int i = 0; i < n; i++)
    {
        f(verts[i].getX(), verts[i].getY(), &points[i].x, &points[i].y);
        points[i].x = (points[i].x) * s + xo;
        points[i].y = (points[i].y) * s + yo;
    }

    points[n].x = points[0].x;
    points[n].y = points[0].y;

    SDL_RenderLines(*r, points, n + 1);

    SDL_FPoint p;
    f(rect->getPos().getX(), rect->getPos().getY(), &p.x, &p.y);
    p.x = (p.x) * s + xo;
    p.y = (p.y) * s + yo;
    SDL_RenderPoint(*r, p.x, p.y);
}

void Drawer::blitCircleOffsetScale(PEngine::BodyTwo *cir, double xo, double yo, double s, VertexTransformFunc f)
{
    int red, green, blue, alpha;
    getRGBAFromColour(cir->getColour(), &red, &green, &blue, &alpha);
    SDL_SetRenderDrawColor(*r, red, green, blue, alpha);

    DrawCircleOffsetScale(*r, cir, xo, yo, s);

    SDL_FPoint p;
    f(cir->getPos().getX(), cir->getPos().getY(), &p.x, &p.y);
    p.x = (p.x) * s + xo;
    p.y = (p.y) * s + yo;
    SDL_RenderPoint(*r, p.x, p.y);
}

void Drawer::blitLineOffsetScale(PEngine::VectorTwo start, PEngine::VectorTwo end, double xo, double yo, double s, VertexTransformFunc f)
{
    float x1, y1, x2, y2;
    f(start.getX(), start.getY(), &x1, &y1);
    x1 = (x1)*s + xo;
    y1 = (y1)*s + yo;
    f(end.getX(), end.getY(), &x2, &y2);
    x2 = (x2)*s + xo;
    y2 = (y2)*s + yo;
    blitLine(x1, y1, x2, y2);
}

void Drawer::blitPoint(PEngine::BodyTwo *body)
{
    int red, green, blue, alpha;
    getRGBAFromColour(body->getColour(), &red, &green, &blue, &alpha);
    SDL_SetRenderDrawColor(*r, red, green, blue, alpha);

    SDL_FPoint p;
    p.x = body->getPos().getX();
    p.y = body->getPos().getY();
    SDL_RenderPoint(*r, p.x, p.y);
}

void Drawer::blitRect(PEngine::BodyTwo *rect)
{
    int red, green, blue, alpha;
    getRGBAFromColour(rect->getColour(), &red, &green, &blue, &alpha);
    SDL_SetRenderDrawColor(*r, red, green, blue, alpha);

    int n = rect->getNVert();
    VectorTwo *verts = rect->getCachedVerts();

    SDL_FPoint points[n + 1];

    for (int i = 0; i < n; i++)
    {
        points[i].x = verts[i].getX();
        points[i].y = verts[i].getY();
    }
    points[n].x = verts[0].getX();
    points[n].y = verts[0].getY();

    SDL_RenderLines(*r, points, n + 1);

    SDL_FPoint p;
    p.x = rect->getPos().getX();
    p.y = rect->getPos().getY();
    SDL_RenderPoint(*r, p.x, p.y);
}

void Drawer::blitCircle(PEngine::BodyTwo *cir)
{
    int red, green, blue, alpha;
    getRGBAFromColour(cir->getColour(), &red, &green, &blue, &alpha);
    SDL_SetRenderDrawColor(*r, red, green, blue, alpha);

    DrawCircle(*r, cir);

    SDL_FPoint p;
    p.x = cir->getPos().getX();
    p.y = cir->getPos().getY();
    SDL_RenderPoint(*r, p.x, p.y);
}

void Drawer::blitLine(PEngine::VectorTwo start, PEngine::VectorTwo end)
{
    float x1, y1, x2, y2;
    x1 = start.getX();
    y1 = start.getY();
    x2 = end.getX();
    y2 = end.getY();
    blitLine(x1, y1, x2, y2);
}

void Drawer::blitLine(float x1, float y1, float x2, float y2)
{
    SDL_SetRenderDrawColor(*r, 255, 255, 255, 255);
    SDL_RenderLine(*r, x1, y1, x2, y2);
}

void Drawer::blitLines(SDL_FPoint *points, int count)
{
    SDL_RenderLines(*r, points, count);
}

// TODO: This is a super ugly function and needs reworking
void Drawer::blitTexture(SDL_Texture *texture, PEngine::BodyTwo *e, double xo, double yo, double s, VertexTransformFunc f)
{
    float x1, y1;
    f((*e).getPos().getX(), (*e).getPos().getY(), &x1, &y1);

    float height = 20;
    if (e->getClassType() == PEngine::ClassType::WALL)
    {
        height = 60;
    }

    SDL_FRect dest;
    SDL_GetTextureSize(texture, &dest.w, &dest.h);

    float asp_r = dest.w / dest.h;
    // dest.h = dest.w / asp_r;
    if (e->getClassType() == PEngine::ClassType::WALL || e->getClassType() == PEngine::ClassType::FLOOR || e->getClassType() == PEngine::ClassType::GOAL)
    {
        float width = 80.0;
        x1 = (x1)*s + xo - width * 0.5;
        y1 = (y1)*s + yo - height;
        dest.x = x1;
        dest.y = y1;
        dest.w = width;
        dest.h = 80; // dest.w / asp_r;
    }
    else if (e->getClassType() == PEngine::ClassType::PLAYER || e->getClassType() == PEngine::ClassType::ENEMY)
    {
        x1 = (x1)*s + xo - dest.w * 0.5;
        y1 = (y1)*s + yo - dest.h;
        dest.x = x1;
        dest.y = y1;
    }
    float v = ((WorldObjects::GameEntity *)e)->GetVisibility();
    SDL_SetTextureColorMod(texture, (int)(255 * v), (int)(255 * v), (int)(255 * v));
    SDL_RenderTexture(*r, texture, NULL, &dest);
}

void Drawer::addObject(PEngine::BodyTwo *e)
{
    if (numObjects < maxObjects)
    {
        objects[numObjects++] = e;
    }
}

void Drawer::drawObjectsOffsetScale(WorldObjects::GameEntity *entities, int n_entities, double xo, double yo, double scale)
{
    WorldObjects::GameEntity *e;
    for (int i = 0; i < n_entities; i++)
    {
        e = &entities[i];
        switch (e->getClassType())
        {
        case ClassType::MISC:
            blitPointOffsetScale(e, xo, yo, scale);
            break;
        case ClassType::CIRC:
            blitCircleOffsetScale(e, xo, yo, scale);
            break;
        case ClassType::REC:
            blitRectOffsetScale(e, xo, yo, scale);
            break;
        case ClassType::BODY:
            blitPointOffsetScale(e, xo, yo, scale);
            break;
        case ClassType::PLAYER:
            blitCircleOffsetScale(e, xo, yo, scale);
            break;
        case ClassType::ENEMY:
            blitCircleOffsetScale(e, xo, yo, scale);
            break;
        case ClassType::WALL:
            blitRectOffsetScale(e, xo, yo, scale);
            break;
        case ClassType::OGTILE:
            blitRectOffsetScale(e, xo, yo, scale);
            break;
        case ClassType::GOAL:
            blitRectOffsetScale(e, xo, yo, scale);
            break;
        case ClassType::GAMEENTITY:
            blitPointOffsetScale(e, xo, yo, scale);
            break;
        case ClassType::FLOOR:
            blitPointOffsetScale(e, xo, yo, scale);
            break;
        }
    }
}

void Drawer::drawCachedObjectsOffsetScale(double xo, double yo, double scale)
{
    PEngine::BodyTwo *e;
    WorldObjects::GameEntity *ge;
    qsort(objects, numObjects, sizeof(PEngine::BodyTwo *), drawComparator);
    auto tm = TextureManager::getInstance();

    for (int i = 0; i < numObjects; i++)
    {
        e = objects[i];
        ge = (WorldObjects::GameEntity *)e;
        // if (ge->GetVisibility() == 0.0)
        //{
        //     continue;
        // }

        auto text = tm->getTexture(e->getClassType());
        if (text != nullptr && SHOW_TEXTURES)
        {
            blitTexture(text, e, xo, yo, scale);
            // continue;
        }
        if (SHOW_2D)
        {

            switch (e->getClassType())
            {
            case ClassType::MISC:
                blitPointOffsetScale(e, xo, yo, scale);
                break;
            case ClassType::CIRC:
                blitCircleOffsetScale(e, xo, yo, scale);
                break;
            case ClassType::REC:
                blitRectOffsetScale(e, xo, yo, scale);
                break;
            case ClassType::BODY:
                blitPointOffsetScale(e, xo, yo, scale);
                break;
            case ClassType::PLAYER:
                blitCircleOffsetScale(e, xo, yo, scale);
                break;
            case ClassType::ENEMY:
                blitCircleOffsetScale(e, xo, yo, scale);
                break;
            case ClassType::WALL:
                blitRectOffsetScale(e, xo, yo, scale);
                break;
            case ClassType::OGTILE:
                blitRectOffsetScale(e, xo, yo, scale);
                break;
            case ClassType::GOAL:
                blitRectOffsetScale(e, xo, yo, scale);
                break;
            case ClassType::GAMEENTITY:
                blitPointOffsetScale(e, xo, yo, scale);
                break;
            case ClassType::FLOOR:
                // floor is a rectangle but we still blit it as a point for clarity.
                blitPointOffsetScale(e, xo, yo, scale);
                break;
            }
            auto fe = (WorldObjects::GameEntity *)(e);
            auto nn = (fe)->GetNumFixedNeighbours();
            for (int i = 0; i < nn; i++)
            {
                blitLineOffsetScale(fe->getPos(), fe->GetFixedNeighbourAtIndex(i)->getPos(), xo, yo, scale);
            }

            nn = (fe)->GetNumVariableNeighbours();
            for (int i = 0; i < nn; i++)
            {
                blitLineOffsetScale(fe->getPos(), fe->GetVariableNeighbourAtIndex(i)->getPos(), xo, yo, scale);
            }
        }
    }
}

void Drawer::drawObjects(void)
{
    PEngine::BodyTwo *e;
    qsort(objects, numObjects, sizeof(PEngine::BodyTwo *), drawComparator);

    for (int i = 0; i < numObjects; i++)
    {
        e = objects[i];
        switch (e->getClassType())
        {
        case ClassType::MISC:
            blitPoint((e));
            break;
        case ClassType::CIRC:
            blitCircle((e));
            break;
        case ClassType::REC:
            blitRect((e));
            break;
        case ClassType::BODY:
            blitPoint((e));
            break;
        case ClassType::PLAYER:
            blitCircle((e));
            break;
        case ClassType::ENEMY:
            blitCircle((e));
            break;
        case ClassType::WALL:
            blitRect((e));
            break;
        case ClassType::OGTILE:
            blitRect((e));
            break;
        case ClassType::GOAL:
            blitRect((e));
            break;
        case ClassType::FLOOR:
            blitPoint((e));
            break;
        case ClassType::GAMEENTITY:
            blitPoint((e));
            break;
        }
        auto fe = (WorldObjects::GameEntity *)(e);
        auto nn = (fe)->GetNumFixedNeighbours();
        for (int i = 0; i < nn; i++)
        {
            blitLine(fe->getPos(), fe->GetFixedNeighbourAtIndex(i)->getPos());
        }
    }
}

void Drawer::setRenderer(SDL_Renderer **r_)
{
    r = r_;
}

void Drawer::prepareScene(void)
{
    // SDL_SetRenderDrawColor(*r, 96, 128, 255, 255);
    SDL_SetRenderDrawColor(*r, 0, 0, 0, 255);

    SDL_RenderClear(*r);
}

void Drawer::presentScene(void)
{
    SDL_RenderPresent(*r);
}

void Drawer::DrawCircleOffsetScale(SDL_Renderer *renderer, PEngine::BodyTwo *c, double xo, double yo, double s, VertexTransformFunc f)
{

    int n = c->getNVert();
    VectorTwo *verts = c->getCachedVerts();

    SDL_FPoint points[n + 1];
    for (int i = 0; i < n; i++)
    {
        f(verts[i].getX(), verts[i].getY(), &points[i].x, &points[i].y);
        points[i].x = (points[i].x) * s + xo;
        points[i].y = (points[i].y) * s + yo;
    }
    points[n].x = points[0].x; //(verts[0].getX()) * s + xo;
    points[n].y = points[0].y; // (verts[0].getY()) * s + yo;

    SDL_RenderLines(renderer, points, n + 1);
}

void Drawer::DrawCircle(SDL_Renderer *renderer, PEngine::BodyTwo *c)
{

    int n = c->getNVert();
    VectorTwo *verts = c->getCachedVerts();

    SDL_FPoint points[n + 1];
    for (int i = 0; i < n; i++)
    {
        points[i].x = verts[i].getX();
        points[i].y = verts[i].getY();
    }
    points[n].x = verts[0].getX();
    points[n].y = verts[0].getY();

    SDL_RenderLines(renderer, points, n + 1);
}

void Drawer::DrawCircle(SDL_Renderer *renderer, double centreX, double centreY, double radius, int n)
{
    if (n < 3)
    {
        return;
    }
    SDL_FPoint points[n + 1];
    double inc = 2 * M_PI / n;
    double cur = 0;
    for (int i = 0; i <= n; i++)
    {
        points[i].x = centreX + radius * cos(cur);
        points[i].y = centreY + radius * sin(cur);
        // SDL_RenderPoint(renderer, points[i].x, points[i].y);
        cur += inc;
    }

    SDL_RenderLines(renderer, points, n + 1);
}