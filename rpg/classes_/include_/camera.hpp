#ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera
{
  private:
    int x_axis_;
    int y_axis_;

    int width_;
    int height_;

  public:

    // Constructor Copy Constructor Destructor
    Camera() = default;
    Camera(int new_x, int new_y, int new_w, int new_h);
    Camera(const Camera& copy) = delete;
    ~Camera() = default;


    // Getters
    int getXAxis() const { return this->x_axis_; }
    int getYAxis() const { return this->y_axis_; }
    int getWidth() const { return this->width_; }
    int getHeight() const { return this->height_; }

    // Setters
    void setXAxis(int& new_x_axis) noexcept { this->x_axis_ = new_x_axis; }
    void setYAxis(int& new_y_axis) noexcept { this->y_axis_ = new_y_axis; }
    void setWidth(int& new_width) noexcept { this->width_ = new_width; }
    void setHeight(int& new_height) noexcept { this->height_ = new_height; }

    





};


#endif