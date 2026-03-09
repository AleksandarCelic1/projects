import pygame

from .constants import SCREEN_WIDTH, SCREEN_HEIGHT

from .classes.tile import Tile
from .classes.matrix import Matrix
from .classes.mouse import Mouse
from .classes.tools import Tools

def initializeEverything() -> Tools:

  matrix_object: Matrix = Matrix()
  mouse_object: Mouse = Mouse(0, 0)
  renderer_object: pygame.Surface = pygame.display.set_mode(())


  main_window = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
  pygame.display.set_caption("Pathfinding Visualizer <3")


  pass