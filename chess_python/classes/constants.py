# Constants used for the project << !
from enum import Enum
from typing import List, Tuple

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

class PlayerID(Enum):
  PLAYER_ONE_WHITE = 1
  PLAYER_TWO_BLACK = 2

class HashKeyForPictures(Enum):
  BLACK_PAWN = 0
  BLACK_KING = 1
  BLACK_QUEEN = 2
  BLACK_BISHOP = 3
  BLACK_KNIGHT = 4
  BLACK_ROOK = 5
  WHITE_PAWN = 6
  WHITE_KING = 7
  WHITE_QUEEN = 8
  WHITE_BISHOP = 9
  WHITE_KNIGHT = 10
  WHITE_ROOK = 11




MAP_WIDTH = 8
MAP_HEIGHT = 8

MAP_UPPER_BOUND = 7
MAP_LOWER_BOUND = 0 # constants used for map scanning 

SCALING_FACTOR_TWO = 2
SCALING_FACTOR_THREE = 3
SCALING_FACTOR_FOUR = 4

TILE_WIDTH_AND_HEIGHT = 16
EVERY_PIECE_WIDTH_AND_HEIGHT = 16







