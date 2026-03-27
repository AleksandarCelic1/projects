import pygame

from ..constants import (
  PADDING_FOR_EVERY_SIDE, 
  MATRIX_X_POSITION, 
  AlgorithmKeys,
  StringsRunReset,
  StringsError,
  hash_map_for_text,
  hash_map_for_errors
)

from ..algorithms_.algorithm import Algorithm
from ..classes.tile import Tile

EVERY_BOX_WIDTH = MATRIX_X_POSITION - (2 * PADDING_FOR_EVERY_SIDE) # Left padding Right padding 
EVERY_BOX_X = PADDING_FOR_EVERY_SIDE
EVERY_BOX_HEIGHT = 50

BFS_Y = PADDING_FOR_EVERY_SIDE
DFS_Y = BFS_Y + EVERY_BOX_HEIGHT + PADDING_FOR_EVERY_SIDE
A_STAR_Y = DFS_Y + EVERY_BOX_HEIGHT + PADDING_FOR_EVERY_SIDE
DJIKSTRA_Y = A_STAR_Y + EVERY_BOX_HEIGHT + PADDING_FOR_EVERY_SIDE

RUN_BUTTON_X = EVERY_BOX_X
RUN_BUTTON_Y = DJIKSTRA_Y + EVERY_BOX_HEIGHT + PADDING_FOR_EVERY_SIDE
RUN_BUTTON_WIDTH = (EVERY_BOX_WIDTH // 2) - PADDING_FOR_EVERY_SIDE


RESET_BUTTON_X = RUN_BUTTON_X + RUN_BUTTON_WIDTH + (PADDING_FOR_EVERY_SIDE * 2)
RESET_BUTTON_Y = RUN_BUTTON_Y

RESET_BUTTON_WIDTH = RUN_BUTTON_WIDTH

WALLS_X = EVERY_BOX_X
WALLS_Y = RUN_BUTTON_Y + PADDING_FOR_EVERY_SIDE + EVERY_BOX_HEIGHT





class RenderingFunctionsContainer:
  def __init__(self):
    self.timer_: float = float(0)

    pass

  def refreshTimer(self):
    self.timer_ = float(0)

  def renderUI(self, main_tool, delta_time: float):


    renderer: pygame.Surface = main_tool.getRenderer()
    algos: dict[AlgorithmKeys, Algorithm] = main_tool.getAlgoDict()

    self.renderBackground(renderer)
    self.renderButtonsForAlgorithms(renderer)
    self.renderRunAndResetButtons(renderer)
    self.renderTextInBoxes(renderer, algos)
    self.renderTutorial(renderer, main_tool.getTutorialSource(), main_tool.getTutorialRect())

    if(main_tool.getErrorBool()):
      self.timer_ += delta_time

      if(main_tool.getWhichErrorOccured() == 0):
        self.renderErrorMustUseBrush(renderer)
      elif(main_tool.getWhichErrorOccured() == 1):
        self.renderErrorTilesAlgo(renderer, main_tool.getSourceTile(), main_tool.getTargetTile(), main_tool.getSelectedAlgorithm())

      if(self.timer_ >= 5.0):
        main_tool.setErrorBool(False)
        main_tool.setWhichErrorOccured(-1)
        self.timer_ = float(0)
      

      





  def renderButtonsForAlgorithms(self, renderer: pygame.Surface):

    pygame.draw.rect(renderer, (255, 255, 255), (EVERY_BOX_X, BFS_Y, EVERY_BOX_WIDTH, EVERY_BOX_HEIGHT), 0)
    pygame.draw.rect(renderer, (255, 255, 255), (EVERY_BOX_X, DFS_Y, EVERY_BOX_WIDTH, EVERY_BOX_HEIGHT), 0)
    pygame.draw.rect(renderer, (255, 255, 255), (EVERY_BOX_X, DJIKSTRA_Y, EVERY_BOX_WIDTH, EVERY_BOX_HEIGHT), 0)
    pygame.draw.rect(renderer, (255, 255, 255), (EVERY_BOX_X, A_STAR_Y, EVERY_BOX_WIDTH, EVERY_BOX_HEIGHT), 0)

  def renderBackground(self, renderer: pygame.Surface):
    renderer.fill((0, 0, 0)) # black

  def renderTextInBoxes(self, renderer: pygame.Surface, algos: dict[AlgorithmKeys, Algorithm]):

    for index in range(4):
      key = AlgorithmKeys(index)
      renderer.blit(algos[key].getTextSrc(), algos[key].getTextRect())

    renderer.blit(hash_map_for_text[StringsRunReset.RUN][0], hash_map_for_text[StringsRunReset.RUN][1])
    renderer.blit(hash_map_for_text[StringsRunReset.RESET][0], hash_map_for_text[StringsRunReset.RESET][1])
    renderer.blit(hash_map_for_text[StringsRunReset.WALLS][0], hash_map_for_text[StringsRunReset.WALLS][1])


    # This should be it regarding the text in boxes print << !
    
  def renderRunAndResetButtons(self, renderer: pygame.Surface):

    pygame.draw.rect(renderer, (255, 255, 255), (RUN_BUTTON_X, RUN_BUTTON_Y, RUN_BUTTON_WIDTH, EVERY_BOX_HEIGHT), 0)
    pygame.draw.rect(renderer, (255, 255, 255), (RESET_BUTTON_X, RESET_BUTTON_Y, RESET_BUTTON_WIDTH, EVERY_BOX_HEIGHT), 0)
    pygame.draw.rect(renderer, (255, 255, 255), (WALLS_X, WALLS_Y, EVERY_BOX_WIDTH, EVERY_BOX_HEIGHT), 0)
    

  def renderErrorMustUseBrush(self, renderer: pygame.Surface):
    
    renderer.blit(hash_map_for_errors[StringsError.ERROR][0], hash_map_for_errors[StringsError.ERROR][1])
    renderer.blit(hash_map_for_errors[StringsError.MUST_RESET][0], hash_map_for_errors[StringsError.MUST_RESET][1])

    
  def renderErrorTilesAlgo(self, renderer: pygame.Surface, source_tile: Tile, target_tile: Tile, algo: Algorithm):

    x: int = hash_map_for_errors[StringsError.ERROR][1].x

    renderer.blit(hash_map_for_errors[StringsError.ERROR][0], hash_map_for_errors[StringsError.ERROR][1])

    x += hash_map_for_errors[StringsError.ERROR][1].width

    renderer.blit(hash_map_for_errors[StringsError.YOU_ARE_MISSING][0], hash_map_for_errors[StringsError.YOU_ARE_MISSING][1])

    x += hash_map_for_errors[StringsError.YOU_ARE_MISSING][1].width + PADDING_FOR_EVERY_SIDE

    if(source_tile is None):
      hash_map_for_errors[StringsError.SOURCE_TILE][1].x = x
      x += hash_map_for_errors[StringsError.SOURCE_TILE][1].width + PADDING_FOR_EVERY_SIDE
      renderer.blit(hash_map_for_errors[StringsError.SOURCE_TILE][0], hash_map_for_errors[StringsError.SOURCE_TILE][1])

    if(target_tile is None):
      hash_map_for_errors[StringsError.TARGET_TILE][1].x = x
      x += hash_map_for_errors[StringsError.TARGET_TILE][1].width + PADDING_FOR_EVERY_SIDE
      renderer.blit(hash_map_for_errors[StringsError.TARGET_TILE][0], hash_map_for_errors[StringsError.TARGET_TILE][1])

    if(algo is None):
      hash_map_for_errors[StringsError.CHOSEN_ALGO][1].x = x
      x += hash_map_for_errors[StringsError.CHOSEN_ALGO][1].width + PADDING_FOR_EVERY_SIDE
      renderer.blit(hash_map_for_errors[StringsError.CHOSEN_ALGO][0], hash_map_for_errors[StringsError.CHOSEN_ALGO][1])

  def renderTutorial(self, renderer: pygame.Surface, src: pygame.Surface, rect: pygame.Rect):

    renderer.blit(src, rect)
    


