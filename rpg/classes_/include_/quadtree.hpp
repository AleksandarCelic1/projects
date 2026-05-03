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
    void subdivision(ElementUI* elem) noexcept;
    void categorize(ElementUI* elem) noexcept;

    ElementUI* search(int mouse_x, int mouse_y) noexcept;

    bool intersectDetection(const SDL_Rect& rect) noexcept;
    bool detectingMouseClick(const SDL_Rect& source, int mouse_x, int mouse_y) noexcept;


    void debugOutline(SDL_Renderer* main_renderer) noexcept;
};

#endif