#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "elementUI.hpp"

class QuadTree
{
  private:
    size_t capacity_;
    bool parent_;


    SDL_Rect bounds_;
    std::vector<QuadTree*> children_;
    std::vector<ElementUI*> elements_;

  public:
    // Constructor Destructor Copy Constructor
    QuadTree() = default;
    QuadTree(SDL_Rect& bounds);
    QuadTree(const QuadTree& copy) = delete;
    ~QuadTree();

    // Getters
    // Setters

    // Functions
    void insert(ElementUI* elem) noexcept;
    void search(int mouse_x, int mouse_y) noexcept;

    void subdivision(ElementUI* elem) noexcept;
    bool intersectDetection(const SDL_Rect& rect) noexcept;


};

#endif