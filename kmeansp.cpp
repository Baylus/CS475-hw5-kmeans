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
Matrix getCenters(int k, Matrix input);

int main(int argc, char *argv[])
{
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
   int k = 0, t = 0;
   k = atoi(argv[1]);
   t = atoi(argv[2]);

   Matrix input("input");
   input.read();
   int n = input.numRows();

   // In order to easily calculate distance, we are gonna transpose input
   // It will be used for calculating min distance.
   Matrix tinput( input, "tinput" );
   tinput.transposeSelf();

   initRand();

   for (int i = 0; i < t; ++i) {
      Matrix centers(getCenters(k, input));

      Matrix newCenters(centers);
      int c = 1;
      // Keep changing until nothing changes.
      do {
         int grouped[k];   // Number of data points gouped. (This number includes self)
         for (int i = 0; i < k; ++i) grouped[i] = 1;

         centers = Matrix(newCenters);
         
         for ( int i = 0; i < n; ++i ) {
            // For each data item, find closest center
            int minC = 0;  // This will be the center point of the minimum distance
            int min = centers.dist2(0, i, tinput); // Start with first possible point
            for ( int j = 1; j < k; ++j ) {
               int x = centers.dist2( j, i, tinput );
               if ( x < min ) {
                  min = x;
                  minC = j;
               }
            }

            // Found the nearest center
            // double newX = newCenters.get(minC, 0) + input.get(i, 0)
            // Add to the current sum for center.
            newCenters.set( minC, 0, newCenters.get(minC, 0) + input.get(i, 0) );
            newCenters.set( minC, 1, newCenters.get(minC, 1) + input.get(i, 1) );

            grouped[minC] += 1;
         }

         for( int i = 0; i < k; ++i ) {
            if (grouped[i] == 1) {
               // One center wasn't linked to any points, 
               // Either get new centers or randomize the one.
               // since this will usually happen at the beginning, it isnt
               // too costly to get new centers, though on troublesome data, it might be
               // getting new ones a lot.

               // Get new centers.
               newCenters = getCenters(k, input);
               if (debug) {
                  printf("Getting new centers after %d iterations.\n", c);
               }
               continue;   // After getting new centers, restart the process.
            }
            // Average out the newCenters
            newCenters.set( i, 0, newCenters.get(i, 0) / grouped[i] );
            newCenters.set( i, 1, newCenters.get(i, 1) / grouped[i] );
         }

         ++c;
      } while ( !newCenters.nearEqual(0.01, centers) );

      centers = Matrix(newCenters);
      centers.sortRows();

      centers.printfmt("Points:", "%.4f ");
      double minDist = centers.dist2();
      printf("K: %d  MinD: %.4f\n", k, minDist);
   }


   

   return 0;
}

/////////////// Functions //////////////////////////

Matrix getCenters(int k, Matrix input) {

   ////////////////// CHANGE THIS FOR KMEANSP //////////////
   Matrix c(k, 2, "Centers");
   input.sample(c);

   return c;
}


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
