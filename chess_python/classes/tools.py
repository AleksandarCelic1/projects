from .player import Player
from .constants import PlayerID
from .board import Board
from enum import Enum # enum is imported from enum and NOT from typing << !!
from .tile import Tile

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

    self.is_piece_selected = False
    self.move_taken = False
  
  



    