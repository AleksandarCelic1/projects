from typing import TYPE_CHECKING, List, Tuple
from .tile import Tile
from .piece import Piece
from .constants import PieceType, ColorsPieces, PlayerID, ColorsTile, HashKeyForPictures
from .moveFunctions import isInsideOfBounds


if TYPE_CHECKING:
  from .board import Board


class Pawn(Piece):
  def __init__(self, piece_type : PieceType, color : ColorsPieces, x : int, y : int, player_id : PlayerID, key: HashKeyForPictures):
    super().__init__(piece_type, color, x, y, player_id, key)
    self.did_i_move_already = False # USED FOR GET MOVES, as it will be used to check if
    # one can jump for 2 fields << !
    # Super() calls the base class in our case Piece CTOR (constructor)


  def getMoves(self, logic_map: "Board", x: int, y: int):
    moves : List[Tuple[Tile, ColorsTile]] = []

    direction = 0 
    if(self.color == ColorsPieces.WHITE):
      direction = -1 # he is going up meaning his Y axis is going down
    else:
      direction = 1 # its black and its going down << !


    #Diagonal Captures << !
    array_of_x_offsets = []
    array_of_x_offsets.append(-1)
    array_of_x_offsets.append(1)

    for offset in array_of_x_offsets:

      diagonal_offset_x = x + offset
      diagonal_offset_y = y + direction

      if(not isInsideOfBounds(diagonal_offset_x, diagonal_offset_y)):
        continue

      current_tile : Tile = logic_map.chess_board[diagonal_offset_y][diagonal_offset_x]
      
      if(not current_tile.is_occupied()):
        continue
      else:

        opposing_figure : Piece = current_tile.piece

        if(opposing_figure.color == self.color):
          continue
        else:
          moves.append((current_tile, ColorsTile.GREEN))

    #Forward moves << !
    if(not isInsideOfBounds(x, y + direction)):
      return moves # does this work i didnt declare to return anything > ?
    
    tile_tile : Tile = logic_map.chess_board[y + direction][x]

    if(tile_tile.is_occupied()):
      return moves
    else:
      moves.append((tile_tile, ColorsTile.GREY))

      if(not isInsideOfBounds(x, y + direction + direction) or self.did_i_move_already):
        return moves
      
      two_sqares_infront_tile : Tile = logic_map.chess_board[y + direction + direction][x]

      if(two_sqares_infront_tile.is_occupied()):
        return moves
      else:
        moves.append((two_sqares_infront_tile, ColorsTile.GREY))
    
    return moves
    