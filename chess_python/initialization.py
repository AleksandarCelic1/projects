from .classes.bishop import Bishop
from .classes.king import King
from .classes.queen import Queen
from .classes.rook import Rook
from .classes.pawn import Pawn
from .classes.knight import Knight
from .classes.board import Board
from .classes.tile import Tile
from .classes.piece import Piece
from .classes.constants import PieceType, ColorsPieces, ColorsTile, PlayerID, MAP_WIDTH, MAP_HEIGHT, HashKeyForPictures
# check for circual imports

from typing import Deque
from collections import deque

import pygame

hash_map_for_pictures : dict[HashKeyForPictures, pygame.Surface] = {}

def initializingAllPieces() -> Deque[Piece]:
  all_pieces : Deque[Piece] = deque() # all pieces will be here << !


  #Black 
  black_rook_one   = Rook(PieceType.ROOK,   ColorsPieces.BLACK, 0, 0, PlayerID.PLAYER_TWO_BLACK)
  black_knight_one = Knight(PieceType.KNIGHT, ColorsPieces.BLACK, 1, 0, PlayerID.PLAYER_TWO_BLACK)
  black_bishop_one = Bishop(PieceType.BISHOP, ColorsPieces.BLACK, 2, 0, PlayerID.PLAYER_TWO_BLACK)
  black_queen      = Queen(PieceType.QUEEN, ColorsPieces.BLACK, 3, 0, PlayerID.PLAYER_TWO_BLACK)
  black_king       = King(PieceType.KING,   ColorsPieces.BLACK, 4, 0, PlayerID.PLAYER_TWO_BLACK)
  black_bishop_two = Bishop(PieceType.BISHOP, ColorsPieces.BLACK, 5, 0, PlayerID.PLAYER_TWO_BLACK)
  black_knight_two = Knight(PieceType.KNIGHT, ColorsPieces.BLACK, 6, 0, PlayerID.PLAYER_TWO_BLACK)
  black_rook_two   = Rook(PieceType.ROOK,   ColorsPieces.BLACK, 7, 0, PlayerID.PLAYER_TWO_BLACK)

  black_pawn_one   = Pawn(PieceType.PAWN, ColorsPieces.BLACK, 0, 1, PlayerID.PLAYER_TWO_BLACK)
  black_pawn_two   = Pawn(PieceType.PAWN, ColorsPieces.BLACK, 1, 1, PlayerID.PLAYER_TWO_BLACK)
  black_pawn_three = Pawn(PieceType.PAWN, ColorsPieces.BLACK, 2, 1, PlayerID.PLAYER_TWO_BLACK)
  black_pawn_four  = Pawn(PieceType.PAWN, ColorsPieces.BLACK, 3, 1, PlayerID.PLAYER_TWO_BLACK)
  black_pawn_five  = Pawn(PieceType.PAWN, ColorsPieces.BLACK, 4, 1, PlayerID.PLAYER_TWO_BLACK)
  black_pawn_six   = Pawn(PieceType.PAWN, ColorsPieces.BLACK, 5, 1, PlayerID.PLAYER_TWO_BLACK)
  black_pawn_seven = Pawn(PieceType.PAWN, ColorsPieces.BLACK, 6, 1, PlayerID.PLAYER_TWO_BLACK)
  black_pawn_eight = Pawn(PieceType.PAWN, ColorsPieces.BLACK, 7, 1, PlayerID.PLAYER_TWO_BLACK)

  # White
  white_rook_one   = Rook(PieceType.ROOK,   ColorsPieces.WHITE, 0, 6, PlayerID.PLAYER_ONE_WHITE)
  white_knight_one = Knight(PieceType.KNIGHT, ColorsPieces.WHITE, 1, 6, PlayerID.PLAYER_ONE_WHITE)
  white_bishop_one = Bishop(PieceType.BISHOP, ColorsPieces.WHITE, 2, 6, PlayerID.PLAYER_ONE_WHITE)
  white_queen      = Queen(PieceType.QUEEN, ColorsPieces.WHITE, 3, 6, PlayerID.PLAYER_ONE_WHITE)
  white_king       = King(PieceType.KING,   ColorsPieces.WHITE, 4, 6, PlayerID.PLAYER_ONE_WHITE)
  white_bishop_two = Bishop(PieceType.BISHOP, ColorsPieces.WHITE, 5, 6, PlayerID.PLAYER_ONE_WHITE)
  white_knight_two = Knight(PieceType.KNIGHT, ColorsPieces.WHITE, 6, 6, PlayerID.PLAYER_ONE_WHITE)
  white_rook_two   = Rook(PieceType.ROOK,   ColorsPieces.WHITE, 7, 6, PlayerID.PLAYER_ONE_WHITE)

  white_pawn_one   = Pawn(PieceType.PAWN, ColorsPieces.WHITE, 0, 7, PlayerID.PLAYER_ONE_WHITE)
  white_pawn_two   = Pawn(PieceType.PAWN, ColorsPieces.WHITE, 1, 7, PlayerID.PLAYER_ONE_WHITE)
  white_pawn_three = Pawn(PieceType.PAWN, ColorsPieces.WHITE, 2, 7, PlayerID.PLAYER_ONE_WHITE)
  white_pawn_four  = Pawn(PieceType.PAWN, ColorsPieces.WHITE, 3, 7, PlayerID.PLAYER_ONE_WHITE)
  white_pawn_five  = Pawn(PieceType.PAWN, ColorsPieces.WHITE, 4, 7, PlayerID.PLAYER_ONE_WHITE)
  white_pawn_six   = Pawn(PieceType.PAWN, ColorsPieces.WHITE, 5, 7, PlayerID.PLAYER_ONE_WHITE)
  white_pawn_seven = Pawn(PieceType.PAWN, ColorsPieces.WHITE, 6, 7, PlayerID.PLAYER_ONE_WHITE)
  white_pawn_eight = Pawn(PieceType.PAWN, ColorsPieces.WHITE, 7, 7, PlayerID.PLAYER_ONE_WHITE)

  all_pieces.append(black_rook_one)
  all_pieces.append(black_knight_one)
  all_pieces.append(black_bishop_one)
  all_pieces.append(black_queen)
  all_pieces.append(black_king)
  all_pieces.append(black_bishop_two)
  all_pieces.append(black_knight_two)
  all_pieces.append(black_rook_two)

  all_pieces.append(black_pawn_one)
  all_pieces.append(black_pawn_two)
  all_pieces.append(black_pawn_three)
  all_pieces.append(black_pawn_four)
  all_pieces.append(black_pawn_five)
  all_pieces.append(black_pawn_six)
  all_pieces.append(black_pawn_seven)
  all_pieces.append(black_pawn_eight)

  all_pieces.append(white_rook_one)
  all_pieces.append(white_knight_one)
  all_pieces.append(white_bishop_one)
  all_pieces.append(white_queen)
  all_pieces.append(white_king)
  all_pieces.append(white_bishop_two)
  all_pieces.append(white_knight_two)
  all_pieces.append(white_rook_two)

  all_pieces.append(white_pawn_one)
  all_pieces.append(white_pawn_two)
  all_pieces.append(white_pawn_three)
  all_pieces.append(white_pawn_four)
  all_pieces.append(white_pawn_five)
  all_pieces.append(white_pawn_six)
  all_pieces.append(white_pawn_seven)
  all_pieces.append(white_pawn_eight)


  return all_pieces

