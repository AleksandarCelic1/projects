import pygame

from .classes.board import Board
from .classes.constants import BOARD_X, BOARD_Y, BOARD_OFFSET_X_AND_Y, BOARD_INNER_WIDTH_AND_HEIGHT, TILE_WIDTH_AND_HEIGHT, PlayerID, ColorsTile, FRAME_DELAY
from .classes.moveFunctions import isInsideOfBounds
from .classes.tile import Tile
from .classes.tools import Tools, GameState

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

    if(not placeholder.is_occupied()):
      main_tools.is_piece_selected = False
      return
    
    current_piece = placeholder.piece
    if(current_piece.player_id != player_id and  not main_tools.is_piece_selected):
      return
    elif(current_piece.player_id != player_id and main_tools.is_piece_selected):
      current_piece.should_be_captured # Will do a linear scan
      main_tools.move_taken = True
      main_tools.current_players_target_tile = placeholder
      return
    
    print("Clicked row:", clicked_row)
    print("Clicked col:", clicked_column)

    board_left = BOARD_X + BOARD_OFFSET_X_AND_Y
    board_top  = BOARD_Y + BOARD_OFFSET_X_AND_Y

    local_x = mouse_x - board_left
    local_y = mouse_y - board_top

    print("mouse:", mouse_x, mouse_y)
    print("board top-left:", board_left, board_top)
    print("local:", local_x, local_y)
    print("row,col:", local_y // TILE_WIDTH_AND_HEIGHT, local_x // TILE_WIDTH_AND_HEIGHT)





    main_tools.is_piece_selected = True
    main_tools.current_players_selected_tile = placeholder
    array_of_legal_moves = current_piece.getMoves(board_placeholder, clicked_column, clicked_row)

    return array_of_legal_moves
  

def validatingLastMove(main_tools: Tools, array_of_legal_moves: List[Tuple[Tile, ColorsTile]]):

  if array_of_legal_moves is None:
    return
  
  for index in range(len(array_of_legal_moves)):

    if(main_tools.current_players_target_tile.x== array_of_legal_moves[index][0].x 
    and main_tools.current_players_target_tile.y == array_of_legal_moves[index][0].y
    and array_of_legal_moves[index][1] != ColorsTile.RED):
      main_tools.game_state = GameState.PERFORMING_LERP
      break
    
  
  main_tools.is_piece_selected = False
  main_tools.move_taken = False # in case if nothing is found everything is reset 
    



# dispatcher should calculate according to the x and y which column and row was pressed on the chess tables if its not within the bounds
# drop it, if yes get that tile from the board and check if its occupied if yes call the getMoves() from that piece and change its "is_selected" to true
# if its not already done within the function, and when we get the moves back we shall return this and render it and when another mousebutton down is selected 
# this one shall not be selected anymore.

def controlFPS(frame_start: int):
  current_frame_time = pygame.time.get_ticks() - frame_start
  if(current_frame_time < FRAME_DELAY):
    pygame.time.delay(FRAME_DELAY - current_frame_time)
  
