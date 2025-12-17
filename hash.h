#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
      // Add your code here
      int spots = 6;
      int taken = k.size();
     
      //make unsinged long long w[i] from instructions
      //should fill from back and go to front, moving on when all 6 spots filled
      unsigned long long w[5] = {0,0,0,0,0};
      unsigned long long fill = 0; //needs to be able to hold 64 bit

      int cnt = 0;
      int pos = 4;//start at end for w
      int multiplicar = 1;
      for(int i=taken-1; i>=0; i--){
        //do something
        int num = letterDigitToNumber(k[i]);
        
        fill += num * multiplicar;
        multiplicar *= 36;
        cnt++;

        if(cnt == 6){//store and reset after filling all spots
          w[pos] = fill;
          pos--;

          multiplicar = 1;
          cnt=0;
          fill=0;
        }
      }

      if(cnt > 0){
        w[pos] = fill;
      }

      unsigned long long hashington = 0;
      for(int i=0; i<5; i++){
        hashington += rValues[i] * w[i];
      }

      for(int i=0; i<5; i++){
        std::cout<<"w["<<i<<"] = "<<w[i]<<std::endl;
      }

      return hashington;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        //if upper make lower
        if(letter >= 'A' && letter <= 'Z'){
          char low = letter - 'A' + 'a';
          return low - 'a';
        } 
        else if(letter >= '0' && letter <= '9'){
          return (letter -'0')+26;
        }
        else if(letter >='a' && letter <= 'z'){
          return letter -'a';
        }
        return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
