import pygame

from .constants import (
  SCREEN_WIDTH,
  SCREEN_HEIGHT, 
  SCALING_FACTOR_TWO,
  MATRIX_X_POSITION,
  MATRIX_Y_POSITION,
  PADDING_FOR_EVERY_SIDE,
  hash_map_for_tile_pictures, 
  hash_map_for_text,
  hash_map_for_errors,
  TilePicturesKeys, 
  FontKeys, 
  AlgorithmKeys, 
  StringsAlgoEnums,
  StringsRunReset,
  StringsError
)

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

from .classes.rendererFunctions import (
  EVERY_BOX_WIDTH, 
  EVERY_BOX_X, 
  EVERY_BOX_HEIGHT, 
  BFS_Y, 
  DFS_Y, 
  DJIKSTRA_Y, 
  A_STAR_Y,
  RUN_BUTTON_WIDTH,
  RUN_BUTTON_X,
  RUN_BUTTON_Y,
  RESET_BUTTON_WIDTH,
  RESET_BUTTON_X,
  RESET_BUTTON_Y
)


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
  initTextForAlgorithms(main_tools)
  initTextForRunResetButtons(main_tools)
  initTextForErrors(main_tools)
  initializeTutorial(main_tools)


  return main_tools

def initializeTutorial(main_tools: Tools):

  main_tools.setTutorialSource(pygame.image.load("pathfinding_visualizer/photos_/tutorialPathfindingVisualizer.png").convert_alpha())
  placeholder: pygame.Surface = main_tools.getTutorialSource()

  rect: pygame.rect = placeholder.get_rect()

  rect.x = EVERY_BOX_X
  rect.y = RUN_BUTTON_Y + PADDING_FOR_EVERY_SIDE + EVERY_BOX_HEIGHT

  main_tools.setTutorialRect(rect)
  


def initializeTilePictures():

  white_tile_src = pygame.image.load("pathfinding_visualizer/photos_/WhiteTile.png").convert_alpha()
  black_tile_src = pygame.image.load("pathfinding_visualizer/photos_/BlackTile.png").convert_alpha()
  green_tile_src = pygame.image.load("pathfinding_visualizer/photos_/GreenTile.png").convert_alpha()
  red_tile_src = pygame.image.load("pathfinding_visualizer/photos_/RedTile.png").convert_alpha()
  light_grey_tile_src = pygame.image.load("pathfinding_visualizer/photos_/LightGreyTile.png").convert_alpha()
  light_green_tile_src = pygame.image.load("pathfinding_visualizer/photos_/LightGreenTile.png").convert_alpha()



  white_tile_src = pygame.transform.smoothscale(white_tile_src, (white_tile_src.get_width() * SCALING_FACTOR_TWO, white_tile_src.get_height() * SCALING_FACTOR_TWO))
  black_tile_src = pygame.transform.smoothscale(black_tile_src, (black_tile_src.get_width() * SCALING_FACTOR_TWO, black_tile_src.get_height() * SCALING_FACTOR_TWO))
  green_tile_src = pygame.transform.smoothscale(green_tile_src, (green_tile_src.get_width() * SCALING_FACTOR_TWO, green_tile_src.get_height() * SCALING_FACTOR_TWO))
  red_tile_src = pygame.transform.smoothscale(red_tile_src, (red_tile_src.get_width() * SCALING_FACTOR_TWO, red_tile_src.get_height() * SCALING_FACTOR_TWO))
  light_grey_tile_src = pygame.transform.smoothscale(light_grey_tile_src, (light_grey_tile_src.get_width() * SCALING_FACTOR_TWO, light_grey_tile_src.get_height() * SCALING_FACTOR_TWO))
  light_green_tile_src = pygame.transform.smoothscale(light_green_tile_src, (light_green_tile_src.get_width() * SCALING_FACTOR_TWO, light_green_tile_src.get_height() * SCALING_FACTOR_TWO))




  hash_map_for_tile_pictures[TilePicturesKeys.WHITE_TILE] = white_tile_src
  hash_map_for_tile_pictures[TilePicturesKeys.BLACK_TILE] = black_tile_src
  hash_map_for_tile_pictures[TilePicturesKeys.GREEN_TILE] = green_tile_src
  hash_map_for_tile_pictures[TilePicturesKeys.RED_TILE] = red_tile_src
  hash_map_for_tile_pictures[TilePicturesKeys.LIGHT_GREY_TILE] = light_grey_tile_src
  hash_map_for_tile_pictures[TilePicturesKeys.LIGHT_GREEN_TILE] = light_green_tile_src

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

