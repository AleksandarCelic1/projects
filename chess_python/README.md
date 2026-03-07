Chess in Python 

1. Implemented classes of All Pieces, Tiles, Board and etc. according to the OOP standards, as classes are much cleaner/ readable code 
(Tools class is treated as a Toolbox of a Handyman, everything he needs its inside)
(This is made to avoid making 15 different small classes but reather to keep some changeable bools inside, dont need a whole class for that)

2. Everything initialized in initialization.py, pictures fonts pieces board players etc.

3. UI is mostly rendered in Tools class and Pieces/Board/Linear Interpolation is rendered in Board

4. Gameloop handles all events (with dispatcher/specialDispatcher/validatingLastMove) according to the GameState

5. MoveFunctions are made to display all possible moves a piece can make when pressed on

6. IsAttacked is a function that checks if a source tile is attacked from anything from NOT source color -> meaning opposite colour

7. GameFunctions - as the name says they are functions for the whole game 
( Stalemate/Checkmate/PawnPromotion/LinearInterpolation/Calculation of delta time/dispatchers etc) handlers

8. Constants file, are just all enums constants and hash maps that map to pygame.Surface/pygame.Rect as those are used to render them

9. main calls all initialization function from initialization.py and then calls gameloop/event handler


###### LEFTOVER BUGS ######

- will find someone to test the program << ! >>
- and with that we'll see if anything needs repairs 