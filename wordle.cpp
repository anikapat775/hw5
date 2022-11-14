// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordle(
    std::string in,
    const std::string& floating,
    const std::set<std::string>& dict, 
    std::set<std::string>& results);

int charCount(std::string in, char c);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> results;
    wordle(in, floating, dict, results);
    return results; 
}

// Define any helper functions here
void wordle(
    std::string in,
    const std::string& floating,
    const std::set<std::string>& dict, 
    std::set<std::string>& results)
{
    //if there are no more dashes 
    if(in.find('-')==std::string::npos){
        //if all floating letters are in "in" 
        for(unsigned int i=0; i<floating.length(); i++){
            if(charCount(in,floating[i])< charCount(floating, floating[i])){
                return;
            }
        }
        //add "in" to the results if it is in the dictionary 
        if(dict.find(in)!=dict.end()){
            results.insert(in);
        }
        return;
    }
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for(unsigned int i=0; i<in.length(); i++){
        //attempt to replace dash with every alphabet letter
        if(in[i]=='-'){
            for(unsigned int j=0; j<alphabet.length(); j++){
                in[i] = alphabet[j];
                wordle(in, floating, dict, results);
            }
        }
    }
}

int charCount(std::string in, char c){
    int count = 0; 
    for(unsigned int i=0; i<in.length(); i++){
        if(in[i]==c){
            count++;
        }
    }
    return count; 
}