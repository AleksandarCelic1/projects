import pygame
import copy
import chess_python.classes.constants as constants

from .classes.board import Board
from .classes.constants import BOARD_X, BOARD_Y, BOARD_OFFSET_X_AND_Y, BOARD_INNER_WIDTH_AND_HEIGHT, TILE_WIDTH_AND_HEIGHT, PlayerID, ColorsTile, FRAME_DELAY, ColorsPieces, HashKeyForPictures
from .classes.constants import ONE_SECOND, NEAR_LIMIT, ARRIVED_EXACT_LIMIT, PieceType, BLACK_PAWN_EN_PASSANT_Y, WHITE_PAWN_EN_PASSANT_Y, PromotionSelection
from .classes.constants import BLACK_PAWN_INITIAL_Y, WHITE_PAWN_INITIAL_Y, KING_SIDE_ROOK_X, QUEEN_SIDE_ROOK_X, ROOK_OFFSET_AFTER_QUEEN_CASTLE, ROOK_OFFSET_AFTER_KING_CASTLE
from .classes.constants import BLACK_PROMOTION_Y, WHITE_PROMOTION_Y, PROMOTION_PICTURES_HEIGHT, PROMOTION_PICTURES_WIDTH, PROMOTION_PICTURES_X, PROMOTION_PICTURES_Y, EACH_BOX_IN_PROMOTION_H, EACH_BOX_IN_PROMOTION_W

from .classes.moveFunctions import isInsideOfBounds, is_attacked
from .classes.tile import Tile
from .classes.tools import Tools, GameState
from .classes.piece import Piece
from .classes.pawn import Pawn
from .classes.king import King
from .classes.queen import Queen
from .classes.bishop import Bishop
from .classes.knight import Knight
from .classes.rook import Rook
from .classes.player import Player


from typing import List, Tuple
#make game dispatcher for x,y of mouse to get what piece shall be moved 

def dispatcher(main_tools: Tools, mouse_x: int, mouse_y: int, player_id: PlayerID):
  
  if(mouse_x >= BOARD_X + BOARD_OFFSET_X_AND_Y 
  and mouse_x <= BOARD_X + BOARD_OFFSET_X_AND_Y + BOARD_INNER_WIDTH_AND_HEIGHT
  and mouse_y >= BOARD_Y + BOARD_OFFSET_X_AND_Y
  and mouse_y <= BOARD_Y + BOARD_OFFSET_X_AND_Y + BOARD_INNER_WIDTH_AND_HEIGHT):
    clicked_column = (mouse_x - (BOARD_X + BOARD_OFFSET_X_AND_Y)) // TILE_WIDTH_AND_HEIGHT
    clicked_row = (mouse_y - (BOARD_Y + BOARD_OFFSET_X_AND_Y)) // TILE_WIDTH_AND_HEIGHT

    if(not isInsideOfBounds(clicked_column, clicked_row)):
      return
    
    board_placeholder = main_tools.main_board
    placeholder : Tile = board_placeholder.chess_board[clicked_row][clicked_column]

    if main_tools.is_piece_selected:
      if not placeholder.is_occupied() or placeholder.piece.player_id != player_id:
        main_tools.move_taken = True
        main_tools.current_players_target_tile = placeholder
        main_tools.is_piece_selected = False
        return None

    if placeholder.is_occupied() and placeholder.piece.player_id == player_id:
      main_tools.is_piece_selected = True
      main_tools.current_players_selected_tile = placeholder
      array_of_legal_moves = placeholder.piece.getMoves(board_placeholder, clicked_column, clicked_row)
      return array_of_legal_moves
  

