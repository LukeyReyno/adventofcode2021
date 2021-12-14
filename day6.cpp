#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>

class LanternFish {
   public:
      int daysLeftCycle;

      LanternFish() {
         daysLeftCycle = 0;
      }

      LanternFish(int cycleVal) {
         daysLeftCycle = cycleVal;
      }

      void passDay() {
         daysLeftCycle--;
      }

      LanternFish procreate() {
         daysLeftCycle = 6;
         return LanternFish(8);
      }

      void print() {
         std::cout << "Cycle: " << daysLeftCycle << std::endl;
      }
};

std::vector<LanternFish> parseFishInput(std::fstream* file) {
   std::vector<LanternFish> fishList;
   std::string fileLine = "";
   getline(*file, fileLine);
   std::stringstream stream(fileLine);
   std::string currentVal;

   while (getline(stream, currentVal, ',')) {
      int dayValue = stoi(currentVal);
      LanternFish newFish = LanternFish(dayValue);
      fishList.push_back(newFish);
   }

   return fishList;
}

void simulateFishPopulation(std::vector<LanternFish>* fishList, int numDays) {
   for (int i = 0; i < numDays; i++) {
      std::vector<LanternFish> tempFList = *fishList;
      for (int j = 0; j < tempFList.size(); j++) {
         LanternFish fish = tempFList[j];
         fish.passDay();
         if (fish.daysLeftCycle == -1) {
            LanternFish newFish = fish.procreate();
            fishList->push_back(newFish);
         }
         fishList->operator[](j) = fish;
      }
   }
}

// Brute Force Solution
void part_1() {
   std::fstream myfile;
   std::string fileName = "input_day6";
   myfile.open(fileName, std::ios::in);

   int daysToPass = 80;
   std::vector<LanternFish> fishList = parseFishInput(&myfile);
   simulateFishPopulation(&fishList, daysToPass);

   std::cout << "Part1 - Results (Number of Lantern Fish after 80 Days): " << fishList.size() << std::endl;
}

unsigned long long* parseFishInput_part2(std::fstream* file, int arraySize) {
   void* fishListVoid = calloc(arraySize, sizeof(unsigned long long));
   unsigned long long* fishList = (unsigned long long*) fishListVoid;
   
   std::string fileLine = "";
   getline(*file, fileLine);
   std::stringstream stream(fileLine);
   std::string currentVal;

   while (getline(stream, currentVal, ',')) {
      int dayValue = stoi(currentVal);
      fishList[dayValue] += 1;
   }

   return fishList;
}

void simulateFishPopulation_part2(unsigned long long** fishList, int numDays, int arraySize) {
   for (int i = 0; i < numDays; i++) {
      void* fishListVoid = calloc(arraySize, sizeof(unsigned long long));
      unsigned long long* prevFishList = (unsigned long long*) fishListVoid;
      
      // copy list and reset main one
      for (int j = 0; j < arraySize; j++) {
         prevFishList[j] = (*fishList)[j];
         (*fishList)[j] = 0;
      }

      for (int j = 0; j < arraySize; j++) {
         // hardcoded values from problem
         if (j == 0) {
            (*fishList)[6] += prevFishList[0];
            (*fishList)[8] += prevFishList[0];
            (*fishList)[0] += prevFishList[1];
         }
         else if (j != 8) {
            (*fishList)[j] += prevFishList[j+1];
         }
      }
   }
}

unsigned long long sumOfPopulations(unsigned long long* fishValues, int arraySize) {
   unsigned long long count = 0;

   for (int i = 0; i < arraySize; i++) {
      count += fishValues[i];
   }

   return count;
}

void part_2() {
   std::fstream myfile;
   std::string fileName = "input_day6";
   myfile.open(fileName, std::ios::in);

   // Max days for cycle is 8
   int fishArraySize = 9;
   int daysToPass = 256;
   unsigned long long* fishValues = parseFishInput_part2(&myfile, fishArraySize);

   simulateFishPopulation_part2(&fishValues, daysToPass, fishArraySize);
   unsigned long long populationSize = sumOfPopulations(fishValues, fishArraySize);

   std::cout << "Part2 - Results (Number of Lantern Fish after 256 Days): " << populationSize << std::endl;
   free(fishValues);
}

// Warning! high memory usage
int main() {
   part_1();
   std::cout << std::endl;
   part_2();
   return 0;
}