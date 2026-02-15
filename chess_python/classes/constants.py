# Constants used for the project << !
from enum import Enum
from typing import List, Tuple

import pygame

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
  BOARD = 12




MAP_WIDTH = 8
MAP_HEIGHT = 8
MAP_UPPER_BOUND = 7
MAP_LOWER_BOUND = 0 # constants used for map scanning 

SCALING_FACTOR_TWO = 2
SCALING_FACTOR_THREE = 3
SCALING_FACTOR_FOUR = 4



# SCREEN
SCREEN_WIDTH = 900
SCREEN_HEIGHT = 900

BOARD_WIDTH_AND_HEIGHT = 142 * SCALING_FACTOR_FOUR # 568
TILE_WIDTH_AND_HEIGHT = 16 * SCALING_FACTOR_FOUR
EVERY_PIECE_WIDTH_AND_HEIGHT = 16 * SCALING_FACTOR_FOUR


#Now our board is centered in the 
BOARD_OFFSET_X_AND_Y = 7 * SCALING_FACTOR_FOUR
BOARD_INNER_WIDTH_AND_HEIGHT = TILE_WIDTH_AND_HEIGHT * 8

BOARD_X = (SCREEN_WIDTH // 2) - (BOARD_WIDTH_AND_HEIGHT // 2)
BOARD_Y = (SCREEN_HEIGHT // 2) - (BOARD_WIDTH_AND_HEIGHT // 2) 




#FPS
FPS = 60
FRAME_DELAY = 1000 // FPS # // means FLOOR division << ! e.g. if result is 4,3 it will be 4

#LOGIC DISPATCHER
IS_A_PIECE_SELECTED = False
MOVE_TAKEN = False
CURRENT_TILE_TO_INSPECT = None

#GLOBAL HASH TABLES
hash_map_for_pictures : dict[HashKeyForPictures, pygame.Surface] = {}
hash_map_for_rgba_tiles : dict[ColorsTile, Tuple[int, int, int, int]] = {} 











