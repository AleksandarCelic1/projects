from .classes.bishop import Bishop
from .classes.king import King
from .classes.queen import Queen
from .classes.rook import Rook
from .classes.pawn import Pawn
from .classes.knight import Knight
from .classes.board import Board
from .classes.tile import Tile
from .classes.piece import Piece
from .classes.constants import PieceType, ColorsPieces, ColorsTile, PlayerID, MAP_WIDTH, MAP_HEIGHT, HashKeyForPictures, SCREEN_HEIGHT, SCREEN_WIDTH, EVERY_PIECE_WIDTH_AND_HEIGHT, hash_map_for_pictures, hash_map_for_rgba_tiles, BLACK_SCORE_STRING, WHITE_SCORE_STRING
from .classes.constants import SCALING_FACTOR_FOUR, BOARD_OFFSET_X_AND_Y, BOARD_X, BOARD_Y, BOARD_WIDTH_AND_HEIGHT, MAP_HEIGHT, MAP_WIDTH, hash_map_for_graveyard_pictures, EVERY_PIECE_W_H_FOR_GRAVEYARD, hash_map_for_scores_and_text, RenderingTextEnums, OFFSET_FOR_TEXT
from .classes.constants import PROMOTION_PICTURES_WIDTH, PROMOTION_PICTURES_HEIGHT
from .classes.player import Player
from .classes.tools import Tools
# check for circual imports

from typing import Deque, Tuple, Optional
from collections import deque

import pygame




