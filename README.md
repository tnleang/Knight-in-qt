# Knight tour

A Knight's Tour is a sequence of moves of a knight on a chessboard such that the knight visits every square once and  only once. If the knight ends on a square that is one knight's move from the beginning square (so that it could tour the board again immediately, following the same path), the tour is closed, otherwise it is open.

The Knight's Tour Problem is the mathematical problem of finding a knight's tour. Creating a program to find a Knight's Tour is a common problem given to computer science students at every major university. Normally, it is given in an introductory course in order to teach recursion. When using recursion, "backtracking" is accomplished via the run-time stack. 

Warnsdorff's rule:
Each square contains an integer giving the number of moves that the knight could make from that square. In this case, the rule tells us to move to the square with the smallest integer in it, namely 2. Warnsdorff's rule is a heuristic for finding a knight's tour. We move the knight so that we always proceed to the square from which the knight will have the fewest onward moves. When calculating the number of onward moves for each candidate square, we do not count moves that revisit any square already visited. It is, of course, possible to have two or more choices for which the number of onward moves is equal; there are various methods for breaking such ties, including one devised by Pohl and another by Squirrel and Cell.

Develop a program that will solve the Knight's Tour for any starting position given by the end-user on a standard chessboard, in standard chess notation. The program with then print, in standard chessboard nomenclature, the moves that the knight must take to touch each square once and only once. After displaying the moves, your program should state whether the solution it provided is either open or closed. This program form a backtracking without using recursion.There are two different methods. First, by using a stack (implemented as a linked list) that you've developed, and then secondly, with a queue (priority queue implemented as an array).