import pygame

from ..constants import MATRIX_WIDTH, MATRIX_HEIGHT, TileColors
from ..classes.matrix import Matrix
from ..classes.tile import Tile
from .algorithm import Algorithm
from ..gameFunctions import isInsideBounds


from typing import Tuple, List
from collections import deque


class BfsAlgorithm(Algorithm):
  def __init__(self):
    super().__init__()

  def runAlgorithm(self, grid: Matrix, source_tile: Tile, target_tile: Tile, renderer: pygame.Surface):
    
    source_tile_coords: Tuple[int, int] = (source_tile.getXCoord(), source_tile.getYCoord())
    target_tile_coords: Tuple[int, int] = (target_tile.getXCoord(), target_tile.getYCoord())
    

    queue: deque[Tuple[int, int]] = deque()

    queue.append(source_tile_coords)

    while ( queue ):

      current_coords: Tuple[int, int] = queue.popleft()
      
      neighbours : List[Tuple[int, int]] = [None] * 4

      neighbours[0] = (current_coords[0] + 1, current_coords[1])
      neighbours[1] = (current_coords[0] - 1, current_coords[1])
      neighbours[2] = (current_coords[0], current_coords[1] + 1)
      neighbours[3] = (current_coords[0], current_coords[1] - 1)

      for index in range(len(neighbours)):
        
        if(not isInsideBounds(neighbours[index][0], neighbours[index][1])):
          continue

        current_tile: Tile = grid.getMatrix()[neighbours[index][1]][neighbours[index][0]]

        if(current_tile == target_tile):
          return True

        if(current_tile.getColor() == TileColors.BLACK
        or current_tile.getColor() == TileColors.GREEN
        or current_tile.getColor() == TileColors.LIGHT_GREY):
          continue


        current_tile.setKeyAndColor(TileColors.LIGHT_GREY)
        queue.append(neighbours[index])
      grid.renderTiles(renderer)
      pygame.display.flip()


      
    return False # will try makign walls and when he doesnt find it we can do some output info regarding it 












    pass