def initializingBoard(all_pieces_in_dq : Deque[Piece], width_board: int, height_board: int):
  main_logic_board = Board(all_pieces_in_dq, MAP_WIDTH, MAP_HEIGHT)

  return main_logic_board

def initializingWindowAndRenderer():
  pass


def initAllImages():
  
  black_bishop = pygame.image.load("classes/photos_/BlackBishop.png").convert_alpha()
  black_horse  = pygame.image.load("classes/photos_/BlackHorse.png").convert_alpha()
  black_king   = pygame.image.load("classes/photos_/BlackKing.png").convert_alpha()
  black_pawn   = pygame.image.load("classes/photos_/BlackPawn.png").convert_alpha()
  black_queen  = pygame.image.load("classes/photos_/BlackQueen.png").convert_alpha()
  black_rook   = pygame.image.load("classes/photos_/BlackRook.png").convert_alpha()

  board_img    = pygame.image.load("classes/photos_/board.png").convert_alpha()

  white_bishop = pygame.image.load("classes/photos_/WhiteBishop.png").convert_alpha()
  white_horse  = pygame.image.load("classes/photos_/WhiteHorse.png").convert_alpha()
  white_king   = pygame.image.load("classes/photos_/WhiteKing.png").convert_alpha()
  white_pawn   = pygame.image.load("classes/photos_/WhitePawn.png").convert_alpha()
  white_queen  = pygame.image.load("classes/photos_/WhiteQueen.png").convert_alpha()
  white_rook   = pygame.image.load("classes/photos_/WhiteRook.png").convert_alpha()

  hash_map_for_pictures: dict[HashKeyForPictures, pygame.Surface] = {}

  hash_map_for_pictures[HashKeyForPictures.BLACK_PAWN] = black_pawn
  hash_map_for_pictures[HashKeyForPictures.BLACK_KING] = black_king
  hash_map_for_pictures[HashKeyForPictures.BLACK_QUEEN] = black_queen
  hash_map_for_pictures[HashKeyForPictures.BLACK_BISHOP] = black_bishop
  hash_map_for_pictures[HashKeyForPictures.BLACK_KNIGHT] = black_horse 
  hash_map_for_pictures[HashKeyForPictures.BLACK_ROOK] = black_rook

  hash_map_for_pictures[HashKeyForPictures.WHITE_PAWN] = white_pawn
  hash_map_for_pictures[HashKeyForPictures.WHITE_KING] = white_king
  hash_map_for_pictures[HashKeyForPictures.WHITE_QUEEN] = white_queen
  hash_map_for_pictures[HashKeyForPictures.WHITE_BISHOP] = white_bishop
  hash_map_for_pictures[HashKeyForPictures.WHITE_KNIGHT] = white_horse  
  hash_map_for_pictures[HashKeyForPictures.WHITE_ROOK] = white_rook








