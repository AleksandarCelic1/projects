import pygame
from initialization import initAllImages, initializingAllPieces, initializingBoard, initializingWindowAndRenderer


def main():
  pygame.init() #Only once is sufficient, from here I will call all other init functions


  # Init - of all necessary things << !
  initAllImages()
  dq_of_all_pieces = initializingAllPieces()
  main_window_and_renderer = initializingWindowAndRenderer()
  initializingBoard(dq_of_all_pieces)

  




  #pygame.display.quit() this maybe fixes some problems if we ever encounter one << !
  pygame.quit()




