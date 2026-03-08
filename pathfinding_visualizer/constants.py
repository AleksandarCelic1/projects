from enum import Enum

class TileColors(Enum):
  GREEN = 0
  RED = 1
  LIGHT_GREY = 2
  WHITE = 3
  BLACK = 4

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
  