from .piece import Piece
from typing import List, TYPE_CHECKING
from .constants import values_for_pieces, PlayerID

if(TYPE_CHECKING):
  from .tools import  Tools

import pygame

class Player:
  def __init__(self, player_id: PlayerID):
    self.graveyard : List[Piece] = []
    self.my_graveyard_changed: bool = False

    self.troops: List[Piece] = [] # USED FOR STALEMATE
    self.score = 0 # Keeping the score of all captured pieces
    self.player_id = player_id

    self.score_src: pygame.Surface = None
    self.score_rect: pygame.Rect = None
    
    
  def compute_score(self, main_tools: "Tools"):

    new_score = 0

    for index in range(len(self.graveyard)):
      new_score += values_for_pieces[self.graveyard[index].type]

    self.score = new_score

    self.score_src = main_tools.font.render(str(self.score), True, (255, 255, 255))
    self.score_rect = self.score_src.get_rect()

    if(self.player_id == PlayerID.PLAYER_ONE_WHITE):
      self.score_rect.x = main_tools.white_rect.x + main_tools.white_rect.w
      self.score_rect.y = main_tools.white_rect.y

      if((len(self.graveyard))):
        main_tools.player_black.troops.remove(self.graveyard[-1])
    else:
      self.score_rect.x = main_tools.black_rect.x + main_tools.black_rect.w
      self.score_rect.y = main_tools.black_rect.y

      if((len(self.graveyard))):
        main_tools.player_white.troops.remove(self.graveyard[-1])

    
     
      
