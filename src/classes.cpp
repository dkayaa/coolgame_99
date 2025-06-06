#include <string>
#include <SDL3_image/SDL_image.h>
#include "classes.h"
#include <iostream>
#include <fstream>
#include <string>
#include "assert.h"
#include "PEngine/BodyTwo.h"
#include "PEngine/VectorTwo.h"
#include "WorldObjects/Enemy.h"
#include "WorldObjects/Player.h"
#include "WorldObjects/Wall.h"
#include "WorldObjects/Floor.h"
#include "WorldObjects/Goal.h"
#include "helpers.h"
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <tuple>

void ObjectSorters::BasicSort(PEngine::BodyTwo **object_array, int n_objects)
{
    std::sort(object_array, object_array + n_objects, [](PEngine::BodyTwo *b1, PEngine::BodyTwo *b2)
              { return PEngine::VectorTwo::Length(b1->getPos()) < PEngine::VectorTwo::Length(b2->getPos()); });
}

void LevelInstances::FlexLevel(int *n, int *n_enem, int *n_mt, PEngine::BodyTwo **p, PEngine::BodyTwo ***objects, PEngine::BodyTwo ***e, PEngine::BodyTwo ***m, int *mw, int *mh)
{
    std::ifstream file("../data/test.txt"); // Replace with your filename
    if (!file.is_open())
    {
        std::cerr << "Failed to open file.\n";
        return;
    }

    int bw = 40;      // block width
    int x_offset = 0; // superseded
    int y_offset = 0; // superseded

    // First Run Through To Compute The Number of Objects
    int n_objects = 0;
    int n_map_tiles = 0;
    int n_enemies = 0;

    std::string line;
    while (std::getline(file, line))
    {
        for (char c : line)
        {
            switch (c)
            {
            case 'W':
                n_objects++;
                n_map_tiles++;
                break;
            case 'P':
                n_objects++;
                n_objects++;
                n_map_tiles++;
                break;
            case 'E':
                n_objects++;
                n_objects++;
                n_enemies++;
                n_map_tiles++;
                break;
            case 'G':
                n_objects++;
                n_map_tiles++;
                break;
            case ' ':
                n_objects++;
                n_map_tiles++;
                break;
            }

            // std::cout << c << std::endl;
        }
    }

    // Reset to beginning
    file.clear();                 // Clear EOF flag
    file.seekg(0, std::ios::beg); // Move file pointer to start

    (*n) = n_objects;
    (*n_enem) = n_enemies;
    (*n_mt) = n_map_tiles;

    PEngine::BodyTwo **objs = (PEngine::BodyTwo **)malloc(sizeof(PEngine::BodyTwo *) * (*n));
    PEngine::BodyTwo **enemies = (PEngine::BodyTwo **)malloc(sizeof(PEngine::BodyTwo *) * (n_enemies));
    PEngine::BodyTwo **map = (PEngine::BodyTwo **)malloc(sizeof(PEngine::BodyTwo *) * (n_map_tiles));

    // Second Run Through To Generate Objects
    int i = 0;
    int j = 0;
    int object_ind = 0;
    int map_ind = 0;
    int enemies_ind = 0;
    while (std::getline(file, line))
    {
        j = 0;
        for (char c : line)
        {
            WorldObjects::GameEntity *e;
            switch (c)
            {
            case 'W':
                e = new WorldObjects::Wall(PEngine::VectorTwo(x_offset + j * bw, y_offset + i * bw), bw);
                e->setColour(PEngine::ShapeColour::GREEN);
                e->DoComputeVerts();
                objs[object_ind] = e;
                map[map_ind] = e;
                map_ind++;
                object_ind++;
                break;
            case 'P':
                e = new WorldObjects::Player(PEngine::VectorTwo(x_offset + j * bw, y_offset + i * bw), bw / 2 / 2);
                *p = e;
                e->DoComputeVerts();
                objs[object_ind] = e;
                object_ind++;
                // Still need a Floor Tile under the Player
                e = new WorldObjects::Floor(PEngine::VectorTwo(x_offset + j * bw, y_offset + i * bw));
                e->setColour(PEngine::ShapeColour::BLUE);
                e->DoComputeVerts();
                map[map_ind] = e;
                objs[object_ind] = e;
                map_ind++;
                object_ind++;
                break;
            case 'E':
                e = new WorldObjects::Enemy(PEngine::VectorTwo(x_offset + j * bw, y_offset + i * bw), bw / 2 / 2, *p);
                e->setColour(PEngine::ShapeColour::RED);
                e->DoComputeVerts();
                objs[object_ind] = e;
                object_ind++;
                enemies[enemies_ind] = e;
                enemies_ind++;
                // Still need a Floor Tile under the Enemy
                e = new WorldObjects::Floor(PEngine::VectorTwo(x_offset + j * bw, y_offset + i * bw));
                e->setColour(PEngine::ShapeColour::BLUE);
                e->DoComputeVerts();
                objs[object_ind] = e;
                map[map_ind] = e;
                map_ind++;
                object_ind++;
                break;
            case 'G':
                e = new WorldObjects::Goal(PEngine::VectorTwo(x_offset + j * bw, y_offset + i * bw), bw);
                e->setColour(PEngine::ShapeColour::RED);
                e->DoComputeVerts();
                objs[object_ind] = e;
                map[map_ind] = e;
                map_ind++;
                object_ind++;
                break;
            case ' ':
                e = new WorldObjects::Floor(PEngine::VectorTwo(x_offset + j * bw, y_offset + i * bw));
                e->setColour(PEngine::ShapeColour::BLUE);
                e->DoComputeVerts();
                objs[object_ind] = e;
                map[map_ind] = e;
                map_ind++;
                object_ind++;
                break;
            }
            j++;
        }
        i++;
    }

    // map width and height.
    (*mw) = j;
    (*mh) = i;

    // here we link neightbours to Floor tiles
    // not sure if this should go here : S
    // not sure if this will be necessary eventually.
    for (int i = 0; i < object_ind; i++)
    {
        if (objs[i]->getClassType() != PEngine::ClassType::FLOOR)
        {
            continue;
        }
        for (int j = 0; j < object_ind; j++)
        {
            // this needs to change too.
            if (objs[i]->getPos() == objs[j]->getPos())
            {
                continue;
            }
            if (i <= j)
            {
                continue;
            }

            if (objs[j]->getClassType() != PEngine::ClassType::FLOOR)
            {
                continue;
            }

            if (PEngine::VectorTwo::Length(objs[i]->getPos() - objs[j]->getPos()) <= 1.0 * bw)
            {
                ((WorldObjects::GameEntity *)objs[i])->AddFixedNeighbour(((WorldObjects::GameEntity *)objs[j]));
                ((WorldObjects::GameEntity *)objs[j])->AddFixedNeighbour(((WorldObjects::GameEntity *)objs[i]));
            }
        }
    }
    *objects = objs;
    *m = map;
    *e = enemies;
    return;
}

