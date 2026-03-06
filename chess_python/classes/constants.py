# Constants used for the project << !
from enum import Enum
from typing import Tuple

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

class PromotionSelection(Enum):
  QUEEN = 0
  ROOK = 1
  KNIGHT = 2
  BISHOP = 3 

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
  PROMOTION_BLACK = 13
  PROMOTION_WHITE = 14

class DiagonalDirection(Enum):
  TOP_LEFT = 0
  TOP_RIGHT = 1
  DOWN_LEFT = 2
  DOWN_RIGHT = 3

class RenderingTextEnums(Enum):
  BLACK_SCORE = "SCORE (BLACK):"
  WHITE_SCORE = "SCORE (WHITE):"
  GAME_STATE_TEXT = "GAMESTATE:"
  GAME_STATE_PLAYING = "PLAYING"
  GAME_STATE_CHECK = "CHECK"
  GAME_STATE_FINISH = "FINISH"
  PLAYER_PLAYING_TEXT = "PLAYER PLAYING:"
  WHITE_TEXT = "WHITE"
  BLACK_TEXT = "BLACK"
  CHECK_MATE_WHITE = "WHITE WINS BY CHECKMATE"
  CHECK_MATE_BLACK = "BLACK WINS BY CHECKMATE "
  STALEMATE = "STALEMATE (NO ONE WINS)"



# constants used for map scanning 
MAP_WIDTH = 8
MAP_HEIGHT = 8
MAP_UPPER_BOUND = 7
MAP_LOWER_BOUND = 0

SCALING_FACTOR_TWO = 2
SCALING_FACTOR_THREE = 3
SCALING_FACTOR_FOUR = 4
SCALING_FACTOR_FIVE = 5 

#Pawn En Passant Specific

BLACK_PAWN_EN_PASSANT_Y = 4
WHITE_PAWN_EN_PASSANT_Y = 3 
X_OFFSETS_FOR_EN_PASSANT = (-1, 1)

# special case for en-passant in lerp finishing logic << !
BLACK_PAWN_INITIAL_Y = 1
WHITE_PAWN_INITIAL_Y = 6

#Check
HORIZONTAL_STRING = 'HORIZONTAL'
VERTICAL_STRING = 'VERTICAL'

#Checkmate global
CURRENT_ATTACKER = []

#King XY

X_INDEX_OF_BOTH_KINGS_INITIALLY = 4
Y_INDEX_OF_WHITE = 7
Y_INDEX_OF_BLACK = 0



# SCREEN
SCREEN_WIDTH = 900
SCREEN_HEIGHT = 900

BOARD_WIDTH_AND_HEIGHT = 142 * SCALING_FACTOR_FOUR # 568
TILE_WIDTH_AND_HEIGHT = 16 * SCALING_FACTOR_FOUR
EVERY_PIECE_WIDTH_AND_HEIGHT = 16 * SCALING_FACTOR_FOUR
EVERY_PIECE_W_H_FOR_GRAVEYARD = 16 * SCALING_FACTOR_TWO


#Now our board is centered in the 
BOARD_OFFSET_X_AND_Y = 7 * SCALING_FACTOR_FOUR
BOARD_INNER_WIDTH_AND_HEIGHT = TILE_WIDTH_AND_HEIGHT * 8

BOARD_X = (SCREEN_WIDTH // 2) - (BOARD_WIDTH_AND_HEIGHT // 2)
BOARD_Y = (SCREEN_HEIGHT // 2) - (BOARD_WIDTH_AND_HEIGHT // 2) 

# Castle
QUEEN_SIDE_ROOK_X = 0
KING_SIDE_ROOK_X = 7

ROOK_OFFSET_AFTER_KING_CASTLE = -2
ROOK_OFFSET_AFTER_QUEEN_CASTLE = 3

#Promotion Pawns Y's
WHITE_PROMOTION_Y = 0
BLACK_PROMOTION_Y = 7


PROMOTION_PICTURES_WIDTH = 72 * SCALING_FACTOR_FIVE
PROMOTION_PICTURES_HEIGHT = 30 * SCALING_FACTOR_FIVE 
EACH_BOX_IN_PROMOTION_W = 18 * SCALING_FACTOR_FIVE
EACH_BOX_IN_PROMOTION_H = 30 * SCALING_FACTOR_FIVE
# the strech is a bit ugly but im not trying to make it look nice im trying to make function chess game thast not in CLI

PROMOTION_PICTURES_X = (SCREEN_WIDTH // 2) - (PROMOTION_PICTURES_WIDTH // 2)
PROMOTION_PICTURES_Y = (SCREEN_WIDTH // 2) - (PROMOTION_PICTURES_HEIGHT // 2)


#FPS
ONE_SECOND = 1000
FPS = 60
FRAME_DELAY = ONE_SECOND // FPS # // means FLOOR division << ! e.g. if result is 4,3 it will be 4

#LIMITS LERP
NEAR_LIMIT = 20
ARRIVED_EXACT_LIMIT = 0.5


#GLOBAL HASH TABLES
hash_map_for_pictures : dict[HashKeyForPictures, pygame.Surface] = {}
hash_map_for_rgba_tiles : dict[ColorsTile, Tuple[int, int, int, int]] = {} 
hash_map_for_graveyard_pictures : dict[HashKeyForPictures, pygame.Surface] = {}
hash_map_for_scores_and_text : dict[RenderingTextEnums, Tuple[pygame.Surface, pygame.Rect]] = {}

#SCORE STUFF
WHITE_SCORE_STRING = 'SCORE (WHITE):'
BLACK_SCORE_STRING = 'SCORE (BLACK):'

#RENDERING OFFSET FOR GAMESTATE AND PLAYERPLAYING
OFFSET_FOR_TEXT = 10 # used for gamestate rendering and playerplaying and so on

# Global BOOL

KING_CALLING = False














