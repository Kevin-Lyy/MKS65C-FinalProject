# MKS65C-FinalProject
## Tic tac toe on a server
## Group 73 - Jack Lu, Kevin Ly

It is a game of tic tac toe played on a server, you login or create a new account and are given a list of active opponents to pick from to challenge.

The game plays like regular tic tac toe.

## Instructions to run
Open 3 terminals <br />
Compile with make <br />
run ./server <br />
run ./client followed by the server's IP address if connecting across a network for player 1 <br />
run ./client followed by the server's IP address if connecting across a network for player 2 <br />
Login or create a new account <br />

## DEVLOG
Kevin <br />
1/7/19 <br />
I coded Tic tac toe, both players play on the same terminal, all ways of winning worked, players could tie and could not place their piece on a taken spot <br />
1/8/19 <br />
Continued with the login aspect of the project, it could take in a username and password but did not display other users <br />
1/9/19 <br />
Fixed display of other players but ran into a bug where a loop would keep prompting <br />
1/11/19 <br />
Fixed loop, login complete, it takes a username, password, displays other uses but did not allow you to choose one yet <br />
1/14/19 <br />
Added comments in Tic Tac Toe for partner <br />

Jack <br />
1/13/19  
Added user login and selecting opponent functionality for network

1/14/19 <br />
Implemented communication between two clients, alternating in turns. <br>
Failed to integrate tic tac toe game into the client-server network.

1/15/19 <br />
Integrated tic tac toe game into client-server network

## Bugs
After 2 players win and disconnect the server does not remove them from the online.txt file
Selecting a player that has disconnected will result in an error.
