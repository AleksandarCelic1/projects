#include "../include_/quadtree.hpp"

QuadTree::QuadTree(SDL_Rect& boundary) 
{
  this->bounds_ = boundary;
  this->capacity_ = QUADTREE_CAPACITY;
  this->parent_ = false;

}

QuadTree::~QuadTree()
{
  for(auto iterator : this->elements_)
  {
    if(iterator != nullptr)
    {
      delete iterator;
      iterator = nullptr;
    }
  }

  for(auto iterator : this->children_)
  {
    if(iterator != nullptr)
    {
      delete iterator;
      iterator = nullptr;
    }
  }
}

void QuadTree::insert(ElementUI* elem) noexcept 
{

  if(!intersectDetection(elem->getDstRect()))
  {
    return;
  }

  if(this->parent_ == true)
  {
    // put the elem in one of your kids!
    return;
  }

  if(this->elements_.size() >= this->capacity_)
  {
    this->subdivision(elem); 
    this->parent_ = true;
    this->insert(elem);
    return;
  }

  this->elements_.push_back(elem);
  return;
}

/* 
  This functions divides the current quadtree into four smaller ones <!>
  Child one boundary {(x,y) , (x + w/2, y), (x, y + h/2), (x + w/2, y + h/2)}
  Child two boundary {(x + w/2, y), (x + w, y), (x + w/2, y + h/2), (x + w, y + h/2)}
  Child three boundary {(x, y + h/2), (x + w/2, y + h/2), (x, y + h), (x + w/2 , y+ h)}
  Child four boundary { ( x + w/2, y +h/2), ( x+w, y+h/2), (x+w/2, y+h), (x+w, y+h)}
  */
void QuadTree::subdivision(ElementUI* elem) noexcept
{
  SDL_Rect& boundary = this->bounds_;
  int x = boundary.x;
  int y = boundary.y;
  int w = boundary.w;
  int h = boundary.h;

  SDL_Rect child_one_boundary;
  SDL_Rect child_two_boundary;
  SDL_Rect child_three_boundary;
  SDL_Rect child_four_boundary;

  child_one_boundary.x = x;
  child_one_boundary.y = y;
  child_one_boundary.w = w / 2;
  child_one_boundary.h = h / 2;

  child_two_boundary.x = x + (w / 2);
  child_two_boundary.y = y;
  child_two_boundary.w = w / 2;
  child_two_boundary.h = h / 2;

  child_three_boundary.x = x;
  child_three_boundary.y = y + (h / 2);
  child_three_boundary.w = w / 2;
  child_three_boundary.h = h / 2;

  child_four_boundary.x = x + (w / 2);
  child_four_boundary.y = y + (h / 2);
  child_four_boundary.w = w / 2;
  child_four_boundary.h = h / 2;

  
  QuadTree* child_one = new QuadTree(child_one_boundary);
  QuadTree* child_two = new QuadTree(child_two_boundary);
  QuadTree* child_three = new QuadTree(child_three_boundary);
  QuadTree* child_four = new QuadTree(child_four_boundary);

  this->children_.push_back(child_one);
  this->children_.push_back(child_two);
  this->children_.push_back(child_three);
  this->children_.push_back(child_four);

  return;
}

void QuadTree::search(int mouse_x, int mouse_y) noexcept
{
  
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

