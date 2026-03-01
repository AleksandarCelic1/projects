from .player import Player
from .constants import PlayerID, hash_map_for_graveyard_pictures, hash_map_for_scores_and_text, RenderingTextEnums
from .board import Board
from enum import Enum # enum is imported from enum and NOT from typing << !!
from .tile import Tile
from .piece import Piece
from typing import List
from .king import King

import pygame

class GameState(Enum):
  PERFORMING_LERP = 1,
  PLAYING = 2,
  CHECK = 3
  CHECKMATE = 4


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

    # Pawn Promotion

    self.pawn_being_promoted = False
    self.alpha_for_dimming_the_brightness = 140

    #Castle

    self.castle_being_performed = False
    self.which_rook = 0 # we would essentially just pass the X and then we can see 
    
    #Check / Checkmate

    self.black_king: King = None
    self.white_king: King = None

    #Win
    self.player_who_won: PlayerID = None

    #Regarding font and score rendering
    self.white_src: pygame.Surface = None
    self.white_rect: pygame.Rect = None
    self.black_src: pygame.Surface = None
    self.black_rect: pygame.Rect = None

    self.font: pygame.font.Font = None
    
  def renderScores(self):

    self.window_and_renderer.blit(self.black_src, self.black_rect)
    self.window_and_renderer.blit(self.white_src, self.white_rect)

    if(self.was_graveyard_changed):
      self.player_black.compute_score(self)
      self.player_white.compute_score(self)
      self.was_graveyard_changed = False

    self.window_and_renderer.blit(self.player_black.score_src, self.player_black.score_rect)
    self.window_and_renderer.blit(self.player_white.score_src, self.player_white.score_rect)


  def renderPlayerPlaying(self):

    self.window_and_renderer.blit(hash_map_for_scores_and_text[RenderingTextEnums.PLAYER_PLAYING_TEXT][0], hash_map_for_scores_and_text[RenderingTextEnums.PLAYER_PLAYING_TEXT][1])
    if(self.player_playing == PlayerID.PLAYER_ONE_WHITE):
      self.window_and_renderer.blit(hash_map_for_scores_and_text[RenderingTextEnums.WHITE_TEXT][0], hash_map_for_scores_and_text[RenderingTextEnums.WHITE_TEXT][1])
    else:
      self.window_and_renderer.blit(hash_map_for_scores_and_text[RenderingTextEnums.BLACK_TEXT][0], hash_map_for_scores_and_text[RenderingTextEnums.BLACK_TEXT][1])


  def renderGamestateStatus(self):
    self.window_and_renderer.blit(hash_map_for_scores_and_text[RenderingTextEnums.GAME_STATE_TEXT][0], hash_map_for_scores_and_text[RenderingTextEnums.GAME_STATE_TEXT][1])
    if(self.game_state == GameState.PLAYING or self.game_state == GameState.PERFORMING_LERP):
      self.window_and_renderer.blit(hash_map_for_scores_and_text[RenderingTextEnums.GAME_STATE_PLAYING][0], hash_map_for_scores_and_text[RenderingTextEnums.GAME_STATE_PLAYING][1])
    elif(self.game_state == GameState.CHECK):
      self.window_and_renderer.blit(hash_map_for_scores_and_text[RenderingTextEnums.GAME_STATE_CHECK][0], hash_map_for_scores_and_text[RenderingTextEnums.GAME_STATE_CHECK][1])
    elif(self.game_state == GameState.CHECKMATE):
      
      if(self.player_who_won == PlayerID.PLAYER_ONE_WHITE):
        self.window_and_renderer.blit(hash_map_for_scores_and_text[RenderingTextEnums.CHECK_MATE_WHITE][0], hash_map_for_scores_and_text[RenderingTextEnums.CHECK_MATE_WHITE][1])
      else:
        self.window_and_renderer.blit(hash_map_for_scores_and_text[RenderingTextEnums.CHECK_MATE_BLACK][0], hash_map_for_scores_and_text[RenderingTextEnums.CHECK_MATE_BLACK][1])


  def renderGraveyardPieces(self):
    graveyard_white: List[Piece] = self.player_white.graveyard
    graveyard_black: List[Piece] = self.player_black.graveyard

    white_x = self.player_white.score_rect.x + self.player_white.score_rect.w
    white_y = self.player_white.score_rect.y

    black_x = self.player_black.score_rect.x + self.player_black.score_rect.w
    black_y = self.player_black.score_rect.y

    iterator = 0

    for index in range(len(graveyard_white)):
      iterator = white_y
      iterator -= (hash_map_for_graveyard_pictures[graveyard_white[index].hash_key].get_rect().h) / 2
      self.window_and_renderer.blit(hash_map_for_graveyard_pictures[graveyard_white[index].hash_key], (white_x, iterator))
      white_x += hash_map_for_graveyard_pictures[graveyard_white[index].hash_key].get_width()

    for inner in range(len(graveyard_black)):
      iterator = black_y
      iterator -= (hash_map_for_graveyard_pictures[graveyard_black[inner].hash_key].get_rect().h) / 2
      self.window_and_renderer.blit(hash_map_for_graveyard_pictures[graveyard_black[inner].hash_key], (black_x, iterator))
      black_x += hash_map_for_graveyard_pictures[graveyard_black[inner].hash_key].get_width()
    
  def renderPawnPromotionUI(self):

    dim = pygame.Surface(self.window_and_renderer.get_size(), pygame.SRCALPHA)
    
    dim.fill((0, 0, 0, self.alpha_for_dimming_the_brightness))
    self.window_and_renderer.blit(dim, (0, 0))






  
  



    