# PS4: Sokoban

## Contact
Name: Manasa Praveen

Section: 202

Time to Complete: 4 hours


## Description
In this project we are creating a version of the Sokoban game. The objective of the game is for the player to push the red boxes into the storage locations. The sokoban.zip file has text files with various levels in them which are recreated in this program. 

### Features
I decided to store level data as a std::vector<std::string> because it would make it easy for indexing and also when implementing my operator>>, and operator<< functions.  I also used sf::Texture to store the images as so that everytime the image is called it does not haev to be loaded repeatedly.  Lastly, when trying to mimic the output from the instructions file I made sure to draw the ground texture first, and then the other objects to avoid redundant rendering. 

#### Part a
In part A of the project we have to implement the Sokoban class, which is where different levels data is stored. Each level text file had an arrangement of symbols which were the converted to their corresponding images and rendered as output. These symbols included: # (grey wall), . (ground), @ (player), A (Red box), a (storage spot).  I wrote code for the operator>>, operator<< which is meant to read and write the levels from stream accordingly.  I also created the protected virtual void method named draw as mentione din the instructions to display the game.

#### Part b

### Memory
I stored level data as a std::vector<std::string>. I did not use any dynamic memory allocation so I did not haev any smart pointer (shared or unique).

### Lambdas
I used the Lambda expression std::none_of inside of my isWon() function to check if any boxes remained that were not in it's storage position yet. 

### Issues
I had issues with my Makefile. I was able to run my program on my personal terminal but the Gradescope autograder was not able to find Sokoban.a. This is because I did not write Sokoban.a in the project root and instead had it inside the build/ subdirectory. However, with a bit of trial and error I was able to fix it.  I also had some trouble with my draw function as I struggled with the placement of the ground tiles. Initially the player did not have the ground background but when I tried fixing that I added the background to the entire screen while in the correct output the ground should not be under the gray walls. So I had to rewrite my if-else statement inside of the draw function a couple of times before I was able to render the correct output.

### Extra Credit
Anything special you did.  This is required to earn bonus points.

### Change (PSXc)
Previously I lost a lot of points on my ps4a project because the make command did not do anything. This is because all was not my first rule inside my Makefile. Hence, the only way to produce the output was to manually type make all in the terminal. To improve the project I added this line .PHONY: all clean lint into my Makefile which ensures that all is indeed my first rule and hence, the command make will compile all of the files. In addition, to tweaking my Makefile I also did the extra credit for ps4a by adding a turn counter. I used my base code from ps4b and added sf::Text moveCounterText, and int moveCount as private member of the Sokoban class to implement the move counter function. I initialized the moveCounterText inside of the reset() function. Inside of this reset function I manually set the position, font, size, and color. The moveCount should increment everytime the player moves which is why it is nested inside of the movePlayer() function. The move count should be displayed at the top left corner of the screen, and should automatically reset to 0 every time the user resets as well.
In order to accomodate for the change in ouput caused by the inclusion of the moveCounterText, I also updated my screenshot.png to display the appropriate output.


## Acknowledgements
https://www.sfml-dev.org/documentation/3.0.0/ - referred to the documentation for SFMl when writing functions.
https://www.google.com/search?client=safari&rls=en&q=functions+in+algorithm+library+c%2B%2B&ie=UTF-8&oe=UTF-8 - used to figure out what algorithm library functions to use
If you used images or other resources than the ones provided, list them here.

Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban
