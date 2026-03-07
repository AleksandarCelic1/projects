#import chess_python.classes.constants as constants

from . import constants
from .board import Board
from .tile import Tile
from .constants import ColorsTile, ColorsPieces, PieceType, HORIZONTAL_STRING, VERTICAL_STRING, DiagonalDirection, QUEEN_SIDE_ROOK_X, KING_SIDE_ROOK_X
from typing import List, Tuple
from .piece import Piece

import chess_python.classes.constants as constants


KNIGHT_VIABLE_MOVES_OFFSETS= {  (-1, -2), (1, -2), (2, -1), (2, 1), (-2, -1), (-2, 1), (-1, 2), (1, 2)}
KING_VIABLE_MOVES_OFFSETS = { (-1, -1), (0, -1), (1, -1), (-1, 0), (1, 0), (-1, 1), (0, 1), (1, 1)}
KING_CASTLE_QUEEN_SIDE = (-1, -2)
KING_CASTLE_KING_SIDE = (1, 2)
BLACK_PAWNS_ATTACKING_WHITE_OFFSET = {(-1, -1), (1, -1)}
WHITE_PAWNS_ATTACKING_BLACK_OFFSET = ((1, 1), (-1, 1))



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
        break
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
        break
      else:
        moves.append((current_tile, ColorsTile.GREEN))
        break
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
        break
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

  total_legal_moves = 0

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
        else:
          
          protected = is_attacked(logical_map, current_tile, origin.piece.color) # checking if the attacker is protected by "attacker accomplice" 
          
        
          if(current_tile.piece.player_id != origin.piece.player_id and protected == 0):
            moves.append((current_tile, ColorsTile.GREEN))
            total_legal_moves += 1
          elif(current_tile.piece.player_id != origin.piece.player_id and protected != 0):
            moves.append((current_tile, ColorsTile.RED))
      else:
        if(is_attacked(logical_map, current_tile, origin.piece.color)):
          moves.append((current_tile, ColorsTile.RED)) # if nothing is there and nothing attack this square can move there
        else: 
          moves.append((current_tile, ColorsTile.GREY)) # if nothing is there but somthing is attacking this square you cant move it 
          total_legal_moves += 1

  
  placeholder: Piece = origin.piece
  if(not placeholder.did_i_move_already and hasattr(placeholder, "am_i_in_check") and not placeholder.am_i_in_check):
    total_legal_moves += isCastlePossible(logical_map, moves, origin)

  return total_legal_moves

def isCastlePossible(logic_map: Board, moves: List[Tuple[Tile, ColorsTile]], origin: Tile):

  placeholder_tile: Tile = logic_map.chess_board[origin.y][0]

   # make another function let this be a mini dispatcher for kings and queens castle here we can do error check and then if 
   # sufficient we do the kings/queens castle to see if its viable 
  total_moves = 0

  kings_rook_tile: Tile = logic_map.chess_board[origin.y][KING_SIDE_ROOK_X]
  queens_rook_tile: Tile = logic_map.chess_board[origin.y][QUEEN_SIDE_ROOK_X]

  if(kings_rook_tile.piece is not None):
    if(not kings_rook_tile.piece.did_i_move_already):
      total_moves += castleHelperFunction(logic_map, moves, origin.piece, KING_CASTLE_KING_SIDE)

  if(queens_rook_tile.piece is not None):
    if(not queens_rook_tile.piece.did_i_move_already):
      total_moves += castleHelperFunction(logic_map, moves, origin.piece, KING_CASTLE_QUEEN_SIDE)

  return total_moves


def castleHelperFunction(logic_map: Board, moves: List[Tuple[Tile, ColorsTile]], origin_piece: Piece, offsets: List[int]):

  validator = 0
  
  for index in range(len(offsets)):

    current_tile: Tile = logic_map.chess_board[origin_piece.y][origin_piece.x + offsets[index]]

    if(not current_tile.is_occupied() and not is_attacked(logic_map, current_tile, origin_piece.color)):
      validator += 1
  


  new_valid_move: Tile = logic_map.chess_board[origin_piece.y][origin_piece.x + offsets[1]]
  if(validator == 2):
    moves.append((new_valid_move, ColorsTile.GREY))
    return validator - 1
  
  
  
  return 0



