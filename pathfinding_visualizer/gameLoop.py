import pygame

from .classes.tools import Tools
from .constants import GameState


def gameLoop(main_tools: Tools):

  running = True

  while running:

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


    




    

    pygame.display.flip()

    
    
