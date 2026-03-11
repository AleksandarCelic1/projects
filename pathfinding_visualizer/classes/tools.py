import pygame

from .matrix import Matrix
from .mouse import Mouse
from .font import FontContainer
from ..constants import AlgorithmKeys, FontKeys






class Tools:
  def __init__(self, matrix: Matrix, renderer: pygame.Surface, mouse: Mouse, font_container: FontContainer):
  
    # The whole grid 
    self.matrix_object_: Matrix = matrix
    self.renderer_: pygame.Surface = renderer
    self.mouse_object_: Mouse = mouse
    self.font_container_object: FontContainer = font_container


  def getMatrixObject(self):
    return self.matrix_object_
  
  def getRenderer(self):
    return self.renderer_
  
  def getMouseObject(self):
    return self.mouse_object_
  
  def getFontContainer(self):
    return self.font_container_object