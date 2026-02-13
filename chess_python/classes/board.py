from .constants import ColorsTile, HashKeyForPictures, BOARD_X, BOARD_Y, BOARD_OFFSET_X_AND_Y, TILE_WIDTH_AND_HEIGHT, MAP_HEIGHT, MAP_WIDTH
from .tile import Tile
from ..initialization import hash_map_for_pictures, hash_map_for_rgba_tiles
from typing import List, Tuple

import pygame





class Board:
  def __init__(self, deque_of_pieces, size_width : int, size_height : int):
    
    self.chess_board = []

    remove_piece_this_iteration = True
    current_color = ColorsTile.WHITE

    
    

    for y in range(size_height):
      row = [] # outer index // index // y in python you must make rows 

      y_axis = BOARD_Y + BOARD_OFFSET_X_AND_Y + TILE_WIDTH_AND_HEIGHT * y
      

      for x in range(size_width):
        
        x_axis = BOARD_X + BOARD_OFFSET_X_AND_Y + TILE_WIDTH_AND_HEIGHT * x 
        if y != 0 and y != 1 and y != 6 and y != 7:
          remove_piece_this_iteration = False


        if remove_piece_this_iteration == True:
          row.append(Tile(current_color, deque_of_pieces.popleft(), x, y, x_axis, y_axis))
        else:
          row.append(Tile(current_color, None, x, y, x_axis, y_axis))

        if current_color == ColorsTile.BLACK:
          current_color = ColorsTile.WHITE
        else:  
          current_color = ColorsTile.BLACK # check this out later << possible bug !

        remove_piece_this_iteration = True

      self.chess_board.append(row)

  def print_background(self, window_renderer: pygame.Surface):
    
    window_renderer.fill(0, 0, 0) # fill black as background

    window_renderer.blit(hash_map_for_pictures[HashKeyForPictures.BOARD], (BOARD_X, BOARD_Y))


  def print_pieces(self, window_renderer: pygame.Surface):
    
    for y in range(MAP_HEIGHT):
      for x in range(MAP_WIDTH):

        placeholder : Tile = self.chess_board[y][x]

        if(not placeholder.is_occupied()):
          continue

        current_piece = placeholder.piece

        window_renderer.blit(hash_map_for_pictures[current_piece.hash_key], placeholder.x_axis, placeholder.y_axis)

  
  def print_legal_moves(self, window_renderer: pygame.Surface, list_of_legal_moves: List[Tuple[Tile, ColorsTile]]):
    

    for index in range(len(list_of_legal_moves)):
      
      placeholder : Tile = list_of_legal_moves[index][0]

      colored_tile = pygame.Surface((TILE_WIDTH_AND_HEIGHT, TILE_WIDTH_AND_HEIGHT), pygame.SRCALPHA)
      colored_tile.fill(hash_map_for_rgba_tiles[list_of_legal_moves[index][1]])

      window_renderer.blit(colored_tile, placeholder.x_axis, placeholder.y_axis)
      






        

  