def initializingAllPieces() -> Deque[Piece]:
  all_pieces : Deque[Piece] = deque() # all pieces will be here << !


  #Black 
  black_rook_one   = Rook(PieceType.ROOK,   ColorsPieces.BLACK, 0, 0, PlayerID.PLAYER_TWO_BLACK, HashKeyForPictures.BLACK_ROOK)
  black_knight_one = Knight(PieceType.KNIGHT, ColorsPieces.BLACK, 1, 0, PlayerID.PLAYER_TWO_BLACK, HashKeyForPictures.BLACK_KNIGHT)
  black_bishop_one = Bishop(PieceType.BISHOP, ColorsPieces.BLACK, 2, 0, PlayerID.PLAYER_TWO_BLACK, HashKeyForPictures.BLACK_BISHOP)
  black_queen      = Queen(PieceType.QUEEN, ColorsPieces.BLACK, 3, 0, PlayerID.PLAYER_TWO_BLACK, HashKeyForPictures.BLACK_QUEEN)
  black_king       = King(PieceType.KING,   ColorsPieces.BLACK, 4, 0, PlayerID.PLAYER_TWO_BLACK, HashKeyForPictures.BLACK_KING)
  black_bishop_two = Bishop(PieceType.BISHOP, ColorsPieces.BLACK, 5, 0, PlayerID.PLAYER_TWO_BLACK, HashKeyForPictures.BLACK_BISHOP)
  black_knight_two = Knight(PieceType.KNIGHT, ColorsPieces.BLACK, 6, 0, PlayerID.PLAYER_TWO_BLACK, HashKeyForPictures.BLACK_KNIGHT)
  black_rook_two   = Rook(PieceType.ROOK,   ColorsPieces.BLACK, 7, 0, PlayerID.PLAYER_TWO_BLACK, HashKeyForPictures.BLACK_ROOK)

  black_pawn_one   = Pawn(PieceType.PAWN, ColorsPieces.BLACK, 0, 1, PlayerID.PLAYER_TWO_BLACK, HashKeyForPictures.BLACK_PAWN)
  black_pawn_two   = Pawn(PieceType.PAWN, ColorsPieces.BLACK, 1, 1, PlayerID.PLAYER_TWO_BLACK, HashKeyForPictures.BLACK_PAWN)
  black_pawn_three = Pawn(PieceType.PAWN, ColorsPieces.BLACK, 2, 1, PlayerID.PLAYER_TWO_BLACK, HashKeyForPictures.BLACK_PAWN)
  black_pawn_four  = Pawn(PieceType.PAWN, ColorsPieces.BLACK, 3, 1, PlayerID.PLAYER_TWO_BLACK, HashKeyForPictures.BLACK_PAWN)
  black_pawn_five  = Pawn(PieceType.PAWN, ColorsPieces.BLACK, 4, 1, PlayerID.PLAYER_TWO_BLACK, HashKeyForPictures.BLACK_PAWN)
  black_pawn_six   = Pawn(PieceType.PAWN, ColorsPieces.BLACK, 5, 1, PlayerID.PLAYER_TWO_BLACK, HashKeyForPictures.BLACK_PAWN)
  black_pawn_seven = Pawn(PieceType.PAWN, ColorsPieces.BLACK, 6, 1, PlayerID.PLAYER_TWO_BLACK, HashKeyForPictures.BLACK_PAWN)
  black_pawn_eight = Pawn(PieceType.PAWN, ColorsPieces.BLACK, 7, 1, PlayerID.PLAYER_TWO_BLACK, HashKeyForPictures.BLACK_PAWN)

  # White
  white_rook_one   = Rook(PieceType.ROOK,   ColorsPieces.WHITE, 0, 7, PlayerID.PLAYER_ONE_WHITE, HashKeyForPictures.WHITE_ROOK)
  white_knight_one = Knight(PieceType.KNIGHT, ColorsPieces.WHITE, 1, 7, PlayerID.PLAYER_ONE_WHITE, HashKeyForPictures.WHITE_KNIGHT)
  white_bishop_one = Bishop(PieceType.BISHOP, ColorsPieces.WHITE, 2, 7, PlayerID.PLAYER_ONE_WHITE, HashKeyForPictures.WHITE_BISHOP)
  white_queen      = Queen(PieceType.QUEEN, ColorsPieces.WHITE, 3, 7, PlayerID.PLAYER_ONE_WHITE, HashKeyForPictures.WHITE_QUEEN)
  white_king       = King(PieceType.KING,   ColorsPieces.WHITE, 4, 7, PlayerID.PLAYER_ONE_WHITE, HashKeyForPictures.WHITE_KING)
  white_bishop_two = Bishop(PieceType.BISHOP, ColorsPieces.WHITE, 5, 7, PlayerID.PLAYER_ONE_WHITE, HashKeyForPictures.WHITE_BISHOP)
  white_knight_two = Knight(PieceType.KNIGHT, ColorsPieces.WHITE, 6, 7, PlayerID.PLAYER_ONE_WHITE, HashKeyForPictures.WHITE_KNIGHT)
  white_rook_two   = Rook(PieceType.ROOK,   ColorsPieces.WHITE, 7, 7, PlayerID.PLAYER_ONE_WHITE, HashKeyForPictures.WHITE_ROOK)

  white_pawn_one   = Pawn(PieceType.PAWN, ColorsPieces.WHITE, 0, 6, PlayerID.PLAYER_ONE_WHITE, HashKeyForPictures.WHITE_PAWN)
  white_pawn_two   = Pawn(PieceType.PAWN, ColorsPieces.WHITE, 1, 6, PlayerID.PLAYER_ONE_WHITE, HashKeyForPictures.WHITE_PAWN)
  white_pawn_three = Pawn(PieceType.PAWN, ColorsPieces.WHITE, 2, 6, PlayerID.PLAYER_ONE_WHITE, HashKeyForPictures.WHITE_PAWN)
  white_pawn_four  = Pawn(PieceType.PAWN, ColorsPieces.WHITE, 3, 6, PlayerID.PLAYER_ONE_WHITE, HashKeyForPictures.WHITE_PAWN)
  white_pawn_five  = Pawn(PieceType.PAWN, ColorsPieces.WHITE, 4, 6, PlayerID.PLAYER_ONE_WHITE, HashKeyForPictures.WHITE_PAWN)
  white_pawn_six   = Pawn(PieceType.PAWN, ColorsPieces.WHITE, 5, 6, PlayerID.PLAYER_ONE_WHITE, HashKeyForPictures.WHITE_PAWN)
  white_pawn_seven = Pawn(PieceType.PAWN, ColorsPieces.WHITE, 6, 6, PlayerID.PLAYER_ONE_WHITE, HashKeyForPictures.WHITE_PAWN)
  white_pawn_eight = Pawn(PieceType.PAWN, ColorsPieces.WHITE, 7, 6, PlayerID.PLAYER_ONE_WHITE, HashKeyForPictures.WHITE_PAWN)

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

  all_pieces.append(white_pawn_one)
  all_pieces.append(white_pawn_two)
  all_pieces.append(white_pawn_three)
  all_pieces.append(white_pawn_four)
  all_pieces.append(white_pawn_five)
  all_pieces.append(white_pawn_six)
  all_pieces.append(white_pawn_seven)
  all_pieces.append(white_pawn_eight)

  all_pieces.append(white_rook_one)
  all_pieces.append(white_knight_one)
  all_pieces.append(white_bishop_one)
  all_pieces.append(white_queen)
  all_pieces.append(white_king)
  all_pieces.append(white_bishop_two)
  all_pieces.append(white_knight_two)
  all_pieces.append(white_rook_two)

  


  return all_pieces

