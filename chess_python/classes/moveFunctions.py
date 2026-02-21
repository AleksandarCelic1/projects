from .board import Board
from .tile import Tile
from . import constants
from .constants import ColorsTile, ColorsPieces, PieceType, HORIZONTAL_STRING, VERTICAL_STRING, DiagonalDirection
from typing import List, Tuple
from .piece import Piece


KNIGHT_VIABLE_MOVES_OFFSETS= {  (-1, -2), (1, -2), (2, -1), (2, 1), (-2, -1), (-2, 1), (-1, 2), (1, 2)}
KING_VIABLE_MOVES_OFFSETS = { (-1, -1), (0, -1), (1, -1), (-1, 0), (1, 0), (-1, 1), (0, 1), (1, 1)}
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

def kingViableMoves(logical_map: Board, x: int, y: int, moves: List[Tuple[Tile, ColorsTile]], origin: Tile, total_legal_moves: int):
  
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
          protected = is_attacked(logical_map, current_tile, origin.piece.color)
          
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

# Core function for all following rules : Check, Checkmate, Castle, Pin
def is_attacked(logical_map: Board, source_tile: Tile, source_color: ColorsPieces) -> bool:
  
  amount_of_pieces_attacking_this = 0
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
  elif(kings_is_attacking(logical_map, source_tile, source_color)): amount_of_pieces_attacking_this += 1

  if(source_color == ColorsPieces.WHITE):
    if(pawn_is_attacking(logical_map, source_tile, source_color, BLACK_PAWNS_ATTACKING_WHITE_OFFSET)): amount_of_pieces_attacking_this += 1
  else:
    if(pawn_is_attacking(logical_map, source_tile, source_color, WHITE_PAWNS_ATTACKING_BLACK_OFFSET)): amount_of_pieces_attacking_this += 1

  return amount_of_pieces_attacking_this


def horizontal_or_vertical_is_attacked(logical_map: Board, source_tile: Tile, source_color: ColorsPieces, offset: int, which_direction: str):

  if(which_direction == VERTICAL_STRING):
    iterator = source_tile.y + offset
  elif(which_direction == HORIZONTAL_STRING):
    iterator = source_tile.x + offset


  while constants.MAP_LOWER_BOUND <= iterator <= constants.MAP_UPPER_BOUND:

    if(which_direction == HORIZONTAL_STRING):
      current_tile: Tile = logical_map.chess_board[source_tile.y][iterator]
    elif(which_direction == VERTICAL_STRING):
      current_tile: Tile = logical_map.chess_board[iterator][source_tile.x]

    if(not current_tile.is_occupied()):
      iterator += offset
      continue

    placeholder_piece: Piece = current_tile.piece

    if((placeholder_piece.type == PieceType.QUEEN or placeholder_piece.type == PieceType.ROOK) and placeholder_piece.color != source_color):
      return True
    else:
      return False
    

  return False

def diagonal_is_attacked(logical_map: Board, source_tile: Tile, source_color: ColorsPieces, which_direction: DiagonalDirection):
  
  offset_x, offset_y = switch_for_diagonal_offsets(which_direction)

  iterator_x = source_tile.x + offset_x
  iterator_y = source_tile.y + offset_y

  while constants.MAP_LOWER_BOUND <= iterator_x <= constants.MAP_UPPER_BOUND and constants.MAP_LOWER_BOUND <= iterator_y <= constants.MAP_UPPER_BOUND:
    
    current_tile: Tile = logical_map.chess_board[iterator_y][iterator_x]

    if(not current_tile.is_occupied()):
      iterator_x += offset_x
      iterator_y += offset_y
      continue

    placeholder_piece: Piece = current_tile.piece

    if((placeholder_piece.type == PieceType.QUEEN or placeholder_piece.type == PieceType.BISHOP)
    and placeholder_piece.color != source_color):
      return True
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

    placeholder_pawn: Piece = current_tile.piece

    if(placeholder_pawn.type == PieceType.KNIGHT and placeholder_pawn.color != source_color):
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
      print('usro sam se << !')
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
      return True
    

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
      return True
    

  return False








  

  

  

  







  





    

















