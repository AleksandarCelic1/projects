#include "../include_/quadtree.hpp"

QuadTree::QuadTree(SDL_Rect& boundary) 
{
  this->bounds_ = boundary;
  this->capacity_ = QUADTREE_CAPACITY;
  this->parent_ = false;

}

QuadTree::~QuadTree()
{
  /*
    QuadTree Shouldnt delete the elements as he doesnt really own them but reather
    just reads them/ obersves them and it should be handled by some other class, but
    to do this correctly to be visible to across every other object that uses the same elementUI* allocated
    object we must pass a reference and EVERYONE must use the same reference <!>
  */
  this->elements_.clear();

  for(auto& iterator : this->children_)
  {
    if(iterator != nullptr)
    {
      delete iterator;
      iterator = nullptr;
    }
  }
}


void QuadTree::categorize(ElementUI* elem) noexcept
{
  for (auto& iterator : this->children_)
  {
    if(iterator->intersectDetection(elem->getDstRect()))
    {
      iterator->insert(elem);
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
    this->categorize(elem);
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


  for (auto iterator : this->elements_)
  {
    categorize(iterator);
  }

  return;
}

ElementUI* QuadTree::search(int mouse_x, int mouse_y) noexcept
{
  if(!detectingMouseClick(this->bounds_, mouse_x, mouse_y))
  {
    return nullptr;
  }

  if(this->parent_ == true)
  {
    for(auto iterator : this->children_)
    {
      ElementUI* tmp = iterator->search(mouse_x, mouse_y);
      
      if(tmp != nullptr)
      {
        return tmp;
      }
    }
    return nullptr;
  }

  for (auto iterator : this->elements_)
  {
    if(iterator->detectMouseClick(mouse_x, mouse_y))
    {
      ElementUI* tmp = iterator;
      return tmp;
    }
  }

  return nullptr;
}

/*
  This functions checks does the provided SDL_Rect intersect
  with this Quadtrees boundary 
*/
bool QuadTree::intersectDetection(const SDL_Rect& rect) noexcept
{
  return RectUtils::intersectDetection(this->bounds_, rect);
}

bool QuadTree::detectingMouseClick(const SDL_Rect& source, int mouse_x, int mouse_y) noexcept
{
  return RectUtils::detectMouseClick(source, mouse_x, mouse_y);
}

void QuadTree::debugOutline(SDL_Renderer* main_renderer) noexcept
{
  RectUtils::debugOutline(main_renderer, this->bounds_);

  if(this->parent_ == true)
  {
    for (auto iterator : this->children_)
    {
      iterator->debugOutline(main_renderer);
    }
  }
  else
  {
    for (auto iterator : this->elements_)
    {
      RectUtils::debugOutline(main_renderer, iterator->getDstRect());
    }
  }
}