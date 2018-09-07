README for Part 1: BST

Separated the two projects so the file names didn't get confusing. 
To build this project please open up a command-line terminal for this directory either by manually navigating via cd commands or by right clicking inside the folder and clicking "Open in Terminal" 

TO COMPILE: Once fully-navigated, type in the following to compile the program: ./BUILD 
*Note, this is a different BUILD file than the Part 3. Please do not move this file around for clarity-purposes. 
This will produce a file named runProg. Do not discard it, it will be used later on. 

TO RUN: Once the previous steps are completed, use the same terminal window to type the following to run the program: ./RUN 
*NOTE: This will run just the program without any standard input. 
If you wish to have standard input be run through the program please look at the following syntax examples to do this: 
./(script) < (inputfile.txt) 
E.g: ./RUN < words.txt
Or if you wish the standard output to be redirected to another folder: 
./(script) < (inputfile.txt) > (outputfile.txt) 
E.g: ./RUN < words.txt > output.txt

This program will work with any standard input but you are provided with the following files in order to do some minimal testing: words.txt, 100words.txt, 1000words.txt, and 10000words.txt. Along with these files, are expected output files to compare the expected vs. actual output. They are located inside the same folder (Part 1 BST) and match with the input files in the following syntax: 
Input file: (fileName).txt, Output file: (fileName)EXPECTED.txt

The source files for this part are DictBST.h, DictNode.h, and main.cpp
