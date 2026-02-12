import pygame

FPS = 60
FRAME_DELAY = 1000 / FPS




def gameLoop():

  program_running = True

  #cap fps
  #pool events
  while program_running:

    for event in pygame.event.get():
      if event.type == pygame.QUIT:
        program_running = False # This is when we exit via "X" of the window

      
      if event.type == pygame.MOUSEBUTTONDOWN:
        if event.button == 1 or event.button == 3: # 1 = left click 2 = middle clikc? i guess scroll 3 = right click
          button_x, button_y = event.pos

          # call dispatcher 
          # THERE WILL BE A GLOBAL IS A PIECE SELECTED THAT WILL BE ON AND OFF when playing << !

        



  #logic
  #render

  pass








