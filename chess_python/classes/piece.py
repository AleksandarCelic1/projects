from abc import ABC, abstractmethod
import constants


class Piece(ABC):
    
    def __init__(self, piece_type : constants.PieceType, color : constants.ColorsPieces, x : int, y : int, player_id : constants.PlayerID):
        
        self.type = piece_type
        self.color = color
        self.can_move = True
        self.x = x
        self.y = y
        self.player_id = player_id
        self.is_protected = False

    @abstractmethod
    def getMoves(self, logic_map, x, y):
        pass
    
        
        
        