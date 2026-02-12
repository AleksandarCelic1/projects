#make game dispatcher for x,y of mouse to get what piece shall be moved 

def dispatcher(mouse_x: int, mouse_y: int):
  pass

# dispatcher should calculate according to the x and y which column and row was pressed on the chess tables if its not within the bounds
# drop it, if yes get that tile from the board and check if its occupied if yes call the getMoves() from that piece and change its "is_selected" to true
# if its not already done within the function, and when we get the moves back we shall return this and render it and when another mousebutton down is selected 
# this one shall not be selected anymore.