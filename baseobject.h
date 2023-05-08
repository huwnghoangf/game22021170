#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "basefunc.h" 

class BaseObject
{
  public:
   BaseObject();
   ~BaseObject();
   void SetRect(const int& x, const int& y) {rect_.x=x;rect_.y=y;}
   SDL_Rect GetRect() const {return rect_;}
   SDL_Texture* GetObject() const {return p_object_;}

   bool LoadImg(string path, SDL_Renderer* screen);
   void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
   void Free();
   //string GetName(){return file_name;}

  protected:
   SDL_Texture* p_object_;
   SDL_Rect rect_;
   float scales;
   //string file_name;
};


#endif