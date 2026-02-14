import pygame
from initialization import initAllImages, initializingAllPieces, initializingBoard, initializingWindowAndRenderer, initPlayersAndTools
from .game_loop import gameLoop



def main():
  pygame.init() #Only once is sufficient, from here I will call all other init functions

  # Init - of all necessary things << !
  initAllImages()
  dq_of_all_pieces = initializingAllPieces()
  placeholder = initializingBoard(dq_of_all_pieces)

  main_tools = initPlayersAndTools()
  main_tools.chess_board = placeholder




  #jump to event handler << !
  gameLoop(main_tools)






  #pygame.display.quit() this maybe fixes some problems if we ever encounter one << !
  pygame.quit()




