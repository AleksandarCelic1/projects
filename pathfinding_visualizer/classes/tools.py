import pygame

from .matrix import Matrix
from .mouse import Mouse





class Tools:
  def __init__(self, matrix: Matrix, renderer: pygame.Surface, mouse: Mouse):
  
    # The whole grid 
    self.matrix_object_: Matrix = matrix
    self.renderer_: pygame.Surface = renderer
    self.mouse_object_: Mouse = mouse


  def getMatrixObject(self):
    return self.matrix_object_
  
  def getRenderer(self):
    return self.renderer_
  
  def getMouseObject(self):
    return self.mouse_object_