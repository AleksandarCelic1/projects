import tile



class Board:
  def __init__(self, deque_of_pieces, size_width : int, size_height : int):
    
    self.chess_board = []

    remove_piece_this_iteration = True
    current_color = tile.piece.constants.ColorsTile.WHITE

    for y in range(size_height):
      row = [] # outer index // index // y in python you must make rows 

      for x in range(size_width):

        if y != 0 and y != 1 and y != 6 and y != 7:
          remove_piece_this_iteration = False


        if remove_piece_this_iteration == True:
          row.append(tile.Tile(current_color, deque_of_pieces.popLeft(), x, y))
        else:
          row.append(tile.Tile(current_color, None, x, y))

        if current_color == tile.piece.constants.ColorsTile.BLACK:
          current_color = tile.piece.constants.ColorsTile.WHITE
        else:  
          current_color = tile.piece.constants.ColorsTile.BLACK

        remove_piece_this_iteration = True

      self.chess_board.append(row)


  








