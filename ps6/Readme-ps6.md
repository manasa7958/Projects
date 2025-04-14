# PS6: RandWriter

## Contact
Name: Manasa Praveen
Section: 202
Time to Complete: 7 hours


## Description
The project implements a Random Writer that predicts the characters while mimicing the structure of the input file. The program uses a Markov model to generate the text of the length that the user inputs.

### Features
Describe what your major decisions were and why you did things that way.
I chose to use an unordered_map with string keys to rpresent the kgrams and string values to represent each new character following the kgram. This supports random selection and allows for more efficient lookups. I used a single mt19937 object to generate randomness in this program.

### Testing
What tests did you write?  What exceptions did you use?  Does your code pass the tests?

### Lambda
What does your lambda expression do?  What function did you pass it to?

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

### Extra Credit
Anything special you did.  This is required to earn bonus points.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
