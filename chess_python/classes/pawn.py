from typing import TYPE_CHECKING
from .piece import Piece
from .constants import PieceType, ColorsPieces, PlayerID

if TYPE_CHECKING:
  from .board import Board


class Pawn(Piece):
  def __init__(self, piece_type : PieceType, color : ColorsPieces, x : int, y : int, player_id : PlayerID):
    super().__init__(piece_type, color, x, y, player_id)
    self.did_i_move_already = False # USED FOR GET MOVES, as it will be used to check if
    # one can jump for 2 fields << !
    # Super() calls the base class in our case Piece CTOR (constructor)


  def getMoves(self, logic_map: "Board", x: int, y: int):
    return super().getMoves(logic_map, x, y)