# PS6: RandWriter

## Contact
Name: Manasa Praveen
Section: 202
Time to Complete: 7 hours


## Description
The project implements a Random Writer that predicts the characters while mimicing the structure of the input file. The program uses a Markov model to generate the text of the length that the user inputs. The user will have to give the program a source text, order k, and a desired output length L. Then the program generates a string of length L by randomly choosing the next charcaters based on the previous k characters. 

### Features
Describe what your major decisions were and why you did things that way.
I chose to use an unordered_map with string keys to represent the kgrams and unordered_map<char, int> as values. This supports random selection and allows for more efficient lookups. I used a single mt19937 object to generate randomness in this program. I also had to implement wraparound logic to support the circular text processing. 

### Testing
What tests did you write?  What exceptions did you use?  Does your code pass the tests?
I had five different tests. These tests look to ensure the basic functionality of the program is running correctly, then it also tests edge cases such as when unvalid k values are used in the input. Lastly, the tests also make sure the program doesn't make any errors while generating ouput. I particularly test to make sure the correct length string is generated, and the correct prefix is used. 
In the case that the wrong output is being generated, I used the general std::exception class to handle errors. All of my tests sucessfully passed.

### Lambda
What does your lambda expression do?  What function did you pass it to?

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

### Extra Credit
Anything special you did.  This is required to earn bonus points.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
