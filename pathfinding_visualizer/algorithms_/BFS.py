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

    path: dict[Tuple[int,int], Tuple[int, int]] = {}
    path[source_tile_coords] = source_tile_coords
    stop = False
    

    queue: deque[Tuple[int, int]] = deque()
    queue.append(source_tile_coords)

    while ( queue ):

      if(stop):
        break

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
          stop = True
          path[neighbours[index]] = current_coords
          break

        if(current_tile.getColor() == TileColors.BLACK
        or current_tile.getColor() == TileColors.GREEN
        or current_tile.getColor() == TileColors.LIGHT_GREY):
          continue


        current_tile.setKeyAndColor(TileColors.LIGHT_GREY)
        queue.append(neighbours[index])
        path[neighbours[index]] = current_coords

      grid.renderTiles(renderer)
      pygame.display.flip()

      
    reconstructed_path: deque[Tuple[int ,int]] = deque()
    iterator_coords: Tuple[int, int] = target_tile_coords

    while iterator_coords is not source_tile_coords:

      iterator_tile: Tile = grid.getMatrix()[iterator_coords[1]][iterator_coords[0]]

      if(iterator_tile != target_tile):
        iterator_tile.setKeyAndColor(TileColors.LIGHT_GREEN)

      reconstructed_path.appendleft(iterator_tile)
      iterator_coords = path[iterator_coords[0], iterator_coords[1]]
      grid.renderTiles(renderer)
      pygame.display.flip()


    return True  
