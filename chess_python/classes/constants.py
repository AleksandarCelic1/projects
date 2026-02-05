# Constants used for the project << !
from enum import Enum

class PieceType(Enum):
  PAWN = 1
  KNIGHT = 2
  QUEEN = 3
  KING = 4
  BISHOP = 5
  ROOK = 6

values_for_pieces = {
  PieceType.PAWN : 1,
  PieceType.BISHOP : 3,
  PieceType.KNIGHT : 3,
  PieceType.QUEEN : 9,
  PieceType.KING : 0,
  PieceType.ROOK : 5
}

class ColorsTile(Enum):
  GREEN = 1,
  RED = 2,
  GREY = 3
  BLACK = 4
  WHITE = 5

class ColorsPieces(Enum):
  WHITE = 1
  BLACK = 2





