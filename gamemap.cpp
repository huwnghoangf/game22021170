#include"gamemap.h"
#include"baseobject.h"


void GameMap :: LoadMap(const char* name)
{
    FILE* fp = NULL;
    fopen_s(&fp,name, "rb");
    if(fp == NULL)
    {
        return;
    }

    game_map_.max_x_ =0;
    game_map_.max_y_ = 0;
    for(int i=0;i< MAX_MAP_Y;i++)
    {
        for(int j=0;j< MAX_MAP_Y;j++)
        {
            fscanf_s(fp,"%d", &game_map_.tile[i][j]);
            int val = game_map_.tile[i][j];
            if(val >0)
            {
                if(j>game_map_.max_x_)
                {
                    game_map_.max_x_ = j;
                }
                if( i> game_map_.max_y_)
                {
                    game_map_.max_y_=i;
                }
            }
        }
    }

    game_map_.max_x_ = (game_map_.max_x_ +1) * TILE_SIZE;
    game_map_.max_y_ = (game_map_.max_y_ +1) * TILE_SIZE;

    game_map_.start_x_=0;
    game_map_.start_y_=0;
    //game_map_.file_name_=name;

    fclose(fp);
}

void GameMap::LoadTiles(SDL_Renderer* screen)
{
    char file_img[30];
    FILE* fp = NULL;

    for(int i=0;i<MAX_TILES;i++)
    {
        sprintf_s(file_img,"%d.png",i);
        fopen_s(&fp,file_img, "rb");
        if(fp==NULL)
        {
            continue;
        }
        fclose(fp);
        tile_mat[i].LoadImg(file_img,screen);

    }
}

void GameMap :: DrawMap(SDL_Renderer* screen)
{

    for(int i=0;i<SCREEN_HEIGHT/TILE_SIZE;i+= 1)
    {
        //map_x= game_map_.start_x_/TILE_SIZE;
        for(int j=0;j<SCREEN_WIDTH/TILE_SIZE;j+= 1)
        {
            int val = game_map_.tile[i][j];
            if (val>=0 /*&& tile_mat[val].GetName()!=""*/)
            {
                tile_mat[val].SetRect(j*TILE_SIZE,i*TILE_SIZE);
                tile_mat[val].Render(screen);
            }
            //map_x++;
        }
        //map_y++;
    }
}