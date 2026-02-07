from abc import ABC, abstractmethod
from typing import TYPE_CHECKING
from .constants import PieceType, ColorsPieces, PlayerID

if TYPE_CHECKING:
    from .board import Board


class Piece(ABC):
    
    def __init__(self, piece_type : PieceType, color : ColorsPieces, x : int, y : int, player_id : PlayerID):
        
        self.type = piece_type
        self.color = color
        self.can_move = True
        self.x = x
        self.y = y
        self.player_id = player_id
        self.is_protected = False

    @abstractmethod
    def getMoves(self, logic_map: "Board", x: int, y: int):
        pass
    
        
        
        