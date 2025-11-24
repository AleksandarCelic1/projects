#ifndef TORCH_HPP
#define TORCH_HPP

#include "mapObjects.hpp"

enum class TorchType
{
  VERTICAL_TORCH,
  VERTICAL_TORCH_INVERTED,
  HORIZONTAL_TORCH
};


class Torch : virtual public MapObjects
{
  TorchType type_;

  public:
    Torch(TorchType x);
    Torch(const Torch& copy) = delete;
    ~Torch() = default;

    TorchType getType() const { return this->type_;}

    void setType(TorchType x) { this->type_ = x;}

    void updateAnimation(float delta_time) override;
};

#endif