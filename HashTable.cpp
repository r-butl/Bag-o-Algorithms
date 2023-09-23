// CSCI 311 - Spring 2023
// Hash table implementation 
// Author: Lucas Butler

#include <iostream>
#include <math.h>
#include "HashTable.h"

// Check if a string is in a vector already
int isin(std::vector<std::string> v, std::string s){

        for(int i = 0; i < v.size(); i++){
            if(v[i] == s) return i;
        }
        return -1;
}

// default constructor for the hash table
HashTable::HashTable(){
        p = 31;
        size = 11;
        table.resize(size);
}

// parameterized constructor for the hash table
HashTable::HashTable(int s, int mult){
        size = s;
        p = mult;
        table.resize(size);
}

// return the size of the table
int HashTable::getSize(){ 
    
        return table.size(); 
}

// return the total number of elements stored in each bucket of the table
int HashTable::getNumElements(){ 

        int sum = 0;
        for(int i = 0; i < table.size(); i++){
                sum += table[i].size();
        }
        return sum;
}

// returns p
int HashTable::getP(){ return p; }

// prints all of the strings in the table
void HashTable::printTable(){
  std::cout << "HASH TABLE CONTENTS" << std::endl;
  for (int i = 0; i < table.size(); i++){
    if (table[i].size() > 0){
      std::cout << i << ": ";
      for (int j = 0; j < table[i].size()-1; j++){
        std::cout << table[i][j] << ", ";
      }
      std::cout << table[i][table[i].size()-1] << std::endl;
    }
  }
}

// Searches for an element in the table
int HashTable::search(std::string s){
  
        int lookup = hash(s);
        if(isin(table[lookup], s) != -1) return lookup; 
        return -1;
}

// Inserts a value into the table
void HashTable::insert(std::string s){

        int lookup = hash(s);
        table[lookup].push_back(s);

}

// Remove a value from the hash table 
void HashTable::remove(std::string s){

        int lookup = hash(s);

        if(table[lookup].size() != 0){
                std::vector<std::string> temp;
                bool removedYet = false;
                for(int i = 0; i < table[lookup].size(); i++){

                        // If the value exists, remove the first instance of it, otherwise keep it
                   if(table[lookup][i] == s){
                           if(removedYet) temp.push_back(table[lookup][i]); 
                           else removedYet = true;
                   }else{
                        temp.push_back(table[lookup][i]);
                   }
                }

                // Reset the vector
                table[lookup] = temp;
        }
}

// Resize the table 
void HashTable::resize(int s){

        // When resizing the table, we will need to rehash all of the elements
        std::vector<std::string> temp;
        for(int i = 0; i < table.size(); i++){
                for(int j = 0; j < table[i].size(); j++){

                        // push all the strings in the current chain to the temporary vector
                        temp.push_back(table[i][j]);
                }
                // clear the elements out of the current chain
                table[i].clear();
        }

        // resize the table
        table.resize(s);

        // rehash all of the elements
        for(int i = 0; i < temp.size(); i++){
            insert(temp[i]);
        }
}

// Produces a hash index given the input string
int HashTable::hash(std::string s){
 
        unsigned int sum = 0;
        // implement a polynomial rolling hash function to determine the index
        for(int i = 0; i < s.size(); i++){
            // return the ascii value of the character, mod it with the size of the table and 
            sum += (pow(p, i) * s[i]);
            
        }
        sum %= table.size();
        return sum;
}
