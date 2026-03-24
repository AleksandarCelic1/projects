import pygame

from enum import Enum
from typing import List, Tuple

class TileColors(Enum):
  GREEN = 0
  RED = 1
  LIGHT_GREY = 2
  WHITE = 3
  BLACK = 4
  LIGHT_GREEN = 5

# Green indicates start point
# Red indicates end point
# Light Grey indicates all verticies visited by Algorithms
# White indicates unvisited
# Black indicates obstacle 


class AlgorithmKeys(Enum):
  BFS = 0
  DFS = 1
  DJIKSTRA = 2
  A_STAR = 3

# those are used in a main class named Tools as we are going to have a hash map that maps
# into our algorthim object that has a Run function << ! (if the signature can be valid for all of them -- pure virtual function)

class TilePicturesKeys(Enum):
  WHITE_TILE = 0
  BLACK_TILE = 1
  GREEN_TILE = 2
  RED_TILE = 3
  LIGHT_GREY_TILE = 4
  LIGHT_GREEN_TILE = 5

#Pretty self explanatory


class FontKeys(Enum):
  MINECRAFT_FONT_12 = 0
  MINECRAFT_FONT_16 = 1 # 16 indicating Size
  MINECRAFT_FONT_20 = 2
  MINECRAFT_FONT_24 = 3

class StringsAlgoEnums(Enum):
  BFS = "BFS"
  DFS = "DFS"
  A_STAR = "A*"
  DJIKSTRA = "Djikstra"

class StringsRunReset(Enum):
  RUN = "RUN"
  RESET = "RESET"

class StringsError(Enum):
  ERROR = "[ERROR]"
  YOU_ARE_MISSING = " -> You are missing:"
  MUST_RESET = " -> You must use reset button!"
  SOURCE_TILE = "Source Tile"
  TARGET_TILE = "Target Tile"
  CHOSEN_ALGO = "Algorithm"


   
class GameState(Enum):
  BUSY = 0 # indicating that a "algorithm" is drawing and cant take input 
  AVAILABLE = 1 # can take input 
  FIRST_MOVE_MADE = 2 # indicating source tile is given
  SECOND_MOVE_MADE = 3 # indicating target tile is given
  MUST_USE_BRUSH = 4 # after algo is finished you have to clean





ONE_SECOND = 1000
FPS = 60
FRAME_DELAY = ONE_SECOND // FPS
#FPS handling

SCREEN_WIDTH = 1200
SCREEN_HEIGHT = 900
PADDING_FOR_EVERY_SIDE = 20

# Screen Dimensions

MATRIX_WIDTH = 50
MATRIX_HEIGHT = 50

MATIRX_WIDTH_PIXELS = 800
MATRIX_HEIGHT_PIXELS = 800

MATRIX_X_POSITION = SCREEN_WIDTH - MATIRX_WIDTH_PIXELS - PADDING_FOR_EVERY_SIDE
MATRIX_Y_POSITION = SCREEN_HEIGHT - MATRIX_HEIGHT_PIXELS - PADDING_FOR_EVERY_SIDE
# The board will be N x N // logically yes but for rendering we have to still decide SCRRENWIDTH AND SCREEENHEIGHT

TILE_WIDTH_AND_HEIGHT = 16 # ? figure out the dimensions << !
SCALING_FACTOR_TWO = 2


hash_map_for_tile_pictures: dict[TilePicturesKeys, pygame.Surface] = {}
hash_map_for_text: dict[StringsRunReset, Tuple[pygame.Surface, pygame.Rect]] = { }
hash_map_for_errors: dict[StringsError, Tuple[pygame.Surface, pygame.Rect]] = { }
