from .classes.constants import PlayerID, MOVE_TAKEN, IS_A_PIECE_SELECTED
from .gameFunctions import dispatcher, controlFPS
from .classes.board import Board

import pygame



def gameLoop(main_renderer_and_window: pygame.Surface, main_board: Board):

  global MOVE_TAKEN
  player_playing = PlayerID.PLAYER_ONE_WHITE
  program_running = True


  last_frame = pygame.time.get_ticks()
  while program_running:

    frame_start = pygame.time.get_ticks()
    last_frame = frame_start

    for event in pygame.event.get():
      if event.type == pygame.QUIT:
        program_running = False # This is when we exit via "X" of the window

      
      if event.type == pygame.MOUSEBUTTONDOWN:
        if event.button == 1 or event.button == 3: # 1 = left click 2 = middle clikc? i guess scroll 3 = right click
          button_x, button_y = event.pos

          legal_moves = dispatcher(main_board, button_x, button_y, player_playing)

          if(MOVE_TAKEN):
            pass
            # logic func to check if its a valid more
          


          # call dispatcher 
          # THERE WILL BE A GLOBAL IS A PIECE SELECTED THAT WILL BE ON AND OFF when playing << !

  
  #logic

  #render
  main_board.print_background(main_renderer_and_window)
  main_board.print_pieces(main_renderer_and_window)

  if(IS_A_PIECE_SELECTED and not MOVE_TAKEN):
    main_board.print_legal_moves(main_renderer_and_window, legal_moves)



  # handle FPS
  controlFPS(frame_start)

  



  pass










