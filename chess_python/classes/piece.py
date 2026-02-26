from abc import ABC, abstractmethod
from typing import TYPE_CHECKING
from .constants import PieceType, ColorsPieces, PlayerID, HashKeyForPictures

if TYPE_CHECKING:
    from .board import Board


class Piece(ABC):
    
    def __init__(self, piece_type : PieceType, color : ColorsPieces, x : int, y : int, player_id : PlayerID, hash_key: HashKeyForPictures):
        
        self.type = piece_type
        self.color = color
        self.can_move = True

        # Moving
        self.did_i_move_already = False

        #indexes
        self.x = x 
        self.y = y

        #axes regarding rendering
        self.x_axis = 0
        self.y_axis = 0
        # thinking about using this so next time im eating some piece i can use axes to perfrom LERP ( linear interpolation )

        self.hash_key = hash_key

        self.player_id = player_id
        self.is_protected = False
        self.should_be_captured = False # This is intended to be True only when its taken so we can render easier using this variable

    @abstractmethod
    def getMoves(self, logic_map: "Board", x: int, y: int):
        pass
    
        
        
        