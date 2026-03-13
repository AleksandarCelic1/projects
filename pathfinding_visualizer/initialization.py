import pygame

from .constants import SCREEN_WIDTH, SCREEN_HEIGHT, hash_map_for_tile_pictures, TilePicturesKeys, FontKeys, AlgorithmKeys

from .classes.tile import Tile
from .classes.matrix import Matrix
from .classes.mouse import Mouse
from .classes.tools import Tools
from .classes.font import FontContainer

from .algorithms_.algorithm import Algorithm
from .algorithms_.A_star import AStarAlgorithm
from .algorithms_.Bfs import BfsAlgorithm
from .algorithms_.Dfs import DfsAlgorithm
from .algorithms_.Djikstra import DjikstraAlgorithm

def initializeEverything() -> Tools:

  matrix_object: Matrix = Matrix()
  mouse_object: Mouse = Mouse(0, 0)
  renderer_object = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
  pygame.display.set_caption("Pathfinding Visualizer <3")
  font_object = initFont()
  dictionary_of_algos = initAlgos()

  main_tools = Tools(matrix_object, renderer_object, mouse_object, font_object, dictionary_of_algos)


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

def initFont():
  font_container_object : FontContainer = FontContainer()

  font_container_object.getContainer()[FontKeys.MINECRAFT_FONT_12] = pygame.font.Font("pathfinding_visualizer/fonts/PressStart2P-Regular.ttf", 12)
  font_container_object.getContainer()[FontKeys.MINECRAFT_FONT_16] = pygame.font.Font("pathfinding_visualizer/fonts/PressStart2P-Regular.ttf", 16)
  font_container_object.getContainer()[FontKeys.MINECRAFT_FONT_20] = pygame.font.Font("pathfinding_visualizer/fonts/PressStart2P-Regular.ttf", 20)
  font_container_object.getContainer()[FontKeys.MINECRAFT_FONT_24] = pygame.font.Font("pathfinding_visualizer/fonts/PressStart2P-Regular.ttf", 24)

  return font_container_object
  
def initAlgos():
  bfs: BfsAlgorithm = BfsAlgorithm()
  dfs: DfsAlgorithm = DfsAlgorithm()
  djikstra: DjikstraAlgorithm = DjikstraAlgorithm()
  a_star: AStarAlgorithm = AStarAlgorithm()


  dictionary: dict[AlgorithmKeys, Algorithm] = {}
  dictionary[AlgorithmKeys.BFS] = bfs
  dictionary[AlgorithmKeys.DFS] = dfs
  dictionary[AlgorithmKeys.DJIKSTRA] = djikstra
  dictionary[AlgorithmKeys.A_STAR] = a_star

  return dictionary