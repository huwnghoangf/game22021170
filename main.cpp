#include "basefunc.h"
#include "baseobject.h"
#include "gamemap.h"
#include <fstream>
#include <ctime>

using namespace std;
int mt[11][11];
int mt1[11][11];
int mt2[11][11];
int flag[11][11];
int numofbom;
int numofflag=0;
int ktlose = 0;

    GameMap game_map;
    

    GameMap game_map1;
    
void khoitao()
{
    for(int i=0;i<9;i++)
     for(int j=0;j<9;j++)
      flag[i][j]=3;
}

bool kt()
{
    bool win = true;
    for(int i=0;i<9;i++)
     for(int j=0;j<9;j++)
      if(mt[i][j]==flag[i][j])
       win=true;
       else return false;
    return win;
}


void taomap1()
{
    ofstream file("mtbom1.dat");
    for(int i=0;i<9;i++)
    {
     for(int j=0;j<9;j++)
       {
        mt1[i][j]=0;
        file<<mt1[i][j]<<" ";
       }
       file<<endl;
    }
    file.close();
}

void taomap()
{
    ofstream file ("mtbom.dat");
    for(int i=0;i<9;i++)
    {
     for(int j=0;j<9;j++)
       {
         mt[i][j]=3;
       }
    }
    int row,col;
    srand(time(NULL));
    numofbom = 10 + rand() % 6;
    while(numofbom!=0)
    {
      row = rand() % 9;
      col = rand() % 9;
      if(mt[row][col]==1)
       {
        continue;
       }
       mt[row][col]=1;
       numofbom--;
    }
    for(int i=0;i<9;i++)
    {
     for(int j=0;j<9;j++)
       {
        file<<mt[i][j]<<" ";
       }
       file<<endl;
    }
    file.close();
}

void taomap2()
{
    ofstream file("mtbom2.dat");
    for(int i =0;i<9;i++)
     {
        for(int j=0;j<9;j++)
         {if(mt[i][j]==1)
          {
            mt2[i][j]=-1;
          }
          else
          {
            if(i-1>=0 && j-1>=0 && mt[i-1][j-1]==1) mt2[i][j]++;
            if(i-1>=0 && j>=0  && mt[i-1][j]==1) mt2[i][j]++;
            if(i-1>=0 && j+1<9 && mt[i-1][j+1]==1) mt2[i][j]++;
            if(i>=0 && j+1<9 && mt[i][j+1]==1) mt2[i][j]++;
            if(i+1<9 && j+1<9 && mt[i+1][j+1]==1) mt2[i][j]++;
            if(i+1<9 && j<9 && mt[i+1][j]==1) mt2[i][j]++;
            if(i+1<9 && j-1>=0 && mt[i+1][j-1]==1) mt2[i][j]++;
            if(i>=0 && j-1>=0 && mt[i][j-1]==1) mt2[i][j]++;
          }
          }
     }
    for(int i=0;i<9;i++)
    {
     for(int j=0;j<9;j++)
       {
        file<<mt2[i][j]<<" ";
       }
       file<<endl;
    }
    file.close();
}

void loang(int x, int y)
{
        for(int i =x-1;i<=x+1;i++)
     {
        for(int j=y-1;j<=y+1;j++)
        {
           if (i<0 || i>=9 || j<0 || j>=9 || (i==x && j==y))
               continue;
            if(mt2[i][j]>0 && game_map1.game_map_.tile[i][j]==0) 
            {
                game_map1.game_map_.tile[i][j]=mt2[i][j]+3;
            }
            if(mt2[i][j]==0 && game_map1.game_map_.tile[i][j]==0) 
            {
                game_map1.game_map_.tile[i][j]=mt2[i][j]+3;
                loang(i,j);
            }
        }
     }
}

BaseObject g_background;
BaseObject g_background1;
BaseObject g_background2;

bool LoadBackground()
{
    bool ret = g_background.LoadImg("bkgn.png",g_screen);
    if(ret== false)
     return false;

    return true;
}

bool LoadWin()
{
    bool ret = g_background1.LoadImg("win.png",g_screen);
    if(ret== false)
     return false;

    return true;
}

bool LoadLose()
{
    bool ret = g_background2.LoadImg("lose.png",g_screen);
    if(ret== false)
     return false;

    return true;
}

void PollEvent(SDL_Event* event)
{
    if(event ->type == SDL_MOUSEBUTTONDOWN)
    {
        int xm,ym;
        SDL_GetMouseState(&xm,&ym);

        int j= xm/TILE_SIZE;
        int i= ym/TILE_SIZE;
        bool insite=false;
        if(i>=0 && i<9 && j>=0 && j<9) insite =true;
        if(insite==true) 
          switch (event -> button.button)
          {
           case SDL_BUTTON_RIGHT:
               if(game_map1.game_map_.tile[i][j]==0 && flag[i][j]==3)
                {
                    
                    if(numofflag<10) 
                     {
                        numofflag++;
                        game_map1.game_map_.tile[i][j]=2;
                        flag[i][j]=1;
                     }
                    if(kt()==true) return;
                }   
                else
               if(game_map1.game_map_.tile[i][j]==2 && flag[i][j]==1)
                   {
                    flag[i][j]=3;
                    game_map1.game_map_.tile[i][j]=0;
                    numofflag--;
                   }
                break;
           case SDL_BUTTON_LEFT:
              if(game_map1.game_map_.tile[i][j]==0 )
                {
                    if(mt[i][j]==1)
                    {
                        ktlose = 1;
                    }
                    else
                    {
                    game_map1.game_map_.tile[i][j]=mt2[i][j]+3;
                    if (mt2[i][j]==0) loang(i,j);
                    }
                }
                break;
            default:
               break;
          }
    }
    
}



bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret<0)
     return false;
    
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("dofminf", 
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, 
                                 SCREEN_WIDTH,SCREEN_HEIGHT,
                                 SDL_WINDOW_SHOWN);
    if(g_window == NULL)
    {
        success =false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
        {
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(g_screen,0,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
            {
                success = false;
            }
        }
    }
    return success;
}

void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen=NULL;
    SDL_DestroyWindow(g_window);
    g_window=NULL;
    IMG_Quit();
    SDL_Quit();
}

int main( int arc, char* argv[])
{
    taomap();
    taomap1();
    taomap2();
    khoitao();
    if(InitData()== false)
     return -1;
    if (LoadBackground()==false)
     return -1;
    game_map.LoadMap( "mtbom.dat" );
    game_map.LoadTiles(g_screen);
    
    game_map1.LoadMap( "mtbom1.dat" );
    game_map1.LoadTiles(g_screen);

    bool is_quit=false;
    while(!is_quit)
    {
        while (SDL_PollEvent(&g_event)!=0)
        {
            if(g_event.type == SDL_QUIT)
            {
                is_quit=true;
            }         
            PollEvent(&g_event);
            game_map1.DrawMap(g_screen);
            
                
        }
        SDL_RenderClear(g_screen);
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);

        g_background.Render(g_screen,NULL);
    
        game_map.DrawMap(g_screen);
        game_map1.DrawMap(g_screen);
        if(kt()==true)
    {
       if (LoadWin()==false) return -1; 
     SDL_RenderClear(g_screen);
     SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
     g_background1.Render(g_screen,NULL);
    }
        if(ktlose == 1)
        {
            if (LoadLose()==false) return -1; 
     SDL_RenderClear(g_screen);
     SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
     g_background2.Render(g_screen,NULL);
        }
        SDL_RenderPresent(g_screen);
    }
    close();
    return 0;
}
