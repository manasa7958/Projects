# PS4: Sokoban

## Contact
Name: Manasa Praveen
Section: 
Time to Complete: 4 hours


## Description
In this project we are creating a version of the classic Sokoban game. The objective of the game is for the player to push the red boxes into the storage locations. The sokoban.zip file has text files with various levels in them which are recreated in this program. 

### Features
Describe what your major decisions were and why you did things that way.

#### Part a
In part A of the project we have to implement the Sokoban class, which is where different levels data is stored. I also had to write code the operator>>, operator<< which is meant to read and write the levels from stream accordingly. I also created the protected virtual void method named draw wwhich is used to display the game.

#### Part b

### Memory
Describe how you decided to store the level data including whether you used smart pointers.

### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.

### Issues
I had issues with my Makefile. I was able to run my program on my personal terminal but the Gradescope autograder was not able to find Sokoban.a. This is because I did not Sokoban.a in the project root and instead had it as a subdirectory inside of build/. However, with a but of trial and error I was able to fix it. 
I also had 

### Extra Credit
Anything special you did.  This is required to earn bonus points.


## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban
