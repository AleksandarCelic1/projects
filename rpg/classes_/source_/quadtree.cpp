#include "../include_/quadtree.hpp"



void QuadTree::insert(ElementUI* elem) noexcept 
{
  if(this->parent_ == true)
  {
    // put the elem in one of your kids!
    return;
  }

  if(this->elements_.size() >= this->capacity_)
  {
    this->subdivision(elem); // this will make 4 new kids 
    this->parent_ = true;
    this->insert(elem); // will now go into parent true if block
    return;
  }

  if(intersectDetection(elem->getDstRect()))
  {
    this->elements_.push_back(elem);
    return;
  }

  std::cout << "[ERROR] -> [QuadTree::insert] -> How did you even manage to come here ?!" << std::endl;
}

void QuadTree::subdivision(ElementUI* elem) noexcept
{
  /* We need to divide the boundary to 4 boundaries

    Child one boundary {(x,y) , (x + w/2, y), (x, y + h/2), (x + w/2, y + h/2)}

    Child two boundary {(x + w/2, y), (x + w, y), (x + w/2, y + h/2), (x + w, y + h/2)}

    Child three boundary {(x, y + h/2), (x + w/2, y + h/2), (x, y + h), (x + w/2 , y+ h)}

    Child four boundary { ( x + w/2, y +h/2), ( x+w, y+h/2), (x+w/2, y+h), (x+w, y+h)}


    then find out where should be with insert or more specific functions 

  */


}


/*
  This functions checks does the provided SDL_Rect intersect
  with this Quadtrees boundary 
*/
bool QuadTree::intersectDetection(const SDL_Rect& rect) noexcept
{
  SDL_Rect& placeholder = this->bounds_;

  int x = rect.x;
  int y = rect.y;
  int w = rect.w;
  int h = rect.h;

  if((x <= placeholder.x + placeholder.w)
  && (x + w >= placeholder.x)
  && (y <= placeholder.y + placeholder.h)
  && (y + h >= placeholder.y))
  {
    return true;
  }

  return false;
}