def validatingLastMove(main_tools: Tools, array_of_legal_moves: List[Tuple[Tile, ColorsTile]]):
  
  if array_of_legal_moves is None:
    return
  
  for index in range(len(array_of_legal_moves)):

    if(main_tools.current_players_target_tile.x == array_of_legal_moves[index][0].x 
    and main_tools.current_players_target_tile.y == array_of_legal_moves[index][0].y
    and array_of_legal_moves[index][1] != ColorsTile.RED):
      
      if(main_tools.game_state != GameState.CHECK):
        if(not isPinned(main_tools, main_tools.current_players_target_tile, main_tools.current_players_selected_tile, main_tools.player_playing)):
          main_tools.game_state = GameState.PERFORMING_LERP
          didCastleOccur(main_tools)
          break
        
      else:
        
        if main_tools.current_players_selected_tile.piece.type == PieceType.KING:
          main_tools.game_state = GameState.PERFORMING_LERP
          didCastleOccur(main_tools)
          break
        else:
          

          board_copy: Board = copy.deepcopy(main_tools.main_board)

          target_tile: Tile = board_copy.chess_board[main_tools.current_players_target_tile.y][main_tools.current_players_target_tile.x]
          target_tile.piece = main_tools.current_players_selected_tile.piece

          # im not changing the XY of the target PIECE << ! just in case it would be needed in future

          origin_tile: Tile = board_copy.chess_board[main_tools.current_players_selected_tile.y][main_tools.current_players_selected_tile.x]
          origin_tile.piece = None

          if(main_tools.player_playing == PlayerID.PLAYER_ONE_WHITE):
            if(is_attacked(board_copy, board_copy.chess_board[main_tools.white_king.y][main_tools.white_king.x], ColorsPieces.WHITE) == 0):
              main_tools.game_state = GameState.PERFORMING_LERP
              didCastleOccur(main_tools)
              break
          else:
            if(is_attacked(board_copy, board_copy.chess_board[main_tools.black_king.y][main_tools.black_king.x], ColorsPieces.BLACK) == 0):
              main_tools.game_state = GameState.PERFORMING_LERP
              didCastleOccur(main_tools)
              break
        

        
  main_tools.is_piece_selected = False
  main_tools.move_taken = False # in case if nothing is found everything is reset 

def specialDispatcherForPromotion(main_tools: Tools, mouse_x: int, mouse_y: int):

  if(mouse_x >= PROMOTION_PICTURES_X and
     mouse_x <= PROMOTION_PICTURES_X + PROMOTION_PICTURES_WIDTH and
     mouse_y >= PROMOTION_PICTURES_Y and
     mouse_y <= PROMOTION_PICTURES_Y + PROMOTION_PICTURES_HEIGHT):
    

    clicked_column = (mouse_x - PROMOTION_PICTURES_X) // EACH_BOX_IN_PROMOTION_W

    # row probably not needed as we dont really have much rows only 1 constantly chekcing rows means nothing << !
    clicked_row = (mouse_y - PROMOTION_PICTURES_Y) // EACH_BOX_IN_PROMOTION_H


    if(clicked_column < 0 or clicked_column > 3):
      return None
    

    changePawnToSelectedPiece(main_tools, clicked_column)
    main_tools.game_state = GameState.PLAYING
    handleEndOfLerpLogic(main_tools) # this is called usually after the LERP is finished to evaluate logic
    # as we didnt perform lerp we only need the logic part << !

    


    pass


  pass



