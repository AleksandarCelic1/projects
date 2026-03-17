import pygame

from .constants import (
  FRAME_DELAY,
  MATRIX_X_POSITION,
  MATRIX_Y_POSITION,
  MATIRX_WIDTH_PIXELS,
  MATRIX_HEIGHT_PIXELS,
  TILE_WIDTH_AND_HEIGHT,
  MATRIX_HEIGHT,
  MATRIX_WIDTH,
  TileColors,
  GameState
)
from .classes.tools import Tools
from .classes.tile import Tile
from .classes.matrix import Matrix

def controlFPS(frame_start: int):
  current_frame_time = pygame.time.get_ticks() - frame_start
  if(current_frame_time < FRAME_DELAY):
    pygame.time.delay(FRAME_DELAY - current_frame_time)


def dispatcher(main_tools: Tools, mouse_x: int, mouse_y: int) -> bool:
  
  if(dispatcherMatrix(main_tools, mouse_x, mouse_y)):
    return True
  
  if(dispatcherAlgorithm(main_tools, mouse_x, mouse_y)):
    return True
  
  if(dispatcherRunButton(main_tools, mouse_x, mouse_y)):
    return True
  
  return False


def dispatcherMatrix(main_tools: Tools, mouse_x: int, mouse_y: int) -> bool:
  
  if(mouse_x >= MATRIX_X_POSITION
  and mouse_x <= MATRIX_X_POSITION + MATIRX_WIDTH_PIXELS
  and mouse_y >= MATRIX_Y_POSITION
  and mouse_y <= MATRIX_Y_POSITION + MATRIX_HEIGHT_PIXELS):
    
    clicked_column = 0
    clicked_row = 0

    clicked_column = (mouse_x - MATRIX_X_POSITION) // TILE_WIDTH_AND_HEIGHT
    clicked_row = (mouse_y - MATRIX_Y_POSITION) // TILE_WIDTH_AND_HEIGHT

    print(clicked_column)
    print(clicked_row)

    if(not isInsideBounds(clicked_column, clicked_row)):
      return False
    

    clicked_tile: Tile = main_tools.getMatrixObject().getMatrix()[clicked_row][clicked_column]


    if(main_tools.getGameState() == GameState.AVAILABLE):

      clicked_tile.setKeyAndColor(TileColors.GREEN)
      main_tools.setGameState(GameState.FIRST_MOVE_MADE)
      main_tools.setSourceTile(clicked_tile)

    elif(main_tools.getGameState() == GameState.FIRST_MOVE_MADE):

      if(not clicked_tile == main_tools.getSourceTile()):
        clicked_tile.setKeyAndColor(TileColors.RED)
        main_tools.setGameState(GameState.SECOND_MOVE_MADE)
        main_tools.setTargetTile(clicked_tile)




    pass

def dispatcherAlgorithm(main_tools: Tools, mouse_x: int, mouse_y: int) -> bool:
  pass

def dispatcherRunButton(main_tools: Tools, mouse_x: int, mouse_y: int) -> bool:
  pass

def isInsideBounds(x: int, y: int):
  placeholder: bool = False

  placeholder = True if (x < MATRIX_WIDTH and x >= 0 and y < MATRIX_HEIGHT and y >= 0) else False

  return placeholder