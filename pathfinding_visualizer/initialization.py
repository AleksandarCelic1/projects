import pygame

from .constants import SCREEN_WIDTH, SCREEN_HEIGHT, hash_map_for_tile_pictures, TilePicturesKeys, FontKeys, AlgorithmKeys, StringsAlgoEnums

from .classes.tile import Tile
from .classes.matrix import Matrix
from .classes.mouse import Mouse
from .classes.tools import Tools
from .classes.font import FontContainer
from .classes.rendererFunctions import RenderingFunctionsContainer

from .algorithms_.algorithm import Algorithm
from .algorithms_.A_star import AStarAlgorithm
from .algorithms_.Bfs import BfsAlgorithm
from .algorithms_.Dfs import DfsAlgorithm
from .algorithms_.Djikstra import DjikstraAlgorithm

from .classes.rendererFunctions import EVERY_BOX_WIDTH, EVERY_BOX_X, EVERY_BOX_HEIGHT, BFS_Y, DFS_Y, DJIKSTRA_Y, A_STAR_Y


def initializeEverything() -> Tools:

  matrix_object: Matrix = Matrix()
  mouse_object: Mouse = Mouse(0, 0)
  renderer_object = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
  pygame.display.set_caption("Pathfinding Visualizer <3")
  font_object = initFont()
  dictionary_of_algos = initAlgos()
  rendering_func_object = RenderingFunctionsContainer()

  main_tools = Tools(matrix_object, renderer_object, mouse_object, font_object, dictionary_of_algos, rendering_func_object)


  initializeTilePictures()
  initText(main_tools)


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

  font_container_object.getContainer()[FontKeys.MINECRAFT_FONT_12] = pygame.font.Font("pathfinding_visualizer/fonts_/PressStart2P-Regular.ttf", 12)
  font_container_object.getContainer()[FontKeys.MINECRAFT_FONT_16] = pygame.font.Font("pathfinding_visualizer/fonts_/PressStart2P-Regular.ttf", 16)
  font_container_object.getContainer()[FontKeys.MINECRAFT_FONT_20] = pygame.font.Font("pathfinding_visualizer/fonts_/PressStart2P-Regular.ttf", 20)
  font_container_object.getContainer()[FontKeys.MINECRAFT_FONT_24] = pygame.font.Font("pathfinding_visualizer/fonts_/PressStart2P-Regular.ttf", 24)

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

def initText(main_tools: Tools):

  # AI GENERATED -- Since Python has some odd way of interpeting function calls, ive had them rewritten with AI
  # basically the same function call but "python"-splitted
  main_tools.getAlgoDict()[AlgorithmKeys.BFS].setTextSrc(
      main_tools.getFontContainer().getContainer()[FontKeys.MINECRAFT_FONT_12].render(
          StringsAlgoEnums.BFS.value, True, (0, 0, 0)
      )
    )

  main_tools.getAlgoDict()[AlgorithmKeys.DFS].setTextSrc(
      main_tools.getFontContainer().getContainer()[FontKeys.MINECRAFT_FONT_12].render(
          StringsAlgoEnums.DFS.value, True, (0, 0, 0)
      )
  )

  main_tools.getAlgoDict()[AlgorithmKeys.DJIKSTRA].setTextSrc(
      main_tools.getFontContainer().getContainer()[FontKeys.MINECRAFT_FONT_12].render(
          StringsAlgoEnums.DJIKSTRA.value, True, (0, 0, 0)
      )
  )

  main_tools.getAlgoDict()[AlgorithmKeys.A_STAR].setTextSrc(
      main_tools.getFontContainer().getContainer()[FontKeys.MINECRAFT_FONT_12].render(
          StringsAlgoEnums.A_STAR.value, True, (0, 0, 0)
      )
  )

  bfs_text_src = main_tools.getAlgoDict()[AlgorithmKeys.BFS].getTextSrc()
  dfs_text_src = main_tools.getAlgoDict()[AlgorithmKeys.DFS].getTextSrc()
  djikstra_text_src = main_tools.getAlgoDict()[AlgorithmKeys.DJIKSTRA].getTextSrc()
  a_star_text_src = main_tools.getAlgoDict()[AlgorithmKeys.A_STAR].getTextSrc()


  bfs_text_rect = bfs_text_src.get_rect()
  dfs_text_rect = dfs_text_src.get_rect()
  djikstra_text_rect = djikstra_text_src.get_rect()
  a_star_text_rect = a_star_text_src.get_rect()



  bfs_text_rect.x = EVERY_BOX_X + (EVERY_BOX_WIDTH - bfs_text_rect.width) // 2
  dfs_text_rect.x = EVERY_BOX_X + (EVERY_BOX_WIDTH - dfs_text_rect.width) // 2
  djikstra_text_rect.x = EVERY_BOX_X + ( EVERY_BOX_WIDTH - djikstra_text_rect.width) // 2
  a_star_text_rect.x = EVERY_BOX_X + (EVERY_BOX_WIDTH - djikstra_text_rect.width) // 2


  bfs_text_rect.y = BFS_Y + (EVERY_BOX_HEIGHT - bfs_text_rect.height) // 2
  dfs_text_rect.y = DFS_Y + (EVERY_BOX_HEIGHT - dfs_text_rect.height) // 2
  djikstra_text_rect.y = DJIKSTRA_Y + (EVERY_BOX_HEIGHT - djikstra_text_rect.height) // 2
  a_star_text_rect.y = A_STAR_Y + (EVERY_BOX_HEIGHT - a_star_text_rect.height) // 2


  main_tools.getAlgoDict()[AlgorithmKeys.BFS].setTextRect(bfs_text_rect)
  main_tools.getAlgoDict()[AlgorithmKeys.DFS].setTextRect(dfs_text_rect)
  main_tools.getAlgoDict()[AlgorithmKeys.DJIKSTRA].setTextRect(djikstra_text_rect)
  main_tools.getAlgoDict()[AlgorithmKeys.A_STAR].setTextRect(a_star_text_rect)


  

  


  








