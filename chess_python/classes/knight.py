from .piece import Piece
from .constants import PieceType, ColorsPieces, PlayerID, ColorsTile, HashKeyForPictures
from typing import TYPE_CHECKING, List, Tuple
from .tile import Tile

from .moveFunctions import knightViableMoves

if(TYPE_CHECKING):
  from .board import Board

class Knight(Piece):
  def __init__(self, piece_type : PieceType, color : ColorsPieces, x : int, y : int, player_id : PlayerID, key: HashKeyForPictures):
    super().__init__(piece_type, color, x, y, player_id, key)
    
  def getMoves(self, logic_map: "Board", x: int, y: int):
    placeholder : List[Tuple[Tile, ColorsTile]] = []
    origin : Tile = logic_map.chess_board[y][x]

    knightViableMoves(logic_map, x, y, placeholder, origin)

    return placeholder