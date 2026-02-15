from .classes import constants
from .gameFunctions import dispatcher, controlFPS, validatingLastMove
from .classes.board import Board
from .classes.tools import Tools, GameState

import pygame



def gameLoop(main_tools: Tools):

  program_running = True


  last_frame = pygame.time.get_ticks()
  while program_running:

    frame_start = pygame.time.get_ticks()
    last_frame = frame_start

    for event in pygame.event.get():
      if event.type == pygame.QUIT:
        program_running = False # This is when we exit via "X" of the window

      
      if event.type == pygame.MOUSEBUTTONDOWN and main_tools.game_state == GameState.PLAYING:
        if event.button == 1 or event.button == 3: # 1 = left click 2 = middle clikc? i guess scroll 3 = right click
          button_x, button_y = event.pos

          legal_moves = dispatcher(main_tools, button_x, button_y, main_tools.player_playing)
          

          if(main_tools.move_taken):
            validatingLastMove(main_tools, legal_moves)
            # logic func to check if its a valid more
      else:
        continue


  
    #logic

    #render
    main_tools.main_board.print_background(main_tools.window_and_renderer)
    main_tools.main_board.print_pieces(main_tools.window_and_renderer)

    if(main_tools.is_piece_selected and not main_tools.move_taken):
      main_tools.main_board.print_legal_moves(main_tools.window_and_renderer, legal_moves)

    if(main_tools.game_state == GameState.PERFORMING_LERP):
      pass
      #call function that will render LERP and complete the engine where when finished the player playing is changed and gamestate is updated
      # as we alreadt take no input while its lerping 

    pygame.display.flip() # this "presents" what we drew 


    # handle FPS
    controlFPS(frame_start)

  










