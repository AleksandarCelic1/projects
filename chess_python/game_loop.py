import pygame






def gameLoop():

  program_running = True

  #cap fps
  last_frame = pygame.time.get_ticks()
  #pool events
  while program_running:

    frame_start = pygame.time.get_ticks()
    # Here coems delta time handling // calculation of it, if it was to be needed in this project
    last_frame = frame_start

    for event in pygame.event.get():
      if event.type == pygame.QUIT:
        program_running = False # This is when we exit via "X" of the window

      
      if event.type == pygame.MOUSEBUTTONDOWN:
        if event.button == 1 or event.button == 3: # 1 = left click 2 = middle clikc? i guess scroll 3 = right click
          button_x, button_y = event.pos

          # call dispatcher 
          # THERE WILL BE A GLOBAL IS A PIECE SELECTED THAT WILL BE ON AND OFF when playing << !

  #call controlFPS
        



  #logic
  #render

  pass










