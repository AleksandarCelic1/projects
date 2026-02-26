from .piece import Piece
from .constants import PieceType, ColorsPieces, PlayerID, ColorsTile, HashKeyForPictures
from typing import TYPE_CHECKING, List, Tuple
from .tile import Tile

from .moveFunctions import kingViableMoves

if(TYPE_CHECKING):
  from .board import Board

class King(Piece):
  def __init__(self, piece_type : PieceType, color : ColorsPieces, x : int, y : int, player_id : PlayerID, key: HashKeyForPictures):
    super().__init__(piece_type, color, x, y, player_id, key)
    self.am_i_in_check = False
    self.total_legal_moves = 0
    
  def getMoves(self, logic_map: "Board", x: int, y: int):
    placeholder : List[Tuple[Tile, ColorsTile]] = []
    origin : Tile = logic_map.chess_board[y][x]

    
    self.total_legal_moves = kingViableMoves(logic_map, x, y, placeholder, origin)

    return placeholder