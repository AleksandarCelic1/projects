import pygame
import copy

from .classes.board import Board
from .classes.constants import BOARD_X, BOARD_Y, BOARD_OFFSET_X_AND_Y, BOARD_INNER_WIDTH_AND_HEIGHT, TILE_WIDTH_AND_HEIGHT, PlayerID, ColorsTile, FRAME_DELAY, ColorsPieces
from .classes.constants import ONE_SECOND, NEAR_LIMIT, ARRIVED_EXACT_LIMIT, PieceType, BLACK_PAWN_EN_PASSANT_Y, WHITE_PAWN_EN_PASSANT_Y, X_OFFSETS_FOR_EN_PASSANT
from .classes.constants import BLACK_PAWN_INITIAL_Y, WHITE_PAWN_INITIAL_Y
from .classes.moveFunctions import isInsideOfBounds, is_attacked
from .classes.tile import Tile
from .classes.tools import Tools, GameState
from .classes.piece import Piece
from .classes.pawn import Pawn
from .classes.king import King


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

    if(main_tools.current_players_target_tile.x== array_of_legal_moves[index][0].x 
    and main_tools.current_players_target_tile.y == array_of_legal_moves[index][0].y
    and array_of_legal_moves[index][1] != ColorsTile.RED):
      
      if(main_tools.game_state != GameState.CHECK):
        main_tools.game_state = GameState.PERFORMING_LERP
      else:
        if():
          pass # << !!!!!


      break
    
  
  main_tools.is_piece_selected = False
  main_tools.move_taken = False # in case if nothing is found everything is reset 
    

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

  source.x = target.x
  source.y = target.y

  current : Tile = board.chess_board[source.y][source.x]
  current.piece = source

  specialCaseForKingsCheck(main_tools)
  main_tools.player_playing = PlayerID.PLAYER_ONE_WHITE if main_tools.player_playing == PlayerID.PLAYER_TWO_BLACK else PlayerID.PLAYER_TWO_BLACK

  

    
  
  return

def specialCaseForKingsCheck(main_tools: Tools):

  board_reference : Board = main_tools.main_board

  if(main_tools.player_playing == PlayerID.PLAYER_ONE_WHITE):
    if(is_attacked(board_reference, board_reference.chess_board[main_tools.black_king.y][main_tools.black_king.x], ColorsPieces.BLACK)):
      main_tools.game_state = GameState.CHECK
      main_tools.black_king.am_i_in_check = True
  elif(main_tools.player_playing == PlayerID.PLAYER_TWO_BLACK):
    if(is_attacked(board_reference, board_reference.chess_board[main_tools.white_king.y][main_tools.white_king.x], ColorsPieces.WHITE)):
      main_tools.game_state = GameState.CHECK
      main_tools.white_king.am_i_in_check = True



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
  else:
    main_tools.player_white.graveyard.append(placeholder)

  target_tile.piece = None
  main_tools.was_graveyard_changed = True

def calculateDeltaTime(current_frame: float, last_frame: float):
  return (current_frame - last_frame) / ONE_SECOND
  
