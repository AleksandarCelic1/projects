import pygame

from .classes.tools import Tools
from .constants import GameState

from .gameFunctions import controlFPS, dispatcher, calculateDeltaTime


def gameLoop(main_tools: Tools):

  running = True
  last_frame = pygame.time.get_ticks()
  delta_time: float = float(0)


  while running:

    frame_start = pygame.time.get_ticks()
    delta_time = calculateDeltaTime(frame_start, last_frame)
    last_frame = frame_start

    for event in pygame.event.get():
      if event.type == pygame.QUIT:
        running = False

      
      if (event.type == pygame.MOUSEBUTTONDOWN 
      and ( event.button == 1 or event.button == 3)):
        
        mouse_x, mouse_y = event.pos
        
        if(main_tools.getGameState() != GameState.BUSY):
          dispatcher(main_tools, mouse_x, mouse_y)
        else:
          pass
          #ignore


    # Logic << !

    

    # Rendering
    main_tools.getRendererFunctionContainer().renderUI(main_tools, delta_time)
    if(main_tools.getGameState() != GameState.BUSY):
      main_tools.getMatrixObject().renderTiles(main_tools.getRenderer())
      
    pygame.display.flip()


    # FPS
    controlFPS(frame_start)

    

    
    