def initTextForAlgorithms(main_tools: Tools):

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
  a_star_text_rect.x = EVERY_BOX_X + (EVERY_BOX_WIDTH - a_star_text_rect.width) // 2


  bfs_text_rect.y = BFS_Y + (EVERY_BOX_HEIGHT - bfs_text_rect.height) // 2
  dfs_text_rect.y = DFS_Y + (EVERY_BOX_HEIGHT - dfs_text_rect.height) // 2
  djikstra_text_rect.y = DJIKSTRA_Y + (EVERY_BOX_HEIGHT - djikstra_text_rect.height) // 2
  a_star_text_rect.y = A_STAR_Y + (EVERY_BOX_HEIGHT - a_star_text_rect.height) // 2


  main_tools.getAlgoDict()[AlgorithmKeys.BFS].setTextRect(bfs_text_rect)
  main_tools.getAlgoDict()[AlgorithmKeys.DFS].setTextRect(dfs_text_rect)
  main_tools.getAlgoDict()[AlgorithmKeys.DJIKSTRA].setTextRect(djikstra_text_rect)
  main_tools.getAlgoDict()[AlgorithmKeys.A_STAR].setTextRect(a_star_text_rect)

def initTextForRunResetButtons(main_tools: Tools):
  
  run_src = main_tools.getFontContainer().getContainer()[FontKeys.MINECRAFT_FONT_12].render(
    StringsRunReset.RUN.value, True, (0, 0, 0)
  )

  reset_src = main_tools.getFontContainer().getContainer()[FontKeys.MINECRAFT_FONT_12].render(
    StringsRunReset.RESET.value, True, (0, 0, 0)
  )

  run_rect: pygame.Rect = run_src.get_rect()
  reset_rect: pygame.Rect = reset_src.get_rect()


  run_rect.x = RUN_BUTTON_X + (RUN_BUTTON_WIDTH - run_rect.width) // 2
  run_rect.y = RUN_BUTTON_Y + (EVERY_BOX_HEIGHT - run_rect.height) // 2

  reset_rect.x = RESET_BUTTON_X + (RESET_BUTTON_WIDTH - reset_rect.width) // 2
  reset_rect.y = RESET_BUTTON_Y + (EVERY_BOX_HEIGHT - reset_rect.height) // 2

  hash_map_for_text[StringsRunReset.RUN] = (run_src, run_rect)
  hash_map_for_text[StringsRunReset.RESET] = (reset_src, reset_rect)
  
def initTextForErrors(main_tools: Tools): 
  error_error_src = main_tools.getFontContainer().getContainer()[FontKeys.MINECRAFT_FONT_12].render(
    StringsError.ERROR.value, True, (255, 255, 255)
  )

  error_you_are_missing_src = main_tools.getFontContainer().getContainer()[FontKeys.MINECRAFT_FONT_12].render(
      StringsError.YOU_ARE_MISSING.value, True, (255, 255, 255)
  )

  error_must_reset_src = main_tools.getFontContainer().getContainer()[FontKeys.MINECRAFT_FONT_12].render(
      StringsError.MUST_RESET.value, True, (255, 255, 255)
  )

  error_source_tile_src = main_tools.getFontContainer().getContainer()[FontKeys.MINECRAFT_FONT_12].render(
      StringsError.SOURCE_TILE.value, True, (255, 255, 255)
  )

  error_target_tile_src = main_tools.getFontContainer().getContainer()[FontKeys.MINECRAFT_FONT_12].render(
      StringsError.TARGET_TILE.value, True, (255, 255, 255)
  )

  error_chosen_algo_src = main_tools.getFontContainer().getContainer()[FontKeys.MINECRAFT_FONT_12].render(
      StringsError.CHOSEN_ALGO.value, True, (255, 255, 255)
  )


  error_error_rect = error_error_src.get_rect()
  error_you_are_missing_rect = error_you_are_missing_src.get_rect()
  error_must_reset_rect = error_must_reset_src.get_rect()
  error_source_tile_rect = error_source_tile_src.get_rect()
  error_target_tile_rect = error_target_tile_src.get_rect()
  error_chosen_algo_rect = error_chosen_algo_src.get_rect()

  EVERY_MESSAGE_Y = MATRIX_Y_POSITION - PADDING_FOR_EVERY_SIDE * 2

  error_error_rect.y = EVERY_MESSAGE_Y
  error_you_are_missing_rect.y = EVERY_MESSAGE_Y
  error_must_reset_rect.y = EVERY_MESSAGE_Y
  error_source_tile_rect.y = EVERY_MESSAGE_Y
  error_target_tile_rect.y = EVERY_MESSAGE_Y
  error_chosen_algo_rect.y = EVERY_MESSAGE_Y

  error_error_rect.x = MATRIX_X_POSITION

  error_you_are_missing_rect.x = error_error_rect.x + error_error_rect.width
  error_must_reset_rect.x = error_error_rect.x + error_error_rect.width


  hash_map_for_errors[StringsError.ERROR] = (error_error_src, error_error_rect)
  hash_map_for_errors[StringsError.YOU_ARE_MISSING] = (error_you_are_missing_src, error_you_are_missing_rect)
  hash_map_for_errors[StringsError.MUST_RESET] = (error_must_reset_src, error_must_reset_rect)
  hash_map_for_errors[StringsError.SOURCE_TILE] = (error_source_tile_src, error_source_tile_rect)
  hash_map_for_errors[StringsError.TARGET_TILE] = (error_target_tile_src, error_target_tile_rect)
  hash_map_for_errors[StringsError.CHOSEN_ALGO] = (error_chosen_algo_src, error_chosen_algo_rect)




  


  








