# BOULDER DASH

Boulder Dash is played on a rectangular board, the fields of which are organized in rows and columns. The player controls the Rockford character. The goal is to collect all the diamonds that are on the board and leave it through the exit. In addition to Rockford, diamonds, and the exit, the board also contain dirt, rocks, and stones. Each square can contain at most one of the listed objects.

Symbols:
* '@' - Rockford
* ' ' - empty space
* '+' - ground
* '#' - rock
* 'O' - stone
* '$' - diamond
* 'X' - exit

Rockford moves on the board, moving to one of the four spaces adjacent to the current space in a row or column. It can enter the target field if one of the conditions is met:
* it is empty
* there is a ground
* there is a diamond
* there is a stone in the same row as Rockford and the space following the stone is empty
* there is an exit and Rockford collected all diamonds

You cannot enter the field with the rock, and you can only enter the field with the exit if you have collected all the diamonds.

The field abandoned by Rockford goes empty. Rockford, entering the field with the diamond, takes it, and when entering the field with the ground, he "digs" it and the soil disappears.

If there is an exit at the target space, Rockford is removed from the board. As Rockford enters a space with a stone on it, the stone is moved to the next empty space.

If there is an empty field directly below the field with a stone or diamond, ie in the next row of the same column, then this stone or diamond "falls" - it is moved to the empty field below it.

The state of the board is called stable when there is no empty space below any stone and below any diamond. Before and after each Rockford move, any stones and diamonds that can do so fall, bringing the board to a steady state.

There is a rock on each space in the first and last row of the board and in the first and last columns of the board. There is at most one Rockford on the board.

Rockford's commands are represented by the characters:
* 'w' - up
* 's' - down
* 'a' - left
* 'd' - right

In the first line of data there is a pair of positive integers 'rows', 'columns' separated by a space. The next lines contain a description of the initial, not necessarily stable, state of the board. There are 'columns' characters in each of these lines. The rest of the data are user commands.