def changePawnToSelectedPiece(main_tools: Tools, choice_clicked: int):

  board_reference: Board = main_tools.main_board
  src_pawn: Pawn = main_tools.source_pawn
  placeholder: Piece = None

  if(choice_clicked == PromotionSelection.QUEEN.value):
    placeholder = Queen(PieceType.QUEEN, src_pawn.color, src_pawn.x, src_pawn.y, src_pawn.player_id,
    HashKeyForPictures.BLACK_QUEEN if (src_pawn.color == ColorsPieces.BLACK) else HashKeyForPictures.WHITE_QUEEN)
  
  elif(choice_clicked == PromotionSelection.ROOK.value):
    placeholder = Rook(PieceType.ROOK, src_pawn.color, src_pawn.x, src_pawn.y, src_pawn.player_id,
    HashKeyForPictures.BLACK_ROOK if (src_pawn.color == ColorsPieces.BLACK) else HashKeyForPictures.WHITE_ROOK)
  
  elif(choice_clicked == PromotionSelection.KNIGHT.value):
    placeholder = Knight(PieceType.KNIGHT, src_pawn.color, src_pawn.x, src_pawn.y, src_pawn.player_id,
    HashKeyForPictures.BLACK_KNIGHT if (src_pawn.color == ColorsPieces.BLACK) else HashKeyForPictures.WHITE_KNIGHT)
  
  elif(choice_clicked == PromotionSelection.BISHOP.value):
    placeholder = Bishop(PieceType.BISHOP, src_pawn.color, src_pawn.x, src_pawn.y, src_pawn.player_id,
    HashKeyForPictures.BLACK_BISHOP if (src_pawn.color == ColorsPieces.BLACK) else HashKeyForPictures.WHITE_BISHOP)
  else:
    return None
  
  placeholder.x_axis = src_pawn.x_axis
  placeholder.y_axis = src_pawn.y_axis


  current_tile: Tile = board_reference.chess_board[src_pawn.y][src_pawn.x]
  current_tile.piece = placeholder

  if(main_tools.player_playing == PlayerID.PLAYER_ONE_WHITE):
    main_tools.player_white.troops.remove(src_pawn)
    main_tools.player_white.troops.append(placeholder)
  elif(main_tools.player_playing == PlayerID.PLAYER_TWO_BLACK):
    main_tools.player_black.troops.remove(src_pawn)
    main_tools.player_black.troops.append(placeholder)


def didCastleOccur(main_tools: Tools):

  selected_piece: Piece = main_tools.current_players_selected_tile.piece
  target_tile: Tile = main_tools.current_players_target_tile

  if(selected_piece.type == PieceType.KING):

    if((selected_piece.x == target_tile.x + 2)):
      print("QUEENSIDE")
      main_tools.castle_being_performed = True
      main_tools.which_rook = QUEEN_SIDE_ROOK_X

    elif(selected_piece.x == target_tile.x - 2):
      print("KINGSIDE")
      main_tools.castle_being_performed = True
      main_tools.which_rook = KING_SIDE_ROOK_X

def controlFPS(frame_start: int):
  current_frame_time = pygame.time.get_ticks() - frame_start
  if(current_frame_time < FRAME_DELAY):
    pygame.time.delay(FRAME_DELAY - current_frame_time)

def lerp(A: float, B: float, T:float):
  return A + (B - A) * T

def updateLerp(main_tools: Tools, delta_time: float):

  time: float = 10.0 * delta_time

  if time > 1.0:
    time = 1.0


  source: Piece = main_tools.current_players_selected_tile.piece
  #source_tile: Tile = main_tools.current_players_selected_tile
  #target: Piece = main_tools.current_players_target_tile.piece
  target_tile: Tile = main_tools.current_players_target_tile



  source.x_axis = lerp(source.x_axis, target_tile.x_axis, time)
  source.y_axis = lerp(source.y_axis, target_tile.y_axis, time)

  
  if(not main_tools.is_near_the_destination):

    if(abs(source.x_axis - target_tile.x_axis) < NEAR_LIMIT and abs(source.y_axis - target_tile.y_axis) < NEAR_LIMIT):
      main_tools.is_near_the_destination = True

      if(target_tile.is_occupied()):
        capturePiece(main_tools, target_tile)
      elif(not target_tile.is_occupied() and source.type == PieceType.PAWN):

        pawn_placeholder: Pawn = source
        tile: Tile = specialCaseEnPassant(main_tools, pawn_placeholder, target_tile)
        if(tile is not None):
          capturePiece(main_tools, tile)

  if(abs(source.x_axis - target_tile.x_axis) < ARRIVED_EXACT_LIMIT and abs(source.y_axis - target_tile.y_axis) < ARRIVED_EXACT_LIMIT):
    finishLerp(main_tools, source, target_tile)

  return

