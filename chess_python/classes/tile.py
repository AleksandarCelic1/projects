from typing import Optional, TYPE_CHECKING

if TYPE_CHECKING:
  from .piece import Piece

from .constants import ColorsTile

class Tile:
  def __init__(self, color_of_tile : ColorsTile, piece : "Piece", x: int , y: int, x_axis: int, y_axis: int): # piece : Optional[piece.Piece] means i must pass something
    # piece : Optional[piece.Piece] = None, i can pass something but i dont have to << !
    self.color = color_of_tile

    #indexes
    self.x = x
    self.y = y

    #axes rendering
    self.x_axis = x_axis
    self.y_axis = y_axis
    #used for coloring the tiles << !

    self.piece = piece
    self.is_under_attack = False

  def is_occupied(self) -> bool: # -> is used to indicate what the function returns 
    return self.piece is not None
  #basically e.g. self.piece = None ... None is not None -> false otherwise true if you know what i mean << !

    