# Game Design
Drakkar is a multiplayer game featuring dragons of different colours trying to chase and eat one another.
The game resembles [agar.io](https://agar.io/) with the addition of a Rock-Paper-Scissor dynamic via the RGB colours.

## General Principle
There are three players. Each player controls a disc-shaped dragon of one of three colours: red, green, and blue.
Every colour is strong against another one and weak against the third one. 
Players chase one another, trying to run into and eat the weaker player while evading the stronger player.

### Interactions
A player running into another one triggers a collision. 
Upon a collision, the colour of the involved dragons is compared, and the dragon with the strongest colour wins, according to the following Rock-Paper-Scissor logic:

- Red is strong against Green, and weak against Blue;
- Green is strong against Blue, and weak against Red;
- Blue is strong against Red, and weak against Green.

The winning dragon then munches on the losing one, growing a bit in the process, while the loser shrinks a bit.
The loser then turns invulnerable for a short duration, so that it has a chance to escape its victor and avoid being munched on indefinitely.
During this time, the invulnerable dragon cannot be involved in a collision with another player (it simply ignores them as it runs into them).

### Winning condition
The game is timed; when the timer runs out, whichever player has the largest dragon wins the game.
In the event of a tie, the winner is decided on a coin flip among the tied players.

### Environment
Players can move and interact within a rectangular environment. The environment has hard boundaries: players cannot move beyond these boundaries.
Otherwise, players can move freely, there are no obstacles other than other players within the environment.

### Player movement
Players can move forward by pressing a key, immediately moving in the direction that the nose of the dragon points towards.
A player can also move backwards, going in the opposite direction to the forward one.
To change direction, a player can pivot left or right with dedicated keys.
Movement is immediate: when a movement key is pressed, the player moves accordingly; when a movement key is released, the player stops moving.

