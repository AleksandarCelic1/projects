import pygame

from .constants import SCREEN_WIDTH, SCREEN_HEIGHT, hash_map_for_tile_pictures, TilePicturesKeys

from .classes.tile import Tile
from .classes.matrix import Matrix
from .classes.mouse import Mouse
from .classes.tools import Tools

def initializeEverything() -> Tools:

  matrix_object: Matrix = Matrix()
  mouse_object: Mouse = Mouse(0, 0)
  renderer_object = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
  pygame.display.set_caption("Pathfinding Visualizer <3")

  main_tools = Tools(matrix_object, renderer_object, mouse_object)

  initializeTilePictures()


  return main_tools


def initializeTilePictures():

  white_tile_src = pygame.image.load("pathfinding_visualizer/photos_/WhiteTile.png").convert_alpha()
  black_tile_src = pygame.image.load("pathfinding_visualizer/photos_/BlackTile.png").convert_alpha()
  green_tile_src = pygame.image.load("pathfinding_visualizer/photos_/GreenTile.png").convert_alpha()
  red_tile_src = pygame.image.load("pathfinding_visualizer/photos_/RedTile.png").convert_alpha()
  light_grey_tile_src = pygame.image.load("pathfinding_visualizer/photos_/LightGreyTile.png").convert_alpha()


  hash_map_for_tile_pictures[TilePicturesKeys.WHITE_TILE] = white_tile_src
  hash_map_for_tile_pictures[TilePicturesKeys.BLACK_TILE] = black_tile_src
  hash_map_for_tile_pictures[TilePicturesKeys.GREEN_TILE] = green_tile_src
  hash_map_for_tile_pictures[TilePicturesKeys.RED_TILE] = red_tile_src
  hash_map_for_tile_pictures[TilePicturesKeys.LIGHT_GREY_TILE] = light_grey_tile_src

