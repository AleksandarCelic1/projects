from .piece import Piece
from .constants import PieceType, ColorsPieces, PlayerID
from typing import TYPE_CHECKING

from .moveFunctions import diagonalMoves

if(TYPE_CHECKING):
  from .board import Board

class Bishop(Piece):
  def __init__(self, piece_type : PieceType, color : ColorsPieces, x : int, y : int, player_id : PlayerID):
    super().__init__(piece_type, color, x, y, player_id)
    
  def getMoves(self, logic_map: "Board", x: int, y: int):
    placeholder = diagonalMoves(logic_map, x, y) # check if this works in python


    return placeholder

  