def initializingBoard(all_pieces_in_dq : Deque[Piece]):
  main_logic_board = Board(all_pieces_in_dq, MAP_WIDTH, MAP_HEIGHT)

  return main_logic_board

def initAllImages():
  

  black_bishop = pygame.image.load("chess_python/classes/photos_/BlackBishop.png").convert_alpha()
  black_horse  = pygame.image.load("chess_python/classes/photos_/BlackHorse.png").convert_alpha()
  black_king   = pygame.image.load("chess_python/classes/photos_/BlackKing.png").convert_alpha()
  black_pawn   = pygame.image.load("chess_python/classes/photos_/BlackPawn.png").convert_alpha()
  black_queen  = pygame.image.load("chess_python/classes/photos_/BlackQueen.png").convert_alpha()
  black_rook   = pygame.image.load("chess_python/classes/photos_/BlackRook.png").convert_alpha()

  white_bishop = pygame.image.load("chess_python/classes/photos_/WhiteBishop.png").convert_alpha()
  white_horse  = pygame.image.load("chess_python/classes/photos_/WhiteHorse.png").convert_alpha()
  white_king   = pygame.image.load("chess_python/classes/photos_/WhiteKing.png").convert_alpha()
  white_pawn   = pygame.image.load("chess_python/classes/photos_/WhitePawn.png").convert_alpha()
  white_queen  = pygame.image.load("chess_python/classes/photos_/WhiteQueen.png").convert_alpha()
  white_rook   = pygame.image.load("chess_python/classes/photos_/WhiteRook.png").convert_alpha()

  black_bishop_playing = pygame.transform.smoothscale(black_bishop, (EVERY_PIECE_WIDTH_AND_HEIGHT, EVERY_PIECE_WIDTH_AND_HEIGHT))
  black_horse_playing  = pygame.transform.smoothscale(black_horse,  (EVERY_PIECE_WIDTH_AND_HEIGHT, EVERY_PIECE_WIDTH_AND_HEIGHT))
  black_king_playing   = pygame.transform.smoothscale(black_king,   (EVERY_PIECE_WIDTH_AND_HEIGHT, EVERY_PIECE_WIDTH_AND_HEIGHT))
  black_pawn_playing   = pygame.transform.smoothscale(black_pawn,   (EVERY_PIECE_WIDTH_AND_HEIGHT, EVERY_PIECE_WIDTH_AND_HEIGHT))
  black_queen_playing  = pygame.transform.smoothscale(black_queen,  (EVERY_PIECE_WIDTH_AND_HEIGHT, EVERY_PIECE_WIDTH_AND_HEIGHT))
  black_rook_playing   = pygame.transform.smoothscale(black_rook,   (EVERY_PIECE_WIDTH_AND_HEIGHT, EVERY_PIECE_WIDTH_AND_HEIGHT))

  white_bishop_playing = pygame.transform.smoothscale(white_bishop, (EVERY_PIECE_WIDTH_AND_HEIGHT, EVERY_PIECE_WIDTH_AND_HEIGHT))
  white_horse_playing  = pygame.transform.smoothscale(white_horse,  (EVERY_PIECE_WIDTH_AND_HEIGHT, EVERY_PIECE_WIDTH_AND_HEIGHT))
  white_king_playing   = pygame.transform.smoothscale(white_king,   (EVERY_PIECE_WIDTH_AND_HEIGHT, EVERY_PIECE_WIDTH_AND_HEIGHT))
  white_pawn_playing   = pygame.transform.smoothscale(white_pawn,   (EVERY_PIECE_WIDTH_AND_HEIGHT, EVERY_PIECE_WIDTH_AND_HEIGHT))
  white_queen_playing  = pygame.transform.smoothscale(white_queen,  (EVERY_PIECE_WIDTH_AND_HEIGHT, EVERY_PIECE_WIDTH_AND_HEIGHT))
  white_rook_playing   = pygame.transform.smoothscale(white_rook,   (EVERY_PIECE_WIDTH_AND_HEIGHT, EVERY_PIECE_WIDTH_AND_HEIGHT))

  #Graveyard smaller Scalings

  black_bishop_graveyard = pygame.transform.smoothscale(black_bishop, (EVERY_PIECE_W_H_FOR_GRAVEYARD, EVERY_PIECE_W_H_FOR_GRAVEYARD))
  black_horse_graveyard  = pygame.transform.smoothscale(black_horse,  (EVERY_PIECE_W_H_FOR_GRAVEYARD, EVERY_PIECE_W_H_FOR_GRAVEYARD))
  black_king_graveyard   = pygame.transform.smoothscale(black_king,   (EVERY_PIECE_W_H_FOR_GRAVEYARD, EVERY_PIECE_W_H_FOR_GRAVEYARD))
  black_pawn_graveyard   = pygame.transform.smoothscale(black_pawn,   (EVERY_PIECE_W_H_FOR_GRAVEYARD, EVERY_PIECE_W_H_FOR_GRAVEYARD))
  black_queen_graveyard  = pygame.transform.smoothscale(black_queen,  (EVERY_PIECE_W_H_FOR_GRAVEYARD, EVERY_PIECE_W_H_FOR_GRAVEYARD))
  black_rook_graveyard   = pygame.transform.smoothscale(black_rook,   (EVERY_PIECE_W_H_FOR_GRAVEYARD, EVERY_PIECE_W_H_FOR_GRAVEYARD))

  white_bishop_graveyard = pygame.transform.smoothscale(white_bishop, (EVERY_PIECE_W_H_FOR_GRAVEYARD, EVERY_PIECE_W_H_FOR_GRAVEYARD))
  white_horse_graveyard  = pygame.transform.smoothscale(white_horse,  (EVERY_PIECE_W_H_FOR_GRAVEYARD, EVERY_PIECE_W_H_FOR_GRAVEYARD))
  white_king_graveyard   = pygame.transform.smoothscale(white_king,   (EVERY_PIECE_W_H_FOR_GRAVEYARD, EVERY_PIECE_W_H_FOR_GRAVEYARD))
  white_pawn_graveyard   = pygame.transform.smoothscale(white_pawn,   (EVERY_PIECE_W_H_FOR_GRAVEYARD, EVERY_PIECE_W_H_FOR_GRAVEYARD))
  white_queen_graveyard  = pygame.transform.smoothscale(white_queen,  (EVERY_PIECE_W_H_FOR_GRAVEYARD, EVERY_PIECE_W_H_FOR_GRAVEYARD))
  white_rook_graveyard   = pygame.transform.smoothscale(white_rook,   (EVERY_PIECE_W_H_FOR_GRAVEYARD, EVERY_PIECE_W_H_FOR_GRAVEYARD))




  map_board = pygame.image.load("chess_python/classes/photos_/board.png").convert_alpha()
  map_board = pygame.transform.smoothscale(map_board, (map_board.get_width() * SCALING_FACTOR_FOUR, map_board.get_height() * SCALING_FACTOR_FOUR))

  # Promotion images << !
  black_promotion = pygame.image.load("chess_python/classes/photos_/blackPawnPromotionFinal.png").convert_alpha()
  black_promotion = pygame.transform.smoothscale(black_promotion, (PROMOTION_PICTURES_WIDTH, PROMOTION_PICTURES_HEIGHT))

  white_promotion = pygame.image.load("chess_python/classes/photos_/whitePawnPromotionFinal.png").convert_alpha()
  white_promotion = pygame.transform.smoothscale(white_promotion, (PROMOTION_PICTURES_WIDTH, PROMOTION_PICTURES_HEIGHT))

  hash_map_for_pictures[HashKeyForPictures.PROMOTION_BLACK] = black_promotion
  hash_map_for_pictures[HashKeyForPictures.PROMOTION_WHITE] = white_promotion





  # Pieces
  hash_map_for_pictures[HashKeyForPictures.BLACK_PAWN]   = black_pawn_playing
  hash_map_for_pictures[HashKeyForPictures.BLACK_KING]   = black_king_playing
  hash_map_for_pictures[HashKeyForPictures.BLACK_QUEEN]  = black_queen_playing
  hash_map_for_pictures[HashKeyForPictures.BLACK_BISHOP] = black_bishop_playing
  hash_map_for_pictures[HashKeyForPictures.BLACK_KNIGHT] = black_horse_playing
  hash_map_for_pictures[HashKeyForPictures.BLACK_ROOK]   = black_rook_playing

  hash_map_for_pictures[HashKeyForPictures.WHITE_PAWN]   = white_pawn_playing
  hash_map_for_pictures[HashKeyForPictures.WHITE_KING]   = white_king_playing
  hash_map_for_pictures[HashKeyForPictures.WHITE_QUEEN]  = white_queen_playing
  hash_map_for_pictures[HashKeyForPictures.WHITE_BISHOP] = white_bishop_playing
  hash_map_for_pictures[HashKeyForPictures.WHITE_KNIGHT] = white_horse_playing
  hash_map_for_pictures[HashKeyForPictures.WHITE_ROOK]   = white_rook_playing

  #Hashing the graveyard ones
  hash_map_for_graveyard_pictures[HashKeyForPictures.BLACK_PAWN]   = black_pawn_graveyard
  hash_map_for_graveyard_pictures[HashKeyForPictures.BLACK_KING]   = black_king_graveyard
  hash_map_for_graveyard_pictures[HashKeyForPictures.BLACK_QUEEN]  = black_queen_graveyard
  hash_map_for_graveyard_pictures[HashKeyForPictures.BLACK_BISHOP] = black_bishop_graveyard
  hash_map_for_graveyard_pictures[HashKeyForPictures.BLACK_KNIGHT] = black_horse_graveyard
  hash_map_for_graveyard_pictures[HashKeyForPictures.BLACK_ROOK]   = black_rook_graveyard

  hash_map_for_graveyard_pictures[HashKeyForPictures.WHITE_PAWN]   = white_pawn_graveyard
  hash_map_for_graveyard_pictures[HashKeyForPictures.WHITE_KING]   = white_king_graveyard
  hash_map_for_graveyard_pictures[HashKeyForPictures.WHITE_QUEEN]  = white_queen_graveyard
  hash_map_for_graveyard_pictures[HashKeyForPictures.WHITE_BISHOP] = white_bishop_graveyard
  hash_map_for_graveyard_pictures[HashKeyForPictures.WHITE_KNIGHT] = white_horse_graveyard
  hash_map_for_graveyard_pictures[HashKeyForPictures.WHITE_ROOK]   = white_rook_graveyard


  hash_map_for_pictures[HashKeyForPictures.BOARD] = map_board

  hash_map_for_rgba_tiles[ColorsTile.RED] = (180, 40, 40, 120) # Crimson red?

  #288c46 EMERALD GREEN
  hash_map_for_rgba_tiles[ColorsTile.GREEN] = (40, 140, 70, 110)

  #787878 Natural Grey
  hash_map_for_rgba_tiles[ColorsTile.GREY] = (120, 120, 120, 120) # alpha is freely by "hand" chosen 

