from .board import Board
from .tile import Tile
from . import constants
from .constants import ColorsTile

from typing import List, Tuple


KNIGHT_VIABLE_MOVES_OFFSETS= {  (-1, -2), (1, -2), (2, -1), (2, 1), (-2, -1), (-2, 1), (-1, 2), (1, 2)}
KING_VIABLE_MOVES_OFFSETS = { (-1, -1), (0, -1), (1, -1), (-1, 0), (1, 0), (-1, 1), (0, 1), (1, 1)}


# ALL FUNCTIONS ARE GOIGN TO BE FIRST MADE WITHOUT THE RULE OF PINNING << !


#1ST PART OF VERTICAL SCAN
def verticalMoves(logical_map : Board, x : int , y : int) -> List[Tuple[Tile, ColorsTile]]:

  origin : Tile = logical_map.chess_board[y][x]
  array_of_legal_moves : List[Tuple[Tile, ColorsTile]] = []

  scanVertical(logical_map, x, y - 1, -1, array_of_legal_moves, origin)
  scanVertical(logical_map, x, y + 1, 1, array_of_legal_moves, origin)

  return array_of_legal_moves

#2ND PART OF VERTICAL SCAN
def scanVertical(logical_map : Board, x : int, y : int, direction_y : int, moves: List[Tuple[Tile, ColorsTile]], origin : Tile):


  while constants.MAP_LOWER_BOUND <= y <= constants.MAP_UPPER_BOUND:

    current_tile : Tile = logical_map.chess_board[y][x]
    
    if current_tile.is_occupied():
      if current_tile.piece.player_id == origin.piece.player_id:
        moves.append((current_tile, ColorsTile.RED))
        break
      else:
        moves.append((current_tile, ColorsTile.GREEN))
    else:
      moves.append((current_tile, ColorsTile.GREY))

    
    y += direction_y

#1ST PART OF HORIZONTAL SCAN
def horizontalMoves(logical_map : Board, x : int, y : int) -> List[Tuple[Tile, ColorsTile]]:

  origin : Tile = logical_map.chess_board[y][x]
  array_of_legal_moves : List[Tuple[Tile, ColorsTile]] = []

  scanHorizontal(logical_map, x - 1, y, -1, array_of_legal_moves, origin)
  scanHorizontal(logical_map, x + 1, y, 1, array_of_legal_moves, origin)

  return array_of_legal_moves

#2ND PART OF HORIZONTAL SCAN
def scanHorizontal(logical_map : Board, x : int, y : int, direction_x : int, moves: List[Tuple[Tile, ColorsTile]], origin : Tile):


  while constants.MAP_LOWER_BOUND <= x <= constants.MAP_UPPER_BOUND:

    current_tile : Tile = logical_map.chess_board[y][x]
    
    if current_tile.is_occupied():
      if current_tile.piece.player_id == origin.piece.player_id:
        moves.append((current_tile, ColorsTile.RED))
        print(x,y)
        break
      else:
        moves.append((current_tile, ColorsTile.GREEN))
    else:
      moves.append((current_tile, ColorsTile.GREY))

    
    x += direction_x


#1ST PART OF DIAGONAL SCAN << !
def diagonalMoves(logical_map : Board, x : int, y : int) -> List[Tuple[Tile, ColorsTile]]:
  origin : Tile = logical_map.chess_board[y][x]

  array_of_legal_moves : List[Tuple[Tile, ColorsTile]]  = []

  scanDiagonals(logical_map, x, y, 1, 1, array_of_legal_moves, origin)
  scanDiagonals(logical_map, x, y, -1, -1, array_of_legal_moves, origin)
  scanDiagonals(logical_map, x, y, 1, -1, array_of_legal_moves, origin)
  scanDiagonals(logical_map, x, y, -1, 1, array_of_legal_moves, origin)

  return array_of_legal_moves

