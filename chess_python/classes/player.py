from .piece import Piece
from typing import List
from .constants import values_for_pieces, PlayerID

class Player:
  def __init__(self, player_id: PlayerID):
    self.graveyard : List[Piece] = []
    self.score = 0 # Keeping the score of all captured pieces
    self.player_id = player_id
    
  def compute_score(self):

    new_score = 0

    for index in range(len(self.graveyard)):
      new_score += values_for_pieces[self.graveyard[index].type]

    self.score = new_score
  
      
