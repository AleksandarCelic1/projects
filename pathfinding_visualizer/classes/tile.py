from constants import TileColors, TilePicturesKeys

class Tile:
  def __init__(self, color: TileColors, x: int, y: int, key: TilePicturesKeys):

    self.color_ = color
    self.x_ = x
    self.y_ = y
    self.key_ = key


    self.x_axis_: int = 0
    self.y_axis_: int = 0

    
    pass

  def getColor(self):
    return self.color_
  
  def getXCoord(self):
    return self.x_
  
  def getYCoord(self):
    return self.y_
  
  def getKeyForImage(self):
    return self.key_
  
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

  def setXAxis(self, x: int):
    self.x_axis_ = x

  def setYAxis(self, y: int):
    self.y_axis_ = y
