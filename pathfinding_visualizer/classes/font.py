import pygame

from enum import Enum
from ..constants import FontKeys

class FontColor(Enum):
  WHITE = (255, 255, 255)
  BLACK = (0, 0, 0)

class FontContainer:
  def __init__(self):
    self.container_map_: dict[FontKeys, pygame.font.Font] = None

  def getContainer(self):
    return self.container_map_
  
  def addFont(self, key: FontKeys, new_font: pygame.font.Font,):
    self.container_map_[key] = new_font

    


