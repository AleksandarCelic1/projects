import pygame


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
from collections import deque


class AStarAlgorithm(Algorithm):
  def __init__(self):
    super().__init__()

  def runAlgorithm(self, grid: Matrix, source_tile: Tile, target_tile: Tile, renderer: pygame.Surface):
    
    not_visited: List[Tile] = [source_tile]
    visited: set = set()

    source_tile.setHcost(self.manhattanDistance(source_tile, target_tile))
    source_tile.setGcost(0)
    source_tile.setFcost(source_tile.getGcost() + source_tile.getHcost())


    while len(not_visited) > 0:
      
      current_tile: Tile = min(not_visited, key=lambda node: node.f_cost_) # Look more into this << !
      current_coords: Tuple[int, int] = (current_tile.getXCoord(), current_tile.getYCoord())

      if(current_tile == target_tile):
        break
    
      not_visited.remove(current_tile)
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

        neighbour_tile = grid.getMatrix()[neighbours[index][1]][neighbours[index][0]]

        if(neighbour_tile.getColor() == TileColors.BLACK
        or neighbour_tile.getColor() == TileColors.GREEN
        or neighbour_tile.getColor() == TileColors.LIGHT_GREY):
          continue

        placeholder_g: int = neighbour_tile.getGcost() + 1 # since the graph is not weighted we add one length << !

        if(neighbour_tile not in not_visited or placeholder_g < neighbour_tile.getGcost()):
          neighbour_tile.setParent(current_tile)
          neighbour_tile.setGcost(placeholder_g)
          neighbour_tile.setHcost(self.manhattanDistance(neighbour_tile, target_tile))
          neighbour_tile.setFcost(neighbour_tile.getHcost() + neighbour_tile.getGcost())


          if (neighbour_tile not in not_visited):
            not_visited.append(neighbour_tile)
        
      grid.renderTiles(renderer)
      pygame.display.flip()    


    if(current_tile != target_tile):
      return False
    
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



