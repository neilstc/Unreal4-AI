# Unreal4-AI
a small part of a bigger project 

basically, 
Code:
1) Decorator - that checks if the bot can see other characters in the map (boolean).
2) Task - the player find some random location in the map.
3) Service - updating the player behavior by checking if he can see other players and telling him what to do.
4) AI Controller - class that the pawn implements, i defined there which perceptions i want him to have (sight),
   made an update that whenever there is a stimulus the bot will get the location vector, this way he will know where to go.
  

 Blueprints 
 
 Behaviour Tree - execute the actions that the bot needs to do depending on the blackboard parameter
 Blackboard - holding the parameters.
 