def initPlayersAndTools():

  player_one: Player = Player(PlayerID.PLAYER_ONE_WHITE)
  player_two: Player = Player(PlayerID.PLAYER_TWO_BLACK)

  main_window = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
  pygame.display.set_caption("Cela's Chess <3")

  tools: Tools = Tools(player_one, player_two, main_window)

  return tools

def initFontAndSurfacesForScores(main_tools: Tools):

  main_tools.font = pygame.font.Font("chess_python/classes/fonts/PressStart2P-Regular.ttf", 12)

  main_tools.white_src = main_tools.font.render(WHITE_SCORE_STRING, True,  (255, 255, 255))
  main_tools.black_src = main_tools.font.render(BLACK_SCORE_STRING, True, (255, 255, 255))


  player_playing_src: pygame.Surface = main_tools.font.render(RenderingTextEnums.PLAYER_PLAYING_TEXT.value, True, (255, 255, 255))
  black_text_src: pygame.Surface = main_tools.font.render(RenderingTextEnums.BLACK_TEXT.value, True, (255, 255, 255))
  white_text_src: pygame.Surface = main_tools.font.render(RenderingTextEnums.WHITE_TEXT.value, True, (255, 255, 255))
  gamestate_text_src: pygame.Surface = main_tools.font.render(RenderingTextEnums.GAME_STATE_TEXT.value, True, (255, 255, 255))
  gamestate_playing_text_src: pygame.Surface = main_tools.font.render(RenderingTextEnums.GAME_STATE_PLAYING.value, True, (255, 255, 255))
  gamestate_check_text_src: pygame.Surface = main_tools.font.render(RenderingTextEnums.GAME_STATE_CHECK.value, True, (255, 255, 255))
  checkmate_text_white_src: pygame.Surface = main_tools.font.render(RenderingTextEnums.CHECK_MATE_WHITE.value, True, (255, 255, 255))
  checkmate_text_black_src: pygame.Surface = main_tools.font.render(RenderingTextEnums.CHECK_MATE_BLACK.value, True, (255, 255, 255))
  


  player_playing_dst = player_playing_src.get_rect()
  black_text_dst = black_text_src.get_rect()
  white_text_dst = white_text_src.get_rect()
  gamestate_text_dst = gamestate_text_src.get_rect()
  gamestate_playing_text_dst = gamestate_playing_text_src.get_rect()
  gamestate_check_text_dst = gamestate_check_text_src.get_rect()
  checkmate_text_white_dst = checkmate_text_white_src.get_rect()
  checkmate_text_black_dst = checkmate_text_black_src.get_rect()

  player_playing_dst.y = OFFSET_FOR_TEXT
  player_playing_dst.x = SCREEN_WIDTH / 4 - player_playing_dst.w / 2

  black_text_dst.y = OFFSET_FOR_TEXT
  black_text_dst.x = player_playing_dst.w + player_playing_dst.x

  white_text_dst.y = OFFSET_FOR_TEXT
  white_text_dst.x = player_playing_dst.w + player_playing_dst.x


  gamestate_text_dst.y = OFFSET_FOR_TEXT
  gamestate_text_dst.x = (SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2) - gamestate_text_dst.w # 3/4 of the screen's X 

  gamestate_check_text_dst.y = OFFSET_FOR_TEXT
  gamestate_check_text_dst.x = gamestate_text_dst.x + gamestate_text_dst.w

  gamestate_playing_text_dst.y = OFFSET_FOR_TEXT
  gamestate_playing_text_dst.x = gamestate_text_dst.x + gamestate_text_dst.w

  checkmate_text_white_dst.y = OFFSET_FOR_TEXT
  checkmate_text_white_dst.x = gamestate_text_dst.x + gamestate_text_dst.w
  
  checkmate_text_black_dst.y = OFFSET_FOR_TEXT
  checkmate_text_black_dst.x = gamestate_text_dst.x + gamestate_text_dst.w


  hash_map_for_scores_and_text[RenderingTextEnums.PLAYER_PLAYING_TEXT] = (player_playing_src, player_playing_dst)
  hash_map_for_scores_and_text[RenderingTextEnums.BLACK_TEXT] = (black_text_src, black_text_dst)
  hash_map_for_scores_and_text[RenderingTextEnums.WHITE_TEXT] = (white_text_src, white_text_dst)
  hash_map_for_scores_and_text[RenderingTextEnums.GAME_STATE_TEXT] = (gamestate_text_src, gamestate_text_dst)
  hash_map_for_scores_and_text[RenderingTextEnums.GAME_STATE_CHECK] = (gamestate_check_text_src, gamestate_check_text_dst)
  hash_map_for_scores_and_text[RenderingTextEnums.GAME_STATE_PLAYING] = (gamestate_playing_text_src, gamestate_playing_text_dst)
  hash_map_for_scores_and_text[RenderingTextEnums.CHECK_MATE_WHITE] = (checkmate_text_white_src, checkmate_text_white_dst)
  hash_map_for_scores_and_text[RenderingTextEnums.CHECK_MATE_BLACK] = (checkmate_text_black_src, checkmate_text_black_dst)

  main_tools.white_rect = main_tools.white_src.get_rect()
  main_tools.black_rect = main_tools.black_src.get_rect()

  #axis
  main_tools.black_rect.x = BOARD_X 
  main_tools.black_rect.y = BOARD_Y - BOARD_OFFSET_X_AND_Y

  main_tools.white_rect.x = BOARD_X
  main_tools.white_rect.y = BOARD_Y + BOARD_WIDTH_AND_HEIGHT + BOARD_OFFSET_X_AND_Y

  main_tools.player_white.compute_score(main_tools)
  main_tools.player_black.compute_score(main_tools)

def initAxisForAllPieces(main_tools: Tools):

  for index in range(MAP_HEIGHT):
    for inner in range(MAP_WIDTH):

      current_tile: Tile = main_tools.main_board.chess_board[index][inner]

      if(not current_tile.is_occupied()):
        continue

      placeholder_piece: Piece = current_tile.piece

      placeholder_piece.x_axis = current_tile.x_axis
      placeholder_piece.y_axis = current_tile.y_axis

def assignKingsToTools(main_tools: Tools, king_white_tile: Tile, king_black_tile: Tile):

  main_tools.black_king = king_black_tile.piece
  main_tools.white_king = king_white_tile.piece


  