PEngine::BodyTwo **LevelInstances::Cage(int *n, PEngine::BodyTwo **p)
{
    int w = 5;   // cage length
    int l = 5;   // cage width
    int bw = 20; // block width
    int x_offset = 100;
    int y_offset = 100;
    int n_players = 1;
    int n_walls = (w * 2) + 2 * (l - 2);
    (*n) = (n_walls + n_players);
    PEngine::BodyTwo **objs = (PEngine::BodyTwo **)malloc(sizeof(PEngine::BodyTwo *) * ((*n)));

    for (int i = 0; i < n_players; i++)
    {
        objs[i] = new WorldObjects::Player(PEngine::VectorTwo(x_offset + 0, y_offset + 0), 5);
    }

    int ind = 0;
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < l; j++)
        {
            if (j == 0 || (j == (l - 1)))
            {
                objs[n_players + ind] = new WorldObjects::Wall(PEngine::VectorTwo(x_offset + j * bw, y_offset + i * bw), bw);
                ind++;
            }
            else if (i == 0 || (i == (w - 1)))
            {
                objs[n_players + ind] = new WorldObjects::Wall(PEngine::VectorTwo(x_offset + j * bw, y_offset + i * bw), bw);
                ind++;
            }
        }
    }
    (*p) = objs[0];
    return objs;
}

