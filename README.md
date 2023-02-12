## C-game-logic

this is some simple game implementation. The program takes a file with current info as input, performs a logic and 
writes the result to the output file.


## Input:

 1. The number N (1≤N≤10) - the number of teams in the game
 2. N lines, each containing a unique magician name. Each of those magician names should correspond to the team number from 0 till N−1, which was chosen by this team to become the head of the club.
 3. The number of players M
 4. M * 4 lines, each represents a player *i* information:
    - the unique name of player *i*
    - team number of the player *t_i* (0 ≤ *t_i* < N)
    - the power of the player *p_i* (0 ≤ *p_i* ≤1000)
    - the visibility of the player
 5. sequence of actions for players *S* (1 ≤ S ≤ 1000) followed on the same line by 1 or 2 player names separated by single spaces. Not each player is guaranteed to have actions.    


## The rules are the following: 

### - *attack name_i name_j*

      - if p_i > p_j, then player_i will gain p_i − p_j power and player_j will have no power left and further will be called frozen.
      - if p_i < p_j, then player_i will be frozen and player_j will gain p_j − p_i power.
      - if p_i = p_j, then both players will be frozen.
      - if player_j is not visible, then the player_i will be frozen.


### - *flip visibility name_i*

flip the status of the visibility of the *player_i*.


### - *heal name_i name_j* 
 
  make *player_i* give half (ceil the numbers up for both players if needed) of his power to *player_j* (from the same team).
  
  
### - *super name_i name_j* 

  create a super player instead of existing 2 players (from the same team) with joint power and actions.
  
  
  A frozen player can be healed, then this player will be unfrozen. A player with visibility equal to **False** can be healed. 
  A frozen *player_j* can be in the action in *super name_i name_j*. 
  A *player_j* with visibility equal to False can be in the action in *super name_i name_j*.
  
  
  
  
  
  ## Output:
  
   the message: "The chosen wizard is #team's_wizard" (the wizard of the team which has the greatest power left which is the sum of all the team members' powers). 
   
   If more than 1 team has the greatest power the output file contains a different message, which is: "It's a tie".
