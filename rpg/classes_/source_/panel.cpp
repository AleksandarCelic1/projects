#include "../include_/panel.hpp"

Panel::Panel(const TextureAsset& asset, int scaling_factor, float time_passed, float panel_delay, float smooth_duration) 
 : ElementUI(asset, scaling_factor), 
   time_passed_(time_passed),
   panel_delay_(panel_delay),
   smooth_duration_(smooth_duration)
  
  {}

Panel::~Panel() {}

