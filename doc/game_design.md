# Game Design
Drakkar is a multiplayer game featuring dragons of different colours trying to chase and eat one another.
The game resembles [agar.io](https://agar.io/) with the addition of a Rock-Paper-Scissor dynamic via the RGB colours.

The goals and rules of the game are described here. We aim to make the design described in this doc come to life, and should refrain from working on things that do not fall in its scope. Any new feature or idea should be discussed first, then if received positively should be included in the design doc. 

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
During this time, the invulnerable dragon cannot be involved in a collision with the stronger player (it simply ignores it as it runs into it), but can still collide with the weaker player.

### Winning condition
The game is timed; when the timer runs out, whichever player has the largest dragon wins the game.
In the event of a tie, the winner is decided on a coin flip among the tied players.

### Death and size limitations
As described above, players change size upon interaction with other players.
When a player falls under a certain size, it "dies". 
While dead, the player cannot interact with either of the other players (and so ignores collisions).
After some time, the player is revived, upon which it returns to its starting size and can interact with other players again.

There is also an upper limit to the size a player can reach, so it does not inflate to occupy the whole environment and automatically trigger collisions with other players.

Players progressively shrink over time, as an incentive to avoid players simply sitting around and waiting for the timer to run out after having reached a winning size.

### Environment
Players can move and interact within a rectangular environment. The environment has hard boundaries: players cannot move beyond these boundaries.
Otherwise, players can move freely, there are no obstacles other than other players within the environment.

### Player movement
Players can move forward by pressing a key, immediately moving in the direction that the nose of the dragon points towards.
A player can also move backwards, going in the opposite direction to the forward one.
To change direction, a player can pivot left or right with dedicated keys.

Movement is immediate: when a movement key is pressed, the player moves accordingly; when a movement key is released, the player stops moving.

