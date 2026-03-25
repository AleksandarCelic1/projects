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
  PADDING_FOR_EVERY_SIDE,
  ONE_SECOND,
  TileColors,
  GameState,
  AlgorithmKeys
)

from .classes.rendererFunctions import (
  EVERY_BOX_HEIGHT,
  EVERY_BOX_WIDTH,
  EVERY_BOX_X,
  BFS_Y,
  DFS_Y,
  DJIKSTRA_Y,
  A_STAR_Y,
  RESET_BUTTON_WIDTH,
  RESET_BUTTON_X,
  RESET_BUTTON_Y,
  RUN_BUTTON_WIDTH,
  RUN_BUTTON_X,
  RUN_BUTTON_Y
)


from .classes.tools import Tools
from .classes.tile import Tile
from .classes.matrix import Matrix

def controlFPS(frame_start: int):
  current_frame_time = pygame.time.get_ticks() - frame_start
  if(current_frame_time < FRAME_DELAY):
    pygame.time.delay(FRAME_DELAY - current_frame_time)


def dispatcher(main_tools: Tools, mouse_x: int, mouse_y: int) -> bool:

  if(dispatcherResetButton(main_tools, mouse_x, mouse_y)):
    return True

  if(main_tools.getGameState() != GameState.MUST_USE_BRUSH):
    if(dispatcherRunButton(main_tools, mouse_x, mouse_y)):
      return True
  
  if(main_tools.getGameState() == GameState.MUST_USE_BRUSH):
    main_tools.setErrorBool(True)
    main_tools.setWhichErrorOccured(0)
    main_tools.getRendererFunctionContainer().refreshTimer()
    return True 
  
  if(main_tools.getGameState() == GameState.AVAILABLE 
  or main_tools.getGameState() == GameState.FIRST_MOVE_MADE):
    if(dispatcherMatrix(main_tools, mouse_x, mouse_y)):
      return True
    
  if(main_tools.getGameState() == GameState.AVAILABLE
  or main_tools.getGameState() == GameState.FIRST_MOVE_MADE
  or main_tools.getGameState() == GameState.SECOND_MOVE_MADE):
    if(dispatcherAlgorithm(main_tools, mouse_x, mouse_y)):
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
  
  algo_dict_ref = main_tools.getAlgoDict()

  if( mouse_x >= EVERY_BOX_X
  and mouse_x <= EVERY_BOX_X + EVERY_BOX_WIDTH):
    
    if( mouse_y >= BFS_Y
    and mouse_y <= BFS_Y + EVERY_BOX_HEIGHT):
      main_tools.setSelectedAlgorithm(algo_dict_ref[AlgorithmKeys.BFS])
      return True
    
    if( mouse_y >= DFS_Y
    and mouse_y <= DFS_Y + EVERY_BOX_HEIGHT):
      main_tools.setSelectedAlgorithm(algo_dict_ref[AlgorithmKeys.DFS])
      return True
    
    if( mouse_y >= DJIKSTRA_Y
    and mouse_y <= DJIKSTRA_Y + EVERY_BOX_HEIGHT):
      main_tools.setSelectedAlgorithm(algo_dict_ref[AlgorithmKeys.DJIKSTRA])
      return True
    
    if( mouse_y >= A_STAR_Y
    and mouse_y <= A_STAR_Y + EVERY_BOX_HEIGHT):
      main_tools.setSelectedAlgorithm(algo_dict_ref[AlgorithmKeys.A_STAR])
      return True

def dispatcherRunButton(main_tools: Tools, mouse_x: int, mouse_y: int) -> bool:
  
  if( mouse_x >= RUN_BUTTON_X
  and mouse_x <= RUN_BUTTON_X + RUN_BUTTON_WIDTH
  and mouse_y >= RUN_BUTTON_Y
  and mouse_y <= RUN_BUTTON_Y + EVERY_BOX_HEIGHT):
    
    if(main_tools.getSourceTile() == None
    or main_tools.getTargetTile() == None
    or main_tools.getSelectedAlgorithm() == None):
      main_tools.setErrorBool(True)
      main_tools.setWhichErrorOccured(1)
      main_tools.getRendererFunctionContainer().refreshTimer()
      return True

    grid_reference: Matrix = main_tools.getMatrixObject()
    src: Tile = main_tools.getSourceTile()
    target: Tile = main_tools.getTargetTile()
    renderer: pygame.Surface = main_tools.getRenderer()

    main_tools.setGameState(GameState.BUSY)
    if(main_tools.getSelectedAlgorithm().runAlgorithm(grid_reference, src, target, renderer)):
      main_tools.setGameState(GameState.MUST_USE_BRUSH)
      return True

      # make a wrapper function that constructs path after AGLO runs if he returns true construct if not dont << !

def dispatcherResetButton(main_tools: Tools, mouse_x: int, mouse_y: int) -> bool:

  if( mouse_x >= RESET_BUTTON_X
  and mouse_x <= RESET_BUTTON_WIDTH + RESET_BUTTON_X
  and mouse_y >= RESET_BUTTON_Y
  and mouse_y <= RESET_BUTTON_Y + EVERY_BOX_HEIGHT):
    
    main_tools.setSelectedAlgorithm(None)
    main_tools.setSourceTile(None)
    main_tools.setTargetTile(None)
    main_tools.getMatrixObject().clearBoard()
    main_tools.setGameState(GameState.AVAILABLE)
    return True
    
def isInsideBounds(x: int, y: int):
  placeholder: bool = False

  placeholder = True if (x < MATRIX_WIDTH and x >= 0 and y < MATRIX_HEIGHT and y >= 0) else False

  return placeholder

def calculateDeltaTime(current_frame: float, last_frame: float):
  return (current_frame - last_frame) / ONE_SECOND