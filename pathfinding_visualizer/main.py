import pygame

from .initialization import initializeEverything
from .classes.tools import Tools
from .gameLoop import gameLoop



def main():
  pygame.init()

  tools: Tools = initializeEverything()

  gameLoop(tools)


  pygame.quit()


  
if __name__ == "__main__":
  main()



