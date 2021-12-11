#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <bitset>

std::vector<std::string> makeMatrix(std::fstream* file) {
   std::vector<std::string> stringList;
   std::string currentLine = "";

   while (!(file->eof())) {
      std::getline(*file, currentLine);
      if (currentLine.empty())
         break;
      stringList.push_back(currentLine);
   }

   return stringList;
}

char findMaxBit(std::string bitString) {
   int _0_count = 0;
   int _1_count = 0;

   for (int i = 0; i < bitString.size(); i++) {
      if (bitString[i] == '0')
         _0_count += 1;
      else
         _1_count += 1;
   }

   if (_0_count == _1_count)
      return '2';

   return (_1_count > _0_count) ? '1' : '0';
}

std::vector<int> findRates(std::vector<std::string> matrix) {
   std::string rateValueBin = "";

   for (int col = 0; col < matrix[0].size(); col++) {
      std::string columnString = "";
      for (int row = 0; row < matrix.size(); row++) {
         columnString += matrix[row][col];
      }
      rateValueBin += findMaxBit(columnString);
   }

   std::vector<int> results;
   unsigned long gammaRate = std::bitset<12>(rateValueBin).to_ulong();
   unsigned long epsilonRate = std::bitset<12>(rateValueBin).flip().to_ulong();

   results.push_back(gammaRate);
   results.push_back(epsilonRate);

   return results;
}

void part_1() {
   std::fstream myfile;
   std::string fileName = "input_day3";
   myfile.open(fileName, std::ios::in);


   if (!myfile) {
		std::cout << "No such file";
	}
   else {
      std::vector<std::string> matrix = makeMatrix(&myfile);
      std::vector<int> results = findRates(matrix);
      int gammaRate = results[0];
      int epsilonRate = results[1];

      std::cout << "Part1 - Gamma Rate: " << gammaRate << std::endl;
      std::cout << "Part1 - Epsilon Rate: " << epsilonRate << std::endl;
      std::cout << "Part1 - Results (Gamma Rate * Epsilon Rate): " << gammaRate * epsilonRate << std::endl;
   }
}

int getGasRating(std::vector<std::string> matrix, std::string gasType) {
   int numCols = matrix[0].size();

   for (int col = 0; col < numCols; col++) {
      std::string columnString = "";
      for (int row = 0; row < matrix.size(); row++) {
         columnString += matrix[row][col];
      }
      char bitCriteria = findMaxBit(columnString);

      if (bitCriteria == '2')
      {
         if (gasType == "Oxygen")
            bitCriteria = '1';
         else if (gasType == "CO2")
            bitCriteria = '0';
      }
      // flip bit for CO2 (need least common)
      else if (gasType == "CO2") {
         if (bitCriteria == '1')
            bitCriteria = '0';
         else
            bitCriteria = '1';
      }

      std::vector<std::string> newMatrix;

      for (int row = 0; row < matrix.size(); row++) {
         if (matrix[row][col] == bitCriteria)
            newMatrix.push_back(matrix[row]);
      }

      if (newMatrix.size() == 0)
         return std::bitset<12>(matrix[matrix.size() - 1]).to_ulong();

      matrix = newMatrix;
   }

   return std::bitset<12>(matrix[0]).to_ulong();
}

void part_2() {
   std::fstream myfile;
   std::string fileName = "input_day3";
   myfile.open(fileName, std::ios::in);


   if (!myfile) {
		std::cout << "No such file";
	}
   else {
      std::vector<std::string> matrix = makeMatrix(&myfile);

      int oxygenRating = getGasRating(matrix, "Oxygen");
      int co2Rating = getGasRating(matrix, "CO2");

      std::cout << "Part1 - Oxygen Rating: " << oxygenRating << std::endl;
      std::cout << "Part1 - CO2 Rating: " << co2Rating << std::endl;
      std::cout << "Part1 - Results (Oxygen Rating * CO2 Rating): " << oxygenRating * co2Rating << std::endl;
   }
}

int main() {
   part_1();
   std::cout << std::endl;
   part_2();
   return 0;
}