# Core function for all following rules : Check, Checkmate, Castle, Pin
def is_attacked(logical_map: Board, source_tile: Tile, source_color: ColorsPieces) -> bool:

  # source tile is whats being attacked << ! checking for that << !

  amount_of_pieces_attacking_this = 0
  constants.CURRENT_ATTACKER.clear()
  #Check each direction to see if a opposing color figure is attack this tile << !
  if(horizontal_or_vertical_is_attacked(logical_map, source_tile, source_color, -1, HORIZONTAL_STRING)): amount_of_pieces_attacking_this += 1
  elif(horizontal_or_vertical_is_attacked(logical_map, source_tile, source_color, 1, HORIZONTAL_STRING)): amount_of_pieces_attacking_this += 1
  elif(horizontal_or_vertical_is_attacked(logical_map, source_tile, source_color, -1, VERTICAL_STRING)): amount_of_pieces_attacking_this += 1
  elif(horizontal_or_vertical_is_attacked(logical_map, source_tile, source_color, 1, VERTICAL_STRING)): amount_of_pieces_attacking_this += 1
  elif(diagonal_is_attacked(logical_map, source_tile, source_color, DiagonalDirection.TOP_LEFT)): amount_of_pieces_attacking_this += 1
  elif(diagonal_is_attacked(logical_map, source_tile, source_color, DiagonalDirection.TOP_RIGHT)): amount_of_pieces_attacking_this += 1
  elif(diagonal_is_attacked(logical_map, source_tile, source_color, DiagonalDirection.DOWN_LEFT)): amount_of_pieces_attacking_this += 1
  elif(diagonal_is_attacked(logical_map, source_tile, source_color, DiagonalDirection.DOWN_RIGHT)): amount_of_pieces_attacking_this += 1
  elif(knight_is_attacking(logical_map, source_tile, source_color)): amount_of_pieces_attacking_this += 1
  elif(kings_is_attacking(logical_map, source_tile, source_color)): amount_of_pieces_attacking_this += 1  # << HERE IS THE THING ABOUT KINGS CHECK THIS OUT 

  if(source_color == ColorsPieces.WHITE):
    if(pawn_is_attacking(logical_map, source_tile, source_color, BLACK_PAWNS_ATTACKING_WHITE_OFFSET)): amount_of_pieces_attacking_this += 1
  else:
    if(pawn_is_attacking(logical_map, source_tile, source_color, WHITE_PAWNS_ATTACKING_BLACK_OFFSET)): amount_of_pieces_attacking_this += 1

  return amount_of_pieces_attacking_this


def horizontal_or_vertical_is_attacked(logical_map: Board, source_tile: Tile, source_color: ColorsPieces, offset: int, which_direction: str):

  if(which_direction == VERTICAL_STRING):
    iterator = source_tile.y
  elif(which_direction == HORIZONTAL_STRING):
    iterator = source_tile.x

  iterator += offset

  while constants.MAP_LOWER_BOUND <= iterator <= constants.MAP_UPPER_BOUND:


    if(which_direction == HORIZONTAL_STRING):
      current_tile: Tile = logical_map.chess_board[source_tile.y][iterator] # theres a bug when sending a queen and then opposite colors
      # because the queen is legit defending herself here << ! 
    elif(which_direction == VERTICAL_STRING):
      current_tile: Tile = logical_map.chess_board[iterator][source_tile.x]

    if(not current_tile.is_occupied()):
      iterator += offset
      continue

    placeholder_piece: Piece = current_tile.piece

    if((placeholder_piece.type == PieceType.QUEEN or placeholder_piece.type == PieceType.ROOK) and placeholder_piece.color != source_color):

      constants.CURRENT_ATTACKER.append(placeholder_piece)
      return True
    #elif(placeholder_piece.type == PieceType.KING):
    #  iterator += offset
    #  continue
    else:
      return False
    

  return False

def diagonal_is_attacked(logical_map: Board, source_tile: Tile, source_color: ColorsPieces, which_direction: DiagonalDirection):
  
  offset_x, offset_y = switch_for_diagonal_offsets(which_direction)

  iterator_x = source_tile.x + offset_x
  iterator_y = source_tile.y + offset_y # the old offsets fixed this << !
  
  #iterator_x = source_tile.x 
  #iterator_y = source_tile.y

  while constants.MAP_LOWER_BOUND <= iterator_x <= constants.MAP_UPPER_BOUND and constants.MAP_LOWER_BOUND <= iterator_y <= constants.MAP_UPPER_BOUND:
    
    current_tile: Tile = logical_map.chess_board[iterator_y][iterator_x]

    if(not current_tile.is_occupied()):
      iterator_x += offset_x
      iterator_y += offset_y
      continue

    placeholder_piece: Piece = current_tile.piece

    if((placeholder_piece.type == PieceType.QUEEN or placeholder_piece.type == PieceType.BISHOP)
    and placeholder_piece.color != source_color):
      
      constants.CURRENT_ATTACKER.append(placeholder_piece)
      return True
    #elif(placeholder_piece.type == PieceType.KING):
    #  iterator_x += offset_x
    #  iterator_y += offset_y
    #  continue
    else:
      return False

    
  return False