def finishLerp(main_tools: Tools, source: Piece, target: Tile):
  main_tools.is_near_the_destination = False
  main_tools.game_state = GameState.PLAYING
  

  source.x_axis = target.x_axis
  source.y_axis = target.y_axis

  board: Board = main_tools.main_board

  current : Tile = board.chess_board[source.y][source.x]
  current.piece = None

  if(source.type == PieceType.PAWN):
    pawn: Pawn = source
    specialCaseForPawn(pawn, target)
  elif(not source.did_i_move_already):
    source.did_i_move_already = True

  source.x = target.x
  source.y = target.y

  if(source.type == PieceType.PAWN):
    pawnPromotionDetecter(main_tools, source)
  

  current : Tile = board.chess_board[source.y][source.x]
  current.piece = source

  handleEndOfLerpLogic(main_tools)

  return

def handleEndOfLerpLogic(main_tools: Tools):

  if(main_tools.castle_being_performed):
    main_tools.game_state = GameState.PERFORMING_LERP
    main_tools.castle_being_performed = False
    main_tools.is_near_the_destination = False
    offset = ROOK_OFFSET_AFTER_KING_CASTLE if main_tools.which_rook == KING_SIDE_ROOK_X else ROOK_OFFSET_AFTER_QUEEN_CASTLE
    if(main_tools.player_playing == PlayerID.PLAYER_ONE_WHITE):
      main_tools.current_players_selected_tile = main_tools.main_board.chess_board[main_tools.white_king.y][main_tools.which_rook]
      main_tools.current_players_target_tile = main_tools.main_board.chess_board[main_tools.white_king.y][main_tools.which_rook + offset]
    else:
      main_tools.current_players_selected_tile = main_tools.main_board.chess_board[main_tools.black_king.y][main_tools.which_rook]
      main_tools.current_players_target_tile = main_tools.main_board.chess_board[main_tools.black_king.y][main_tools.which_rook + offset]

  elif(main_tools.game_state == GameState.PROMOTION):
    return # im not going to check for CHECKS before the player chose the desired piece to turn his pawn into and 
    # i will not change player playing as the turn for the current player didn't change << !
  else:
    specialCaseForKingsCheck(main_tools)
    main_tools.player_playing = PlayerID.PLAYER_ONE_WHITE if main_tools.player_playing == PlayerID.PLAYER_TWO_BLACK else PlayerID.PLAYER_TWO_BLACK


  pass

def pawnPromotionDetecter(main_tools: Tools, source: Pawn):

  if((source.color == ColorsPieces.WHITE and source.y == WHITE_PROMOTION_Y) or (source.color == ColorsPieces.BLACK and source.y == BLACK_PROMOTION_Y)):
    main_tools.game_state = GameState.PROMOTION
    main_tools.source_pawn = source

def specialCaseForKingsCheck(main_tools: Tools):

  board_reference : Board = main_tools.main_board

  if(main_tools.white_king.am_i_in_check):
    main_tools.white_king.am_i_in_check = False
    main_tools.game_state = GameState.PLAYING
  elif(main_tools.black_king.am_i_in_check):
    main_tools.black_king.am_i_in_check = False
    main_tools.game_state = GameState.PLAYING

  if(main_tools.player_playing == PlayerID.PLAYER_ONE_WHITE and not main_tools.white_king.am_i_in_check):
    amount_of_attackers = is_attacked(board_reference, board_reference.chess_board[main_tools.black_king.y][main_tools.black_king.x], ColorsPieces.BLACK)
    
    if(amount_of_attackers == 0):
      # from here you can call STALEMATE CHECKER WITH THE BLACK KING 
      stalemateCheck(main_tools, main_tools.player_black, main_tools.player_white, main_tools.black_king)
      
    else:
      print('BLACK KING ATTACKED')
      main_tools.game_state = GameState.CHECK
      main_tools.black_king.am_i_in_check = True

      specialCaseForCheckmate(main_tools, amount_of_attackers, main_tools.black_king)
  elif(main_tools.player_playing == PlayerID.PLAYER_TWO_BLACK and not main_tools.black_king.am_i_in_check):
    amount_of_attackers = is_attacked(board_reference, board_reference.chess_board[main_tools.white_king.y][main_tools.white_king.x], ColorsPieces.WHITE)

    if(amount_of_attackers == 0):
      stalemateCheck(main_tools, main_tools.player_white, main_tools.player_black, main_tools.white_king)
    else:
      print('WHITE KING ATTACKED')
      main_tools.game_state = GameState.CHECK
      main_tools.white_king.am_i_in_check = True

      specialCaseForCheckmate(main_tools, amount_of_attackers, main_tools.white_king)

