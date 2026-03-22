from ..constants import TileColors, TilePicturesKeys

class Tile:
  def __init__(self, color: TileColors, x: int, y: int):

    self.color_ = color
    self.x_ = x
    self.y_ = y
    self.key_ : TilePicturesKeys = None


    self.x_axis_: int = 0
    self.y_axis_: int = 0

    # A*

    self.parent_: Tile = None # used so we can reconstruct paths in A_star
    self.g_cost_: int = 0 # real costfrom start to current node
    self.h_cost_: int = 0 # estimated cost from current node to goal
    self.f_cost_: int = 0 # total score used to decide priority

    pass

  # Getters
  def getColor(self):
    return self.color_
  
  def getXCoord(self):
    return self.x_
  
  def getYCoord(self):
    return self.y_
  
  def getKeyForImage(self):
    return self.key_
  
  def getXAxis(self):
    return self.x_axis_
  
  def getYAxis(self):
    return self.y_axis_
  
  def getParent(self):
    return self.parent_
  
  def getGcost(self):
    return self.g_cost_
  
  def getFcost(self):
    return self.f_cost_
  
  def getHcost(self):
    return self.h_cost_
  

  

  # Setters
  
  def setKeyAndColor(self, color: TileColors):

    self.color_ = color

    if(self.color_ == TileColors.BLACK):
      self.key_ = TilePicturesKeys.BLACK_TILE

    elif(self.color_ == TileColors.GREEN):
      self.key_ = TilePicturesKeys.GREEN_TILE

    elif(self.color_ == TileColors.LIGHT_GREY):
      self.key_ = TilePicturesKeys.LIGHT_GREY_TILE

    elif(self.color_ == TileColors.RED):
      self.key_ = TilePicturesKeys.RED_TILE

    elif(self.color_ == TileColors.WHITE):
      self.key_ = TilePicturesKeys.WHITE_TILE

    elif(self.color_ == TileColors.LIGHT_GREEN):
      self.key_ = TilePicturesKeys.LIGHT_GREEN_TILE

  def setXAxis(self, x: int):
    self.x_axis_ = x

  def setYAxis(self, y: int):
    self.y_axis_ = y

  def setParent(self, new_parent: Tile):
    self.parent_ = new_parent
  
  def setGcost(self, new_cost: int):
    self.g_cost_ = new_cost
  
  def setFcost(self, new_cost: int):
    self.f_cost_ = new_cost
  
  def setHcost(self, new_cost: int):
    self.h_cost_ = new_cost

