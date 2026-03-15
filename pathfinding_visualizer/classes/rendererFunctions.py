import pygame

from ..constants import PADDING_FOR_EVERY_SIDE, MATRIX_X_POSITION

EVERY_BOX_WIDTH = MATRIX_X_POSITION - (2 * PADDING_FOR_EVERY_SIDE) # Left padding Right padding 
EVERY_BOX_X = PADDING_FOR_EVERY_SIDE
EVERY_BOX_HEIGHT = 50

BFS_Y = PADDING_FOR_EVERY_SIDE
DFS_Y = BFS_Y + EVERY_BOX_HEIGHT + PADDING_FOR_EVERY_SIDE
A_STAR_Y = DFS_Y + EVERY_BOX_HEIGHT + PADDING_FOR_EVERY_SIDE
DJIKSTRA_Y = A_STAR_Y + EVERY_BOX_HEIGHT + PADDING_FOR_EVERY_SIDE





class RenderingFunctionsContainer:
  def __init__(self):
    pass

  def renderUI(self, renderer: pygame.Surface, algos: dict[a]):

    self.renderBackground()
    self.renderButtonsForAlgorithms()


  def renderButtonsForAlgorithms(self, renderer: pygame.Surface):

    pygame.draw.rect(renderer, (255, 255, 255), (EVERY_BOX_X, BFS_Y, EVERY_BOX_WIDTH, EVERY_BOX_HEIGHT), 0)
    pygame.draw.rect(renderer, (255, 255, 255), (EVERY_BOX_X, DFS_Y, EVERY_BOX_WIDTH, EVERY_BOX_HEIGHT), 0)
    pygame.draw.rect(renderer, (255, 255, 255), (EVERY_BOX_X, DJIKSTRA_Y, EVERY_BOX_WIDTH, EVERY_BOX_HEIGHT), 0)
    pygame.draw.rect(renderer, (255, 255, 255), (EVERY_BOX_X, A_STAR_Y, EVERY_BOX_WIDTH, EVERY_BOX_HEIGHT), 0)

  def renderBackground(self, renderer: pygame.Surface):
    renderer.fill((0, 0, 0)) # black

  def renderTextInBoxes(self, renderer: pygame.Surface):
    pass
    





