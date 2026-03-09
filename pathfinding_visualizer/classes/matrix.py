from .tile import Tile
from ..constants import MATRIX_WIDTH, MATRIX_HEIGHT, TileColors

from typing import List


class Matrix():
  def __init__(self):
    
    self.matrix_: List[List[Tile]] = None
    self.initMatrix(self)

    
  def initMatrix(self):

    index = 0
    inner = 0

    for index in range(MATRIX_WIDTH): # y
      for inner in range(MATRIX_WIDTH): # x
        self.matrix_[index][inner] = Tile(TileColors.WHITE, inner, index)

  def getMatrix(self):
    return self.matrix_