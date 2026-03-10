from .tile import Tile
from ..constants import MATRIX_WIDTH, MATRIX_HEIGHT, TileColors, MATRIX_X_POSITION, MATRIX_Y_POSITION, TILE_WIDTH_AND_HEIGHT

from typing import List


class Matrix():
  def __init__(self):
    
    self.matrix_: List[List[Tile]] = None
    self.initMatrix(self)

    
  def initMatrix(self):

    for index in range(MATRIX_HEIGHT): # y
      for inner in range(MATRIX_WIDTH): # x
        self.matrix_[index][inner] = Tile(TileColors.WHITE, inner, index)

    self.initTilesAxis(self)

  def getMatrix(self):
    return self.matrix_
  
  def clearBoard(self):
    # essentially this means putting everything back to white << !

    for index in range(MATRIX_HEIGHT):
      for inner in range(MATRIX_WIDTH):
        self.matrix_[index][inner].setKeyAndColor(TileColors.WHITE)

  def initTilesAxis(self):

    y_axis = MATRIX_Y_POSITION
    x_axis = MATRIX_X_POSITION

    for index in range(MATRIX_HEIGHT):

      x_axis = MATRIX_X_POSITION
      for inner in range(MATRIX_WIDTH):

        self.matrix_[index][inner].setXAxis(x_axis)
        self.matrix_[index][inner].setYAxis(y_axis)
        x_axis += TILE_WIDTH_AND_HEIGHT

      y_axis += TILE_WIDTH_AND_HEIGHT








