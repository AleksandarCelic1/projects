import pygame
from .initialization import initAllImages, initializingAllPieces, initializingBoard, initPlayersAndTools, initFontAndSurfacesForScores, initAxisForAllPieces
from .game_loop import gameLoop



def main():
  pygame.init() #Only once is sufficient, from here I will call all other init functions

  # Init - of all necessary things << !
  dq_of_all_pieces = initializingAllPieces()
  placeholder = initializingBoard(dq_of_all_pieces)

  main_tools = initPlayersAndTools()
  main_tools.main_board = placeholder
  initAllImages()
  initFontAndSurfacesForScores(main_tools)
  initAxisForAllPieces(main_tools)
  




  #jump to event handler << !
  gameLoop(main_tools)


  #pygame.display.quit() this maybe fixes some problems if we ever encounter one << !
  pygame.quit()

if __name__ == "__main__":
  main()