PEngine::BodyTwo **LevelInstances::RandomSpawns(int *n, PEngine::BodyTwo **p)
{
    // BodyTwo* p = nullptr; //player
    auto r = Helpers::RandomHelper();
    auto i = 10; // r.randInRange(1, 50);
    *n = i;
    PEngine::BodyTwo **objs = (PEngine::BodyTwo **)malloc(sizeof(PEngine::BodyTwo *) * (*n));
    for (int j = 0; j < i; j++)
    {
        auto s = (PEngine::ShapeType)r.randInRange(0, 2);
        // auto s = PEngine::ShapeType::CIRCLE;
        double x = 0.0;
        double y = 0.0;
        if (j == 0)
        {
            objs[j] = new PEngine::BodyTwo(PEngine::VectorTwo(x, y), PEngine::VectorTwo(0, 0), 0, 0, 0.0, 40, 40, PEngine::ShapeType::RECT);
            // objs[j] = new PEngine::CircleBodyTwo(PEngine::VectorTwo(x, y), PEngine::VectorTwo(0, 0), 0, 0, 10);
        }
        else
        {
            if (s == PEngine::ShapeType::CIRCLE)
            {
                x = (double)r.randInRange(100, 1000);
                y = (double)r.randInRange(100, 500);
                auto rad = (double)r.randInRange(10, 30);
                // objs[j] = new PEngine::CircleBodyTwo(PEngine::VectorTwo(x, y), PEngine::VectorTwo(0, 0), 0, 0, rad, false);
                objs[j] = new PEngine::BodyTwo(PEngine::VectorTwo(x, y), PEngine::VectorTwo(0, 0), 0.0, 0.0, rad, 0.0, 0.0, PEngine::ShapeType::CIRCLE, false, true);
            }
            else if (s == PEngine::ShapeType::RECT)
            {
                x = (double)r.randInRange(100, 1000);
                y = (double)r.randInRange(100, 500);
                auto l = (double)r.randInRange(5, 30);
                auto w = (double)r.randInRange(5, 30);
                objs[j] = new PEngine::BodyTwo(PEngine::VectorTwo(x, y), PEngine::VectorTwo(0, 0), 0, 0, 0.0, l, w, PEngine::ShapeType::RECT);

                // objs[j] = new PEngine::RectBodyTwo(PEngine::VectorTwo(x, y), PEngine::VectorTwo(0, 0), 0, 0, l, w, true);
            }
            // objs[j] =  new PEngine::RectBodyTwo(PEngine::VectorTwo(100, 100), PEngine::VectorTwo(0,0),0,0,40,40);
        }

        std::cout << "Created " << j << " of " << i << " Shapes @ (" << x << "," << y << ")" << std::endl;
    }
    (*p) = objs[0];
    // std::cout<<"testing"<<std::endl;
    return objs;
}

void ObjectVertexComputers::ComputeCircleVertices(PEngine::VectorTwo **vertices, PEngine::BodyTwo *body, int *n_vert)
{
    free(*vertices);
    *n_vert = 8;
    *vertices = (PEngine::VectorTwo *)malloc(sizeof(PEngine::VectorTwo) * (*n_vert));
    assert((*vertices) != NULL);
    double inc = 2 * M_PI / 8;
    double cur = 0;
    for (int i = 0; i < 8; i++)
    {
        (*vertices)[i] = PEngine::VectorTwo((*body).getPos().getX() + (*body).getRadius() * cos(cur), (*body).getPos().getY() + (*body).getRadius() * sin(cur));
        cur += inc;
    }
}

