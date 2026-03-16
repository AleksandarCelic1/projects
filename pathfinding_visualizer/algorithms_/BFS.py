import pygame

from ..constants import MATRIX_WIDTH, MATRIX_HEIGHT
from ..classes.matrix import Matrix
from ..classes.tile import Tile
from .algorithm import Algorithm


class BfsAlgorithm(Algorithm):
  def __init__(self):
    super().__init__()

  def runAlgorithm(self, grid: Matrix, source_tile: Tile, target_tile: Tile):
    pass