import pygame
import random

from ..constants import (
  MATRIX_WIDTH, 
  MATRIX_HEIGHT,
  TileColors
)

from ..classes.matrix import Matrix
from ..classes.tile import Tile
from .algorithm import Algorithm

from ..gameFunctions import isInsideBounds
from typing import List, Tuple


class DfsAlgorithm(Algorithm):
  def __init__(self):
    super().__init__()

  def runAlgorithm(self, grid: Matrix, source_tile: Tile, target_tile: Tile, renderer: pygame.Surface):

    stack: List[Tile] = [] # stack is essentialy a List in python

    stack.append((source_tile.getXCoord(), source_tile.getYCoord()))

    while len(stack) > 0:
      current_coords : Tuple[int, int] = stack.pop()

      neighbours: List[Tuple[int ,int]] = [None] * 4

      self.randomizeNeighbours(current_coords, neighbours)

      for index in range(len(neighbours)):
        
        if (not isInsideBounds(neighbours[index][0], neighbours[index][1])):
          continue

        current_tile: Tile = grid.getMatrix()[neighbours[index][1]][neighbours[index][0]]

        if(current_tile == target_tile):
          return True
        
        if(current_tile.getColor() == TileColors.BLACK
        or current_tile.getColor() == TileColors.GREEN
        or current_tile.getColor() == TileColors.LIGHT_GREY):
          continue


        current_tile.setKeyAndColor(TileColors.LIGHT_GREY)
        stack.append(neighbours[index])
      grid.renderTiles(renderer)
      pygame.display.flip()
        

    return False
  

  def randomizeNeighbours(self, current_coords: Tuple[int, int], neighbours: List[Tuple[int, int]]):
    
    choices: List[int] = [0, 1, 2, 3]

    list_of_new_neighbours: List[Tuple, Tuple] =  [ 
      (current_coords[0] + 1, current_coords[1]),
      (current_coords[0] - 1, current_coords[1]),
      (current_coords[0], current_coords[1] + 1),
      (current_coords[0], current_coords[1] - 1)
    ]

    random.shuffle(choices)

    for index, inner in enumerate(choices):
      neighbours[index] = list_of_new_neighbours[inner]

      


