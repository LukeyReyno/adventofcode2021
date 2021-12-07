#include <iostream>
#include <string>
#include <vector>
#include <fstream>

void part_1() {
   // Count the number of number increases
   // start at -1 because first input doesn't count
   int results = -1;

   std::fstream myfile;
   std::string fileName = "input";
   myfile.open(fileName, std::ios::in);


   if (!myfile) {
		std::cout << "No such file";
	}
   else {
      int prev = -1;
      int num = -1;
      std::string currentNum = "";

      while (!myfile.eof()) {
         std::getline(myfile, currentNum);
         if (currentNum.empty())
            break;
         num = std::stoi(currentNum);
         if (num > prev)
            results++;
         prev = num;
      }
   }

   std::cout << "Part1 - Num Increases: " << results << std::endl;

}

void part_2() {
   // Count the number of number increases
   // start at -1 because first input doesn't count
   int results = -1;

   std::fstream myfile;
   std::string fileName = "input";
   myfile.open(fileName, std::ios::in);


   if (!myfile) {
		std::cout << "No such file";
	}
   else {
      // TODO: use index based retrieval of array values instead of this
      int num = -1;
      int offset = 0;
      int prevSum = -1;
      int currentSum = -2;
      std::string currentNum = "";

      std::vector<int> prevList1;
      std::vector<int> prevList2;
      std::vector<int> prevList3;

      while (!myfile.eof()) {
         std::getline(myfile, currentNum);
         if (currentNum.empty())
            break;
         num = std::stoi(currentNum);
         if (offset == 0) {
            prevList1.push_back(num);
            offset += 1;
         }
         else if (offset == 1) {
            prevList1.push_back(num);
            prevList2.push_back(num);
            offset += 1;
         }
         else {
            prevList1.push_back(num);
            prevList2.push_back(num);
            prevList3.push_back(num);
         }

         if (prevList1.size() >= 3) {
            currentSum = prevList1[0] + prevList1[1] + prevList1[2];
            prevList1.clear();
         }
         else if (prevList2.size() >= 3) {
            currentSum = prevList2[0] + prevList2[1] + prevList2[2];
            prevList2.clear();
         }
         else if (prevList3.size() >= 3) {
            currentSum = prevList3[0] + prevList3[1] + prevList3[2];
            prevList3.clear();
         }

         if (currentSum > prevSum) {
            results++;
         }
         prevSum = currentSum;
      }
   }

   std::cout << "Part1 - Num Increases: " << results << std::endl;

}

int main() {
   part_1();
   part_2();
   return 0;
}
