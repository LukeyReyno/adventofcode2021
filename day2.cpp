#include <iostream>
#include <string>
#include <fstream>

void part_1() {
   std::fstream myfile;
   std::string fileName = "input_day2";
   myfile.open(fileName, std::ios::in);


   if (!myfile) {
		std::cout << "No such file";
	}
   else {
      int horizPos = 0;
      int depth = 0;
      std::string currentLine = "";

      int spaceIndex;
      std::string direction;
      std::string valString;
      int val;

      while (!myfile.eof()) {
         std::getline(myfile, currentLine);
         if (currentLine.empty())
            break;
         spaceIndex = currentLine.find_first_of(" ");
         direction = currentLine.substr(0, spaceIndex);
         valString = currentLine.substr(spaceIndex + 1);

         //std::cout << direction << std::endl;
         //std::cout << valString << std::endl;

         val = std::stoi(valString);
         
         if (direction == "forward") {
            horizPos += val;
         }
         else if (direction == "down") {
            depth += val;
         }
         else if (direction == "up") {
            depth -= val;
         }
      }

      std::cout << "Part1 - Horizontal Distance: " << horizPos << std::endl;
      std::cout << "Part1 - Depth: " << depth << std::endl;
      std::cout << "Part1 - Results (HorizDist * Depth): " << horizPos * depth << std::endl;
   }
}

void part_2() {
   std::fstream myfile;
   std::string fileName = "input_day2";
   myfile.open(fileName, std::ios::in);


   if (!myfile) {
		std::cout << "No such file";
	}
   else {
      int horizPos = 0;
      int depth = 0;
      int aim = 0;
      std::string currentLine = "";

      int spaceIndex;
      std::string direction;
      std::string valString;
      int val;

      while (!myfile.eof()) {
         std::getline(myfile, currentLine);
         if (currentLine.empty())
            break;
         spaceIndex = currentLine.find_first_of(" ");
         direction = currentLine.substr(0, spaceIndex);
         valString = currentLine.substr(spaceIndex + 1);

         val = std::stoi(valString);
         
         if (direction == "forward") {
            horizPos += val;
            depth += aim * val;
         }
         else if (direction == "down") {
            aim += val;
         }
         else if (direction == "up") {
            aim -= val;
         }
      }

      std::cout << "Part2 - Horizontal Distance: " << horizPos << std::endl;
      std::cout << "Part2 - Depth: " << depth << std::endl;
      std::cout << "Part2 - Results (HorizDist * Depth): " << horizPos * depth << std::endl;
   }
}

int main() {
   part_1();
   std::cout << std::endl;
   part_2();
   return 0;
}
