import pygame

from ..constants import FontKeys


class FontContainer:
  def __init__(self):
    self.container_map_: dict[FontKeys, pygame.font.Font] = None

  def getContainer(self):
    return self.container_map_
  
  def addFont(self, key: FontKeys, new_font: pygame.font.Font,):
    self.container_map_[key] = new_font

    


