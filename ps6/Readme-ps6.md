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
I used the std::for_each lambda functions several times throughout my code to replace loops within the RandWriter::kRand(), and ostream& operator<< functions. This made my code a lot more easily readable, and debuggable. I also used the std::count_if lambda expression for character counting inside of the RandWriter::freq() funciton. 

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.
I think one of the main issues was when handling k = 0. I had to adjust how the frequencies and kgrams were stored when dealing with k  = 0. I also initally had some off-by-one error when generating output that I later had to debug to make sure my program ran correctly. 
There are no problems in program and it should all be working correctly. 

### Extra Credit
Anything special you did.  This is required to earn bonus points.
I made a sperate version of this program that uses words instead of characters. I created a new class (WordWriter.cpp and WordWriter.hpp) that recognizes the input file as words instead of a string of characters this time around. Then I had to create a WordTextWriter.cpp (similar to the TextWriter.cpp) which reads the user input, runs the program, and generates the desired output using k order and L length. This new program is very similar to the original TextWriter program but instead of storing the characters as std::string, here I had to write a std::istringstream function that will extract the words. Additionally, when generating the ouput unlike before the ouput can no longer be generated as a string but rather as separate words and in order to do that I had to convert the std::vector<std::string> into ostringstream. 

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
Used the How to loop through a map pdf provided by the instructor to undertsand and implement wraparound logic.
