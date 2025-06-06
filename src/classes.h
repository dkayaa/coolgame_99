#ifndef CLASS_H
#define CLASS_H

#include "defines.h"

class App;

namespace PEngine
{
    class BodyTwo;
    class VectorTwo;
}

namespace WorldObjects
{
    class GameEntity;
}

namespace ObjectVertexComputers
{
    void ComputeCircleVertices(PEngine::VectorTwo **vertices, PEngine::BodyTwo *body, int *n_vert);
    void ComputeRectVertices(PEngine::VectorTwo **vertices, PEngine::BodyTwo *body, int *n_vert);
    void ComputePointVertices(PEngine::VectorTwo **vertices, PEngine::BodyTwo *body, int *n_vert);
}

namespace LevelInstances
{
    void FlexLevel(int *n, int *n_enem, int *n_mt, PEngine::BodyTwo **p, PEngine::BodyTwo ***objects, PEngine::BodyTwo ***e, PEngine::BodyTwo ***m, int *mw, int *mh);
    PEngine::BodyTwo **Cage(int *n, PEngine::BodyTwo **p);
    PEngine::BodyTwo **RandomSpawns(int *n, PEngine::BodyTwo **p);
}

namespace ObjectSorters
{
    void BasicSort(PEngine::BodyTwo **object_array, int num_objects);
}

namespace MapHelpers
{
    void ComputeNearestTile(WorldObjects::GameEntity *e, WorldObjects::GameEntity **tiles, int tw, int grid_height, int grid_width, WorldObjects::GameEntity **nearest_tile);
    void BoundedBreadthFirstSearch(WorldObjects::GameEntity *start, int max_depth = 10);
}

namespace VertexTransformers
{
    void NoTransform(float x, float y, float *px, float *py);
    void IsoTransform(float x, float y, float *px, float *py);
}

#endif