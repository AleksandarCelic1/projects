import pygame

from .classes.board import Board
from .classes.constants import FPS, FRAME_DELAY, IS_A_PIECE_SELECTED, BOARD_OFFSET_X_AND_Y, BOARD_X, BOARD_Y, BOARD_INNER_WIDTH_AND_HEIGHT, TILE_WIDTH_AND_HEIGHT
from .classes.moveFunctions import isInsideOfBounds
from .classes.tile import Tile

from typing import List, Tuple
#make game dispatcher for x,y of mouse to get what piece shall be moved 

def dispatcher(board: Board, mouse_x: int, mouse_y: int):
  
  if(mouse_x >= BOARD_X + BOARD_OFFSET_X_AND_Y 
  and mouse_x <= BOARD_X + BOARD_OFFSET_X_AND_Y + BOARD_INNER_WIDTH_AND_HEIGHT
  and mouse_y >= BOARD_Y + BOARD_OFFSET_X_AND_Y
  and mouse_y <= BOARD_Y + BOARD_OFFSET_X_AND_Y + BOARD_INNER_WIDTH_AND_HEIGHT):
    clicked_column = mouse_x / TILE_WIDTH_AND_HEIGHT
    clicked_row = mouse_y / TILE_WIDTH_AND_HEIGHT

    if(not isInsideOfBounds(clicked_column, clicked_row)):
      return
    
    placeholder : Tile = board.chess_board[clicked_row][clicked_column]

    if(not placeholder.is_occupied()):
      return
    
    IS_A_PIECE_SELECTED = True
    current_piece = placeholder.piece

    array_of_legal_moves = current_piece.getMoves(board, clicked_column, clicked_row)

    return array_of_legal_moves



# dispatcher should calculate according to the x and y which column and row was pressed on the chess tables if its not within the bounds
# drop it, if yes get that tile from the board and check if its occupied if yes call the getMoves() from that piece and change its "is_selected" to true
# if its not already done within the function, and when we get the moves back we shall return this and render it and when another mousebutton down is selected 
# this one shall not be selected anymore.

def controlFPS(frame_start: int):
  current_frame_time = pygame.time.get_ticks() - frame_start
  if(current_frame_time < FRAME_DELAY):
    pygame.time.delay(FRAME_DELAY - current_frame_time)
  
