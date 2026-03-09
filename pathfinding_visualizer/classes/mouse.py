
class Mouse():
  def __init__(self, x: int, y:int):
    self.clicked_x_axis_ = 0
    self.clicked_y_axis_ = 0

    self.setXAxis(x)
    self.setYAxis(y)

  def getXAxis(self):
    return self.clicked_x_axis_
  
  def getYAxis(self):
    return self.clicked_y_axis_
  
  def setXAxis(self, new_x: int):
    self.clicked_x_axis_ = new_x
  
  def setYAxis(self, new_y: int):
    self.clicked_y_axis_ = new_y
