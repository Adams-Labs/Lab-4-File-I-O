/* 
 * This is the Main.cpp file for the File I/O program for Comp 139e lab 04. This file opens a input and output file
 * based on command line arguments and parses the data from the input file into words and numbers.
 * Outputs the word and length of words found and the value of integers. 
 * Ignores white space and prints each input found on a different line. 
 * 
 * File:   main.cpp
 * Author: Adam Claxton 
 *
 * Created on October 14, 2020, 9:32 AM
 */

#include <cstdlib>
#include <fstream> // include the input and output file streams with fstream
#include <iostream>

using namespace std; // using standard name space

int main(int argc, char** argv) { // main function is passed command line arguments input file name(argv[1]) and output file name(argv[2])
    
    
    // Check command line arguments and open appropriate input and output files 
    
    if (argc < 3) { // we need at least 3 command line arguments for this program to work (argv[0] is the output path)  
        std::cerr << "Incorrect number of arguments" << argc << std::endl;
        return EXIT_FAILURE;
    } 
    else { // if we have at least 3 command line arguments 
        ifstream myInputFile(argv[1]); // open input file 
        if (!myInputFile.is_open()) { // check that the input file opened correctly
            std::cerr << "Failed to open Input File" << argv[1] << std::endl;
            return EXIT_FAILURE;
        }
        ofstream myOutputFile; // create output stream for output file 
        myOutputFile.open(argv[2], ios::out | ios::app); // open output file in append mode 
        if (!myOutputFile.is_open()) { // make sure the output file opened correctly 
            std::cerr << "Failed to open Output File" << argv[2] << std::endl;
            return EXIT_FAILURE;
        }
        
        // Checks all the entries of the input file, sorts and reports them accordingly 
        
        while (!myInputFile.eof()) { // while we are not at the end of the input file, keep reading from it. 
            int nextChar = myInputFile.peek(); // look at the first char of the next entry without removing or changing it. 

            if (isdigit(nextChar)) { // if the char peek is a digit 
                int numFound;
                myInputFile >> numFound; // read the input file entry as an integer and stop at the next whitespace 
                myOutputFile << "Found an integer: " << numFound << std::endl;
            }
            else if (isalpha(nextChar)) { // if the char peek is a letter (use else if so it only preforms one of the operations) 
                string letters;
                int length;
                myInputFile >> letters;// read the input file entry as an string and stop at the next whitespace 
                length = letters.length(); // find the length of the string found 
                
                if(!ispunct(letters[length-1])){ // if the string doesn't end if punctuation (word) 
                myOutputFile << "Found a " << length << " character word " << letters << std::endl;
                }
                else{ // if the string does end in punctuation (word.) 
                    myOutputFile << "Found a " << (length-1) << " character word ";  // reports the length of just the word without the punctuation 
                    for(int i = 0; i < (length-1); i++){ // prints the string one char at a time up to the punctuation 
                      myOutputFile << letters[i];   
                    }
                    myOutputFile << endl; // next line 
                    myOutputFile << "Found a 1 character word " << letters[length-1] << endl; // reports the punctuation as a 1 char word
                }
            }
            else if (ispunct(nextChar)) { // if the char peek is punctation (use else if so it only preforms one of the operations) 
                char c;
                myInputFile >> c; // read the punctuation as a single char
                myOutputFile << "Found a 1 character word " << c << endl;

            }
            else { // if the char peek is whitespace or another unwanted character
                myInputFile.get(); // grab the unwanted character to remove it from the buffer but don't print it
            }
        }
        
        // close files when done using them 
        
        myInputFile.close(); // close input file 
        myOutputFile.close(); // close output file 
    }
    return EXIT_SUCCESS;
}

