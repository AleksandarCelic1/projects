from abc import ABC, abstractmethod

from ..classes.matrix import Matrix
from ..classes.tile import Tile

class Algorithm(ABC):
  def __init__(self):
    pass

  @abstractmethod
  def runAlgorithm(self, grid: Matrix, source_tile: Tile, target_tile: Tile):
    pass