def knight_is_attacking(logical_map: Board, source_tile: Tile, source_color: ColorsPieces):
  iterator_x :int = source_tile.x
  iterator_y :int = source_tile.y

  for offset_x, offset_y in KNIGHT_VIABLE_MOVES_OFFSETS:
    iterator_x = source_tile.x
    iterator_y = source_tile.y

    iterator_y += offset_y
    iterator_x += offset_x

    if not isInsideOfBounds(iterator_x, iterator_y):
      continue

    current_tile: Tile = logical_map.chess_board[iterator_y][iterator_x]

    if(not current_tile.is_occupied()):
      continue

    placeholder_piece: Piece = current_tile.piece

    if(placeholder_piece.type == PieceType.KNIGHT and placeholder_piece.color != source_color):
      constants.CURRENT_ATTACKER.append(placeholder_piece)
      return True
    
  return False

def switch_for_diagonal_offsets(desired_direction: DiagonalDirection):

  match desired_direction:
    case DiagonalDirection.DOWN_LEFT:
      return (-1, 1)
    case DiagonalDirection.DOWN_RIGHT:
      return (1, 1)
    case DiagonalDirection.TOP_LEFT:
      return (-1, -1)
    case DiagonalDirection.TOP_RIGHT:
      return (1, -1)
    case _:
      return None
    
def pawn_is_attacking(logical_map: Board, source_tile: Tile, source_color: ColorsPieces, moves: List[Tuple[int ,int ]]):


  iterator_x = source_tile.x
  iterator_y = source_tile.y


  for offset_x, offset_y in moves:
    iterator_x = source_tile.x
    iterator_y = source_tile.y

    iterator_x += offset_x
    iterator_y += offset_y

    if(not isInsideOfBounds(iterator_x, iterator_y)):
      continue

    current_tile: Tile = logical_map.chess_board[iterator_y][iterator_x]

    if(not current_tile.is_occupied()):
      continue

    placeholder_piece: Piece = current_tile.piece
    if(placeholder_piece.color != source_color and placeholder_piece.type == PieceType.PAWN): 

      
      if(source_tile.is_occupied()):
        constants.CURRENT_ATTACKER.append(placeholder_piece)
        return True
      else:
        if(constants.KING_CALLING): # GAME SHOULD BE GOOD TO BE TESTED NOW << !
          constants.CURRENT_ATTACKER.append(placeholder_piece)
          return True
        else:
          continue
    
    

  return False

def kings_is_attacking(logical_map: Board, source_tile: Tile, source_color: ColorsPieces):
  
  iterator_x = source_tile.x
  iterator_y = source_tile.y

  for offset_x, offset_y in KING_VIABLE_MOVES_OFFSETS:
    iterator_x = source_tile.x
    iterator_y = source_tile.y

    iterator_x += offset_x
    iterator_y += offset_y

    if(not isInsideOfBounds(iterator_x, iterator_y)):
      continue
    
    current_tile: Tile = logical_map.chess_board[iterator_y][iterator_x]

    if(not current_tile.is_occupied()):
      continue

    placeholder_piece: Piece = current_tile.piece

    if(placeholder_piece.type == PieceType.KING and placeholder_piece.color != source_color):

      if(constants.KING_CALLING):
        constants.CURRENT_ATTACKER.append(placeholder_piece)
        return True
      else:
        if(quickCheckIfKingCanTakeThis(logical_map, source_tile, ColorsTile.GREEN, placeholder_piece)): #  Queen tile  
          constants.CURRENT_ATTACKER.append(placeholder_piece) # bug rises from here again
          return True
    

  return False

def quickCheckIfKingCanTakeThis(logical_map: Board, source_tile: Tile, source_color: ColorsTile, king: Piece):
  moves: List[Tuple[Tile, ColorsTile]] = []
  moves = king.getMoves(logical_map, king.x, king.y)

  return (source_tile, source_color) in moves
    








  

  

  

  







  





    

