#2ND PART OF DIAGONAL SCAN << !
def scanDiagonals(logical_map : Board, x : int, y : int, direction_x : int, direction_y : int, moves: List[Tuple[Tile, ColorsTile]], origin : Tile):
  

  iterator_y = y + direction_y
  iterator_x = x + direction_x

  while constants.MAP_LOWER_BOUND <= iterator_y <= constants.MAP_UPPER_BOUND and constants.MAP_LOWER_BOUND <= iterator_x <= constants.MAP_UPPER_BOUND:

    current_tile : Tile = logical_map.chess_board[iterator_y][iterator_x]
    
    if current_tile.is_occupied():
      if current_tile.piece.player_id == origin.piece.player_id:
        moves.append((current_tile, ColorsTile.RED))
        break
      else:
        moves.append((current_tile, ColorsTile.GREEN))
    else:
      moves.append((current_tile, ColorsTile.GREY))

    
    iterator_x += direction_x
    iterator_y += direction_y
  

def knightViableMoves(logical_map: Board, x: int, y: int, moves: List[Tuple[Tile, ColorsTile]], origin: Tile):
  iterator_x :int = x
  iterator_y :int = y

  for offset_x, offset_y in KNIGHT_VIABLE_MOVES_OFFSETS:
    iterator_x = x
    iterator_y = y

    iterator_y += offset_y
    iterator_x += offset_x


    if not isInsideOfBounds(iterator_x, iterator_y):
      continue
      
    current_tile : Tile = logical_map.chess_board[iterator_y][iterator_x]

    if(current_tile.is_occupied()):
      if(current_tile.piece.player_id == origin.piece.player_id):
        moves.append((current_tile, ColorsTile.RED))
      else:
        moves.append((current_tile, ColorsTile.GREEN))
    else:
      moves.append((current_tile, ColorsTile.GREY))

      
        
  

def isInsideOfBounds(x: int, y: int) -> bool:
  placeholder = ((constants.MAP_LOWER_BOUND <= x <= constants.MAP_UPPER_BOUND) and (constants.MAP_LOWER_BOUND <= y <= constants.MAP_UPPER_BOUND))
  return placeholder

def kingViableMoves(logical_map: Board, x: int, y: int, moves: List[Tuple[Tile, ColorsTile]], origin: Tile):
  
  iterator_x = x
  iterator_y = y

  for offset_x, offset_y in KING_VIABLE_MOVES_OFFSETS:

    iterator_x = x
    iterator_y = y # must be reseted every time << !

    iterator_x += offset_x
    iterator_y += offset_y ### SEE IF THE LOGIC HERE IS AS IT SHOULD BE << !!

    if isInsideOfBounds(iterator_x, iterator_y):
      current_tile : Tile = logical_map.chess_board[iterator_y][iterator_x]

      if(current_tile.is_occupied()):
        if(current_tile.piece.player_id == origin.piece.player_id):
          moves.append((current_tile, ColorsTile.RED)) # cant eat your own stuff << !
        elif((current_tile.piece.player_id != origin.piece.player_id ) and ( not current_tile.piece.is_protected)):
          moves.append((current_tile, ColorsTile.GREEN)) # can eaet something next to the king as its not protected
        elif ((current_tile.piece.player_id != origin.piece.player_id) and (current_tile.piece.is_protected)):
          moves.append((current_tile, ColorsTile.RED)) # cant eat something next to king because its protected
      else:
        if(not current_tile.is_under_attack):
          moves.append((current_tile, ColorsTile.GREY)) # if nothing is there and nothing attack this square can move there
        else: 
          moves.append((current_tile, ColorsTile.RED)) # if nothing is there but somthing is attacking this square you cant move it 
  ### THIS MIGHT BE A PROBLEM LATER AS BOTH SIDES CAN ATTACK THE TILES  << !!!!!

#This is firstly made withou en-passant << !

  

  

  







  





    

















