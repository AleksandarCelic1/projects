import pygame

from abc import ABC, abstractmethod

from ..classes.matrix import Matrix
from ..classes.tile import Tile

class Algorithm(ABC):
  def __init__(self):
    
    self.text_src: pygame.Surface = None
    self.text_rect: pygame.Rect = None 
    pass

  @abstractmethod
  def runAlgorithm(self, grid: Matrix, source_tile: Tile, target_tile: Tile, renderer: pygame.Surface):
    pass


  # Getters
  def getTextSrc(self):
    return self.text_src
  
  def getTextRect(self):
    return self.text_rect
  
  # Setters
  def setTextSrc(self, src: pygame.Surface):
    self.text_src = src

  def setTextRect(self, dst: pygame.Rect):
    self.text_rect = dst

  
