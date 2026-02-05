from abc import ABC, abstractmethod
import constants


class Piece(ABC):
    
    def __init__(self, piece_type : constants.PieceType, color : constants.ColorsPieces, x, y):
        
        self.type = piece_type
        self.color = color
        self.x = x
        self.y = y

    @abstractmethod
    def getMoves(self, logic_map, x, y):
        pass
    
        
        
        