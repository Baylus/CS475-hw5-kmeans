/* 
Baylus Tunnicliff    4/5/2019

CS 475 - Machine Learning     
HW 5 - K-means analysis
*/

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string>
#include <cstring>

#include "mat.h"
#include "rand.h"

using namespace std;

int debug = false;

// debug/exit functions
// void e(string s);
void e(string s="Error occurred", int r=-1);
// void ddebug(string s);

int main(int argc, char* argv[]) {
   if (argc > 1) {
      for ( int i=0; i < argc; ++i ) {
         if ( strcmp(argv[i], "--debug") == 0 || strcmp(argv[i], "-d") == 0 ) {
            if (debug != false) {
               // Debug already set
               debug = 2;
            }
            else {
               debug = true;
            }
         }
      }
   }
   
   return 0;
}

/////////////// Functions //////////////////////////


////////////////// Private Functions //////////////////

// void e(string s) { e(s, -1); }

void e(string s, int r)
{
   cerr << s << endl;
   exit(r);
}

// void ddebug(string s)
// {
//    // Prints iff debug == 2

// }
