import pygame

from ..constants import (
  MATRIX_WIDTH, 
  MATRIX_HEIGHT,
  TileColors
)

DJIKSTRA_INF = 999

from ..classes.matrix import Matrix
from ..classes.tile import Tile
from .algorithm import Algorithm

from typing import Tuple, List
from collections import deque
from ..gameFunctions import isInsideBounds


class DjikstraAlgorithm(Algorithm):
  def __init__(self):
    super().__init__()

  def runAlgorithm(self, grid: Matrix, source_tile: Tile, target_tile: Tile, renderer: pygame.Surface):
    
    min_prio_queue: List[Tile] = [source_tile]
    visited: set = set()

    for index in range(MATRIX_HEIGHT):
      for inner in range(MATRIX_WIDTH):
        initialization: Tile = grid.getMatrix()[index][inner]
        initialization.setGcost(DJIKSTRA_INF)


    source_tile.setGcost(0)
    # Djikstra uses no H cost << ! no heuristic taken into account


    while len(min_prio_queue) > 0:
      current_tile: Tile = min(min_prio_queue, key=lambda node: node.g_cost_) 
      current_coords: Tuple[int, int] = (current_tile.getXCoord(), current_tile.getYCoord())

      if(current_tile == target_tile):
        break
    
      min_prio_queue.remove(current_tile)
      visited.add(current_tile)
      if(current_tile.getColor() != TileColors.GREEN):
        current_tile.setKeyAndColor(TileColors.LIGHT_GREY)

      neighbours : List[Tuple[int, int]] = [None] * 4

      neighbours[0] = (current_coords[0] + 1, current_coords[1])
      neighbours[1] = (current_coords[0] - 1, current_coords[1])
      neighbours[2] = (current_coords[0], current_coords[1] + 1)
      neighbours[3] = (current_coords[0], current_coords[1] - 1)


      for index in range(len(neighbours)):

        if(not isInsideBounds(neighbours[index][0], neighbours[index][1])):
          continue

        neighbour_tile: Tile = grid.getMatrix()[neighbours[index][1]][neighbours[index][0]]

        if(neighbour_tile.getColor() == TileColors.BLACK
        or neighbour_tile.getColor() == TileColors.GREEN
        or neighbour_tile.getColor() == TileColors.LIGHT_GREY):
          continue

        placeholder_g = current_tile.getGcost() + 1

        if(placeholder_g < neighbour_tile.getGcost()):
          neighbour_tile.setGcost(placeholder_g)
          neighbour_tile.setParent(current_tile)
          min_prio_queue.append(neighbour_tile)

      grid.renderTiles(renderer)
      pygame.display.flip()    
      

    if(target_tile.getGcost() == DJIKSTRA_INF):
      # no path found
      return False
      
    
    # Reconstruction of path can be done later << !
    reconstructed_path: deque[Tile] = deque()
    iterator_tile: Tile = target_tile

    while(iterator_tile is not source_tile):
      if(iterator_tile != target_tile):
        iterator_tile.setKeyAndColor(TileColors.LIGHT_GREEN)

      reconstructed_path.appendleft(iterator_tile)
      iterator_tile = iterator_tile.getParent()
      grid.renderTiles(renderer)
      pygame.display.flip()    

      

    
    return True















