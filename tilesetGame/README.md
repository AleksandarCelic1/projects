# Knight: The Orc Slayer

# Tech Stack
  - C++
  - SDL2

Textures used are from public website

## Features Introduced:
  - 5 Levels
    - Ascension via Ladder
    - Between Each level, is a shop
    - Cant ascend to next level if all Enemies aren't cleared
  - Shop
    - Run by Shopkeeper
    - Separate UI for Shop
      - Can Buy/Sell things
  - Inventory
    - Separate UI for Inventory
    - Armory
      - Rings (Increases Max Health Points)
        - Ruby Ring 
        - Sapphire Ring 
        - Golden Sapphire Ring
      - Trinkets (Increases Special Ability Damage and Healing)
        - Ruby Trinket
        - Sapphire Trinket
        - Gold Ruby Trinket
      - Swords (Increases Attack Points/Power)
        - Stone Sword
        - Gold Sword
        - Big Gold Sword
    - 35 Inventory Slots in 2 Dimensions ( 7 X 5 )
  - Enemies (Orc)
    - Ascending Difficulty, every odd level
    - Boss
      - 3 attacking animations
    - Breadth First Search Pathfinding
    - Vision (Player Detection System)
    - Drops loot on kill
  - Player
    - Attributes (Stats)
      - Max Health Points
      - Attack Points
      - Coins (in-game money)
    - Special Attack
      - Earthquake
        - Can be performed when not on Cooldown
        - Cooldown is reseted according to global delta time
        - Is Usable when the Hourglass is steady
  - Movement
    - Player/Enemy traverses using Linear Interpolation
  - Screens
    - Transistion between Screens and Gameplay
      - Introduction 
      - Game-Over
      - You-Win
  - Traps (From Walls)
    - Shooting Arrow
    - Flamethrower
  - Traps (from Ground)
    - Needles
  - Box
    - Drops certain Loot according to Boxex Quality
      - Wood Small
      - Wood Big
      - Iron Small
      - Iron Big
  - Chest
    - Drops certain Loot according to Chest's Quality
      - Big Chest
      - Mini Chest
  - Doors
    - Requires key to unlock, except on first level
  - Keys
    - Silver Key
      - unlocks Vertical Doors
    - Gold Key
      - unlocks Horizontal Doors
  - Controls
    - Using TAB
      - Opens Control Menu
    - WASD / Arrows
      - Movement
    - Enter
      - Used to open 
        - Doors
      - Used to ascend
        - Level
    - K
      - Special Ability 
    - E 
      - Inventory
  - Animations
    - Updated with Delta Time
    - Map Objects
      - Idle 
        - Traps
        - Torches
        - Lights
        - Banners
        - Chests
        - Boxes
        - Keys
    - Enemies / Player
      - Idle
      - Death
      - Walking
      - Attacking
      - Special Attack
        - Boss has them, regular enemy doesn't
      - Hurt / Taking Damage
  - Consumables
    - Potion
      - Restores Health
    - Mushroom
      - Loses Health
  - Decorations
    - Big Cobweb
    - Small Cobweb
    - Chains
    - Different Floor Textures
    - Skulls 
    - Bones
  - Framerate
    - Capped to 60
  
  
  

  
    
    

 