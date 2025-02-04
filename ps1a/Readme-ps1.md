# PS1: LFSR / PhotoMagic

## Contact
Name: Manasa Praveen

Section: 202

Time to Complete: 3 hours


## Description
The purpose of this project is to procude psedo-random bits by simulating a linear feedback shift register (LFSR). The project has been split into parts a and b, the first part requires us to create different tests that are implemented by the Boost.Test. In the second part of the project we need to define necessary functions like the generate and step functions. Our code is then tested to ensure that the appropriate results are obtained (in this project we use tap positions at 13, 12, and 10).

### Features
I had to brainstorm what kind of tests I want to implement, I made an InvalidInput test, EdgeCase Test, LFSROutput test, and modified the GeneratInstr test.

#### Part a
I made an InvalidInput test, EdgeCase Test, LFSROutput test, and modified the GeneratInstr test.

#### Part b

### Issues
What doesn't work.  Be honest.  You might be penalized if you claim something works and it doesn't.
As of now I have been having some trouble when trying to run my tests.

### Tests
Describe what is being tested in your Boost unit tests.
The string is being tested to make sure that is is indeed 16-bit, does not contain an invalid characters, etc.

### Extra Credit
Anything special you did. This is required to earn bonus points.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

### Credits
https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c  - I used this to figure how to store the seed in integer format
