import pygame

from .initialization import initializeEverything
from .classes.tools import Tools



def main():
  pygame.init()

  tools: Tools = initializeEverything()


  pygame.quit()
if __name__ == "__main__":
  main()



