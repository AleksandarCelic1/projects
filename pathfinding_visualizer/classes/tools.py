import pygame

from .matrix import Matrix
from .tile import Tile
from .mouse import Mouse
from .font import FontContainer
from .rendererFunctions import RenderingFunctionsContainer
from ..constants import AlgorithmKeys, GameState


from ..algorithms_.algorithm import Algorithm






class Tools:
  def __init__(self, matrix: Matrix, renderer: pygame.Surface, mouse: Mouse, 
  font_container: FontContainer, dict_algos: dict[AlgorithmKeys, Algorithm], render_func_object : RenderingFunctionsContainer):
  
    # The whole grid 
    self.matrix_object_: Matrix = matrix
    self.renderer_: pygame.Surface = renderer
    self.mouse_object_: Mouse = mouse
    self.font_container_object: FontContainer = font_container
    self.dict_algorithms_: dict[AlgorithmKeys, Algorithm] = dict_algos
    self.render_func_object_: RenderingFunctionsContainer = render_func_object
  

    # Not rendering anything at the start << in the means of pathfinding algos
    self.game_state_: GameState = GameState.AVAILABLE




    # Dispatcher Tiles
    self.source_tile_: Tile = None
    self.target_tile_: Tile = None

  # Getters
  def getMatrixObject(self):
    return self.matrix_object_
  
  def getRenderer(self):
    return self.renderer_
  
  def getMouseObject(self):
    return self.mouse_object_
  
  def getFontContainer(self):
    return self.font_container_object
  
  def getGameState(self):
    return self.game_state_
  
  def getAlgoDict(self):
    return self.dict_algorithms_
  
  def getRendererFunctionContainer(self):
    return self.render_func_object_
  
  def getSourceTile(self):
    return self.source_tile_
  
  def getTargetTile(self):
    return self.target_tile_
  

  

  #Setters
  def setGameState(self, new_game_state: GameState):
    self.game_state_ = new_game_state

  def setSourceTile(self, new_source_tile: Tile):
    self.source_tile_ = new_source_tile

  def setTargetTile(self, new_target_tile: Tile):
    self.target_tile_ = new_target_tile
  
  
  
  