def specialCaseForCheckmate(main_tools: Tools, amount_of_attackers: int, current_king: King):

  current_king.getMoves(main_tools.main_board, current_king.x, current_king.y) # Current king is attacked << !

  if(current_king.total_legal_moves == 0): 

    if(amount_of_attackers > 1):
      main_tools.game_state = GameState.CHECKMATE
      main_tools.player_who_won = PlayerID.PLAYER_ONE_WHITE if (current_king.player_id == PlayerID.PLAYER_TWO_BLACK) else PlayerID.PLAYER_TWO_BLACK

    elif(amount_of_attackers == 1): # amount_of_attackers == 1   
      if(checkmateConfirmer(main_tools, current_king)):
        main_tools.game_state = GameState.CHECKMATE
        main_tools.player_who_won = PlayerID.PLAYER_ONE_WHITE if (current_king.player_id == PlayerID.PLAYER_TWO_BLACK) else PlayerID.PLAYER_TWO_BLACK



  else:
    return None
  
  return None
  
def checkmateConfirmer(main_tools: Tools, current_king: King):

  if(constants.CURRENT_ATTACKER):
    copy_of_current_attacker: Piece = copy.deepcopy(constants.CURRENT_ATTACKER[0]) # there must be at least one according to the ALGO #   queen thast attacking
    moves_between_king_and_attacker: List[Tuple[int, int]] = checkmateCoordsCalculator(copy_of_current_attacker, current_king)

  
  if(not checkIfAttackerCanBeEaten(main_tools, current_king, copy_of_current_attacker)
  and not checkIfAnyTileCanBeBlocked(main_tools, current_king, copy_of_current_attacker, moves_between_king_and_attacker)):
    print('Im checkmated <!')
    return True # means checkmate


    
  return False

def canBeBlocked(main_tools: Tools, current_king: King, current_attacker: Piece, tile_between_attacker_and_king: Tuple[int, int]):

  board_reference: Board = main_tools.main_board

  amount_of_attackers = is_attacked(board_reference, 
  board_reference.chess_board[tile_between_attacker_and_king[1]][tile_between_attacker_and_king[0]], current_attacker.color)
  #print(amount_of_attackers)

  

  if(amount_of_attackers == 0):
    return False
  
  elif(amount_of_attackers == 1): 
    # one piece can block this there must be isPinned as e.g. rook pins queen to hers king, and then bishop gives check 
    # queen can block but only if its not pinned << !
    if(not isPinned(main_tools, board_reference.chess_board[tile_between_attacker_and_king[1]][tile_between_attacker_and_king[0]],
    board_reference.chess_board[constants.CURRENT_ATTACKER[0].y][constants.CURRENT_ATTACKER[0].x], current_king.player_id)):
      
      return True # its not pinned means it CAN be blocked
    else:
      return False

  elif(amount_of_attackers > 1):

    copy_of_all_attackers: List[Piece] = copy.deepcopy(constants.CURRENT_ATTACKER)

    for index in range(len(copy_of_all_attackers)):
      if(not isPinned(main_tools, board_reference.chess_board[current_attacker.y][current_attacker.x],
      board_reference.chess_board[copy_of_all_attackers[index].y][copy_of_all_attackers[index].x], current_king.player_id)):
        return True # means it can be blocked
      
    return False
  return False

def checkIfAnyTileCanBeBlocked(main_tools: Tools, current_king: King, current_attacker: Piece, moves: List[Tuple[int, int]]):
  

  if(moves is None):
    return False
  
  for index in range(len(moves)):
    print(moves[index][0], moves[index][1])
    if(canBeBlocked(main_tools, current_king, current_attacker, (moves[index][0], moves[index][1]))):
      return True # means a tile between them can be blocked and thats NOT a checkmate << !
    
  return False

def checkIfAttackerCanBeEaten(main_tools: Tools, current_king: King, current_attacker: Piece):

  amount_of_attackers = is_attacked(main_tools.main_board, 
  main_tools.main_board.chess_board[current_attacker.y][current_attacker.x], current_attacker.color)

  if(amount_of_attackers == 0):
    return False # False means it cant be eaten which indicates a Checkmate
  
  elif(amount_of_attackers == 1):
    if(isPinned(main_tools, main_tools.main_board.chess_board[current_attacker.y][current_attacker.x],
    main_tools.main_board.chess_board[constants.CURRENT_ATTACKER[0].y][constants.CURRENT_ATTACKER[0].x], current_king.player_id)):
      # for id we can alos use current attackers ID
      print('[ERROR] CHECKIFATTACKERCANBEEATEN 2')
      return False
    else:
      print('[ERROR] CHECKIFATTACKERCANBEEATEN 3')
      return True
    
  elif(amount_of_attackers > 1):
    copy_of_all_attackers: List[Piece] = copy.deepcopy(constants.CURRENT_ATTACKER)

    for index in range(len(copy_of_all_attackers)):
      if(not isPinned(main_tools, main_tools.main_board.chess_board[current_attacker.y][current_attacker.x],
      main_tools.main_board.chess_board[copy_of_all_attackers[index].y][copy_of_all_attackers[index].x], current_king.player_id)):
        print('[ERROR] CHECKIFATTACKERCANBEEATEN 4')
        return True # if its NOT pinned means it can eat the attacker meaning there will be no CHECKMATE
      
  print('[ERROR] CHECKIFATTACKERCANBEEATEN 5')
  return False
  
def checkmateCoordsCalculator(current_attacker: Piece, current_king: King):

  # How do i go from king to attacker << ! if we wanted vice versa just turn the variables around << !
  direction_x = current_attacker.x - current_king.x
  direction_y = current_attacker.y - current_king.y

  if(direction_x == 0 and direction_y == 0):
    return None
  
  if not (direction_x == 0 or direction_y == 0 or abs(direction_x) == abs(direction_y)):
    return None

  step_x = 0 
  step_y = 0

  if(direction_x == 0):
    step_x = 0
  else:
    if(direction_x > 0):
      step_x = 1
    else:
      step_x = -1

  if(direction_y == 0):
    step_y = 0
  else:
    if(direction_y > 0):
      step_y = 1
    else:
      step_y = -1


  array_of_coords_towards_atttacker : List[Tuple[int, int]] = []

  # essentially first in between move 
  iterator_x = current_king.x + step_x 
  iterator_y = current_king.y + step_y

  for _ in range(7):

    if (iterator_x, iterator_y) == (current_attacker.x, current_attacker.y):
      break

    array_of_coords_towards_atttacker.append((iterator_x, iterator_y))
    iterator_x += step_x
    iterator_y += step_y

  #array_of_coords_towards_atttacker.append((current_attacker.x, current_attacker.y))

  return array_of_coords_towards_atttacker

def specialCaseForPawn(source: Pawn, target: Tile):
  if(not source.did_i_move_already):
    source.did_i_move_already = True

    if(source.y == WHITE_PAWN_INITIAL_Y and source.color == ColorsPieces.WHITE and target.y == BLACK_PAWN_EN_PASSANT_Y):
      source.vunerable_to_en_passant = True 
    elif(source.y == BLACK_PAWN_INITIAL_Y and source.color == ColorsPieces.BLACK and target.y == WHITE_PAWN_EN_PASSANT_Y):
      source.vunerable_to_en_passant = True
  
  elif(source.did_i_move_already and source.vunerable_to_en_passant):
    source.vunerable_to_en_passant = False

def specialCaseEnPassant(main_tools: Tools, source: Pawn, target: Tile):
  
  if(source.x == target.x):
    return None
  
  current_tile : Tile = None
  if((source.color == ColorsPieces.WHITE and source.y == WHITE_PAWN_EN_PASSANT_Y)
  or (source.color == ColorsPieces.BLACK and source.y == BLACK_PAWN_EN_PASSANT_Y)):
    current_tile = main_tools.main_board.chess_board[source.y][target.x]

  return current_tile
  
def capturePiece(main_tools: Tools, target_tile: Tile):
  placeholder: Piece = target_tile.piece
  
  if(placeholder.player_id == PlayerID.PLAYER_ONE_WHITE):
    main_tools.player_black.graveyard.append(placeholder)
    main_tools.player_black.my_graveyard_changed = True
  else:
    main_tools.player_white.graveyard.append(placeholder)
    main_tools.player_white.my_graveyard_changed = True

  target_tile.piece = None

def calculateDeltaTime(current_frame: float, last_frame: float):
  return (current_frame - last_frame) / ONE_SECOND
  
def isPinned(main_tools: Tools, target_tile_origin: Tile, source_tile_origin: Tile, king_id: PlayerID): # source goes to target and then we see if king is attacked 

  board_reference: Board = copy.deepcopy(main_tools.main_board)

  target_tile: Tile = board_reference.chess_board[target_tile_origin.y][target_tile_origin.x]
  source_tile: Tile = board_reference.chess_board[source_tile_origin.y][source_tile_origin.x]

  target_tile.piece = source_tile.piece
  source_tile.piece = None

  if(king_id == PlayerID.PLAYER_ONE_WHITE): # True means Corresponding King is still in check after simulating this move << ! 
    if(is_attacked(board_reference, board_reference.chess_board[main_tools.white_king.y][main_tools.white_king.x], ColorsPieces.WHITE) != 0):
      del board_reference
      return True
  else: 
    if(is_attacked(board_reference, board_reference.chess_board[main_tools.black_king.y][main_tools.black_king.x], ColorsPieces.BLACK) != 0):
      del board_reference
      return True

  del board_reference
  return False

def stalemateCheck(main_tools: Tools, player: Player, opposite_player: Player, king: King):

  # player is the one that has "king"
  king.getMoves(main_tools.main_board, king.x, king.y)
  iterator: Piece = None

  if(king.total_legal_moves == 0):
    for iterator in range(len(player.troops)):
    
      #checking if individual piece can move 
      player.troops[iterator].getMoves(main_tools.main_board, player.troops[iterator].x, player.troops[iterator].y)

      if(player.troops[iterator].total_legal_moves > 0):
        return
      
    main_tools.game_state = GameState.STALEMATE
    return
  else:
    # king can move << !
    if(len(player.troops) == 0 and len(opposite_player.troops) == 1):
      
      for iterator in range(len(opposite_player.troops)):

        if(opposite_player.troops[iterator].type != PieceType.KNIGHT and opposite_player.troops[iterator].type != PieceType.BISHOP):
          return

      main_tools.game_state = GameState.STALEMATE
      return


    elif(len(player.troops) == 0 and len(opposite_player.troops) > 1):
      return
    elif(len(player.troops) == 0 and len(opposite_player.troops) == 0):
      main_tools.game_state = GameState.STALEMATE
      return

      
  
  return
