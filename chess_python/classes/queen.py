from .piece import Piece
from .constants import PieceType, ColorsPieces, PlayerID, ColorsTile, HashKeyForPictures
from typing import TYPE_CHECKING, List, Tuple
from .tile import Tile

from .moveFunctions import diagonalMoves, verticalMoves, horizontalMoves

if(TYPE_CHECKING):
  from .board import Board

class Queen(Piece):
  def __init__(self, piece_type : PieceType, color : ColorsPieces, x : int, y : int, player_id : PlayerID, key: HashKeyForPictures):
    super().__init__(piece_type, color, x, y, player_id, key)
    
  def getMoves(self, logic_map: "Board", x: int, y: int):
    a = diagonalMoves(logic_map, x, y)
    b = horizontalMoves(logic_map, x, y)
    c = verticalMoves(logic_map, x, y)

    placeholder : List[Tuple[Tile, ColorsTile]] = []
    placeholder = a + b + c

    if(placeholder is not None):
      self.total_legal_moves = len(placeholder)

    return placeholder