import pygame

from .classes.tools import Tools
from .constants import GameState

from .gameFunctions import controlFPS


def gameLoop(main_tools: Tools):

  running = True
  last_frame = pygame.time.get_ticks()


  while running:

    frame_start = pygame.time.get_ticks()
    last_frame = frame_start

    for event in pygame.event.get():
      if event.type == pygame.QUIT:
        running = False

      
      if (event.type == pygame.MOUSEBUTTONDOWN 
      and ( event.button == 1 or event.button == 3)):
        
        if(main_tools.getGameState() == GameState.AVAILABLE):
          pass
          # call dispatcher
        else:
          pass
          #ignore


    # Logic << !

    

    # Rendering
    main_tools.getRendererFunctionContainer().renderUI(main_tools.getRenderer())
    main_tools.getMatrixObject().renderTiles()
    pygame.display.flip()


    # FPS
    controlFPS(frame_start)

    

    
    