void ObjectVertexComputers::ComputeRectVertices(PEngine::VectorTwo **vertices, PEngine::BodyTwo *body, int *n_vert)
{
    free(*vertices);
    *n_vert = 4;
    *vertices = (PEngine::VectorTwo *)malloc(sizeof(PEngine::VectorTwo) * (*n_vert));
    assert((*vertices) != NULL);
    (*vertices)[0] = PEngine::VectorTwo((*body).getPos().getX() - ((*body).getW() / 2), (*body).getPos().getY() - ((*body).getL() / 2));
    (*vertices)[1] = PEngine::VectorTwo((*body).getPos().getX() - ((*body).getW() / 2), (*body).getPos().getY() + ((*body).getL() / 2));
    (*vertices)[2] = PEngine::VectorTwo((*body).getPos().getX() + ((*body).getW() / 2), (*body).getPos().getY() + ((*body).getL() / 2));
    (*vertices)[3] = PEngine::VectorTwo((*body).getPos().getX() + ((*body).getW() / 2), (*body).getPos().getY() - ((*body).getL() / 2));
}

void ObjectVertexComputers::ComputePointVertices(PEngine::VectorTwo **vertices, PEngine::BodyTwo *body, int *n_vert)
{
    free(*vertices);
    *n_vert = 1;
    *vertices = (PEngine::VectorTwo *)malloc(sizeof(PEngine::VectorTwo) * (*n_vert));
    assert((*vertices) != NULL);
    (*vertices)[0] = PEngine::VectorTwo((*body).getPos().getX(), (*body).getPos().getY());
}

void MapHelpers::ComputeNearestTile(WorldObjects::GameEntity *e, WorldObjects::GameEntity **tiles, int tw, int grid_height, int grid_width, WorldObjects::GameEntity **nearest_tile)
{
    if (e->getClassType() == PEngine::ClassType::PLAYER)
    {
        auto p = (*e).getPos();
        int x = 1;
    }
    auto p = (*e).getPos();
    int x = (int)((p.getX() + tw / 2) / (double)tw);
    int y = (int)((p.getY() + tw / 2) / (double)tw);
    auto n = tiles[y * grid_width + x];
    (*e).AddVariableNeighbour(n);
    (*n).AddVariableNeighbour(e);
    *nearest_tile = n;
}

void MapHelpers::BoundedBreadthFirstSearch(WorldObjects::GameEntity *start, int max_depth)
{
    using queue_elem = std::tuple<WorldObjects::GameEntity *, int>;

    std::unordered_map<int, WorldObjects::GameEntity *> backtrack;
    std::unordered_map<int, bool> visited;
    backtrack[start->GetID()] = start;
    std::queue<queue_elem> q;
    q.push({start, 0});
    while (q.size() != 0)
    {
        queue_elem current = q.front();
        q.pop();
        WorldObjects::GameEntity *e = std::get<0>(current);
        int depth = std::get<1>(current);

        visited[e->GetID()] = true;

        // abstract this to a handler func
        if (e->getClassType() == PEngine::ClassType::ENEMY)
        {
            WorldObjects::GameEntity *n2 = backtrack[backtrack[e->GetID()]->GetID()];
            PEngine::VectorTwo d = PEngine::VectorTwo::Normalise(n2->getPos() - e->getPos());
            e->setV(d * 200);
        }
        //

        if (depth + 1 > max_depth)
        {
            continue;
        }

        for (int i = 0; i < e->GetNumFixedNeighbours(); i++)
        {
            WorldObjects::GameEntity *n = e->GetFixedNeighbourAtIndex(i);
            if (visited.contains(n->GetID()))
            {
                continue;
            }
            q.push({n, depth + 1});
            backtrack[n->GetID()] = e;
        }

        for (int i = 0; i < e->GetNumVariableNeighbours(); i++)
        {
            WorldObjects::GameEntity *n = e->GetVariableNeighbourAtIndex(i);
            if (visited.contains(n->GetID()))
            {
                continue;
            }
            q.push({n, depth + 1});
            backtrack[n->GetID()] = e;
        }
    }
}

void VertexTransformers::NoTransform(float x, float y, float *px, float *py)
{
    *px = x;
    *py = y;
}

void VertexTransformers::IsoTransform(float x, float y, float *px, float *py)
{
    *px = x - y;
    *py = (x + y) * 0.5;
}
