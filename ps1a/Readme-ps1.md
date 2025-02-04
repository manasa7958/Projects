# PS1: LFSR / PhotoMagic

## Contact
Name: Manasa Praveen

Section: 202

Time to Complete: 3 hours


## Description
The purpose of this project is to procude psedo-random bits by simulating a linear feedback shift register (LFSR). The project has been split into parts a and b, the first part requires us to create different tests that are implemented by the Boost.Test. In the second part of the project we need to define necessary functions like the generate and step functions. Our code is then tested to ensure that the appropriate results are obtained (in this project we use tap positions at 13, 12, and 10).

### Features
I had to brainstorm what kind of tests I want to implement, I made an LFSROutput test, noThrow test, wrongInsert test and modified the GeneratInstr test. I particularly struggled with the wringInsert test and had to resubmit my project multiple times to the autograder.

#### Part a
I made an LFSROutput test, noThrow test, wrongInsert test and modified the GeneratInstr test.

#### Part b
In the second part of the project I defined necessary function and modfied the private class in the hpp file. I had to write code for the generate and step functions mainly. I did have to rework my step function multiple times because i had been trying to declare my tap positions instead if using their indexes. This had caused quite a bit of errors but then I chose to directly use the indexes and that made my program compile correctly.

### Issues
As of now there are no issues. My program is compiling correctly and my linting all seems to right as well. 

### Tests
Describe what is being tested in your Boost unit tests.
The string is being tested to make sure that is is indeed 16-bit, does not contain an invalid characters, etc.

### Extra Credit
Anything special you did. This is required to earn bonus points.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

### Credits
https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c  - I used this to figure how to store the seed in integer format
