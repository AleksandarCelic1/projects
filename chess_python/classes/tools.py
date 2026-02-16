from .player import Player
from .constants import PlayerID
from .board import Board
from enum import Enum # enum is imported from enum and NOT from typing << !!
from .tile import Tile
from .piece import Piece
from typing import List

import pygame

class GameState(Enum):
  PERFORMING_LERP = 1,
  PLAYING = 2


class Tools:
  def __init__(self, player_one: Player, player_two: Player, wind_render: pygame.Surface):
    self.game_state : GameState = GameState.PLAYING
    self.player_white : Player = player_one
    self.player_black : Player = player_two
    self.player_playing : PlayerID = PlayerID.PLAYER_ONE_WHITE

    self.window_and_renderer : pygame.Surface = wind_render
    self.main_board: Board = None
    self.current_players_selected_tile: Tile = None
    self.current_players_target_tile: Tile = None 

    #BOOLEAN
    self.is_piece_selected = False
    self.move_taken = False
    self.was_graveyard_changed = False
    self.is_near_the_destination = False

    #Regarding font and score rendering
    self.white_src: pygame.Surface = None
    self.white_rect: pygame.Rect = None
    self.black_src: pygame.Surface = None
    self.black_rect: pygame.Rect = None

    self.font: pygame.font.Font = None

    #lerp 
    self.lerp_timer: float = 0.0
    self.is_animating: bool = False
    


  def renderScores(self):

    self.window_and_renderer.blit(self.black_src, self.black_rect)
    self.window_and_renderer.blit(self.white_src, self.white_rect)

    if(self.was_graveyard_changed):
      self.player_black.compute_score(self)
      self.player_white.compute_score(self)
      self.was_graveyard_changed = False

    self.window_and_renderer.blit(self.player_black.score_src, self.player_black.score_rect)
    self.window_and_renderer.blit(self.player_white.score_src, self.player_white.score_rect)

  def renderGraveyardPieces(self):
    graveyard_white: List[Piece] = self.player_white.graveyard
    graveyard_black: List[Piece] = self.player_black.graveyard

    white_x = self.player_white.score_rect.x + self.player_white.score.w
    white_y = self.player_white.score_rect.y


    for index in range(len(graveyard_white)):
      pass # tommorow 






  
  



    