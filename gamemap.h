#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "basefunc.h"
#include "baseobject.h"

#define MAX_TILES 20

class TILEMAT : public BaseObject
{
    public:
     TILEMAT() {;}
     ~TILEMAT() {;}
    
};

class GameMap
{
   public:
    GameMap(){;}
    ~GameMap(){;}

    void LoadMap( const char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    MAP game_map_;
   private:
     
     TILEMAT tile_mat[MAX_TILES];

};





#endif