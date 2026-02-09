from .piece import Piece
from .constants import PieceType, ColorsPieces, PlayerID, ColorsTile
from typing import TYPE_CHECKING, List, Tuple
from .tile import Tile

from .moveFunctions import verticalMoves, horizontalMoves

if(TYPE_CHECKING):
  from .board import Board

class Rook(Piece):
  def __init__(self, piece_type : PieceType, color : ColorsPieces, x : int, y : int, player_id : PlayerID):
    super().__init__(piece_type, color, x, y, player_id)
    
  def getMoves(self, logic_map: "Board", x: int, y: int):
    a = horizontalMoves(logic_map, x, y)
    b = verticalMoves(logic_map, x, y)

    placeholder : List[Tuple[Tile, ColorsTile]] = []
    placeholder = a + b
    

    return placeholder