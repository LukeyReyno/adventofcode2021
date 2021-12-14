#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <fstream>

class BingoSpace {
   public:
      std::string value;
      bool marked;

      BingoSpace(std::string val) {
         value = val;
         marked = false;
      }

      void setMarked() {
         marked = true;
      }
};

void printBingCardList(std::vector<std::vector<std::vector<BingoSpace>>> bingos) {
   for (auto bingo : bingos) {
      std::cout << "{" << std::endl;
      for (auto row : bingo) {
         for (auto bingoSpace : row) {
            std::cout << bingoSpace.marked << ", ";
         }
         std::cout << std::endl;
      }
      std::cout << "}" << std::endl;
   }
}

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

std::vector<std::string> parseList(std::fstream* file) {
   std::vector<std::string> stringList;
   std::string line = "";
   std::getline(*file, line);
   std::stringstream stream(line);
   std::string currentVal;

   while (getline(stream, currentVal, ',')) {
      stringList.push_back(currentVal);
   }

   return stringList;
}

std::vector<std::vector<BingoSpace>> makeBingoCard(std::string bingoString) {
   std::stringstream bingoStream(bingoString);
   std::vector<std::vector<BingoSpace>> bingoMatrix;
   std::string currentRow, currentVal;

   while (getline(bingoStream, currentRow, '\n')) {
      std::stringstream lineStream(currentRow);
      std::vector<BingoSpace> rowVector;

      while (getline(lineStream, currentVal, ' ')) {
         // skip whitespace values
         while (currentVal == "")
         {
            getline(lineStream, currentVal, ' ');
         }
         BingoSpace bs(currentVal);
         rowVector.push_back(bs);
      }
      bingoMatrix.push_back(rowVector);
   }

   return bingoMatrix;
}

std::vector<std::vector<std::vector<BingoSpace>>> makeListOfBingoCards(std::fstream* file) {
   std::vector<std::vector<std::vector<BingoSpace>>> bingoList;
   std::string line = "";
   std::string currentBingoString = "";

   while (!(file->eof())) {
      std::getline(*file, line);
      if (line == "")
      {
         if (!currentBingoString.empty())
         {
            std::vector<std::vector<BingoSpace>> newBingoMatrix = makeBingoCard(currentBingoString);
            bingoList.push_back(newBingoMatrix);
            currentBingoString = "";
         }
      }
      else {
         currentBingoString.append(line + "\n");
      }
   }

   return bingoList;
}

bool containsBingo(std::vector<std::vector<BingoSpace>> bingoCard, std::vector<int> point) {
   bool rowBingo = true;
   bool colBingo = true;

   //check row
   for (int col = 0; col < bingoCard[0].size(); col++) {
      if (!bingoCard[point[0]][col].marked) {
         rowBingo = false;
         break;
      }
   }

   //check col
   for (int row = 0; row < bingoCard.size(); row++) {
      if (!bingoCard[row][point[1]].marked) {
         colBingo = false;
         break;
      }
   }

   return rowBingo || colBingo;
}

bool checkBingoCard(std::vector<std::vector<BingoSpace>>* bingoCard, std::string num) {
   bool containsNum = false;
   std::vector<int> numLoc;

   for (int rowIndex = 0; rowIndex < bingoCard->size(); rowIndex++) {
      for (int colIndex = 0; colIndex < bingoCard->at(rowIndex).size(); colIndex++) {
         BingoSpace* bs = &((bingoCard->at(rowIndex)).at(colIndex));
         //std::cout << bs.value << " ---- " << num << std::endl;
         if (bs->value == num) {
            bs->setMarked();
            containsNum = true;
            numLoc = {rowIndex, colIndex};
            break;
         }
      }
      if (containsNum)
         break;
   }

   if (containsNum)
      return containsBingo(*bingoCard, numLoc);
   
   return false;
}

int countUnmarkedSpaces(std::vector<std::vector<BingoSpace>> bingoCard) {
   int results = 0;

   for (int rowIndex = 0; rowIndex < bingoCard.size(); rowIndex++) {
      for (int colIndex = 0; colIndex < bingoCard[rowIndex].size(); colIndex++) {
         BingoSpace bs = bingoCard[rowIndex][colIndex];
         if (!bs.marked)
            results += stoi(bs.value);
      }
   }

   return results;
}

/*
Begins to fill out each bingo card in search of a bingo
Returns the sum of all unchecked boxes in the card with the first bingo
times the last used value in the number list
*/
int fillBingoCards(
   std::vector<std::vector<std::vector<BingoSpace>>>* bingoCardList, 
   std::vector<std::string> numList) 
{
   for (std::string num : numList) {
      for (int cardIndex = 0; cardIndex < bingoCardList->size(); cardIndex++) {
         if (checkBingoCard(&(bingoCardList->at(cardIndex)), num)) {
            int unmarkedSum = countUnmarkedSpaces(bingoCardList->at(cardIndex));
            return unmarkedSum * stoi(num);
         }
      }
   }

   return -1;
}

void part_1() {
   std::fstream myfile;
   std::string fileName = "input_day4";
   myfile.open(fileName, std::ios::in);


   if (!myfile) {
		std::cout << "No such file";
	}
   else {
      std::vector<std::string> numbersToCall = parseList(&myfile);
      std::vector<std::vector<std::vector<BingoSpace>>> bingoList = makeListOfBingoCards(&myfile);
      //printBingCardList(bingoList);

      int bingoResults = fillBingoCards(&bingoList, numbersToCall);

      std::cout << "Part1 - Results (unmarked sum * last called num): " << bingoResults << std::endl;
   }
}

int fillBingoCards_part2(
   std::vector<std::vector<std::vector<BingoSpace>>>* bingoCardList, 
   std::vector<std::string> numList) 
{
   int totalBingoCards = bingoCardList->size();
   int totalCompletedCards = 0;
   std::vector<bool> completedCards;
   
   for (int cardIndex = 0; cardIndex < bingoCardList->size(); cardIndex++) {
      completedCards.push_back(false);
   }

   for (std::string num : numList) {
      for (int cardIndex = 0; cardIndex < bingoCardList->size(); cardIndex++) {
         if (checkBingoCard(&(bingoCardList->at(cardIndex)), num)) {
            if (!(completedCards[cardIndex]))
            {
               totalCompletedCards += 1;
               completedCards[cardIndex] = true;
            }
            if (totalBingoCards == totalCompletedCards)
            {
               int unmarkedSum = countUnmarkedSpaces(bingoCardList->at(cardIndex));
               return unmarkedSum * stoi(num);
            }
         }
      }
   }

   return -1;
}

void part_2() {
   std::fstream myfile;
   std::string fileName = "input_day4";
   myfile.open(fileName, std::ios::in);


   if (!myfile) {
		std::cout << "No such file";
	}
   else {
      std::vector<std::string> numbersToCall = parseList(&myfile);
      std::vector<std::vector<std::vector<BingoSpace>>> bingoList = makeListOfBingoCards(&myfile);
      //printBingCardList(bingoList);

      int bingoResults = fillBingoCards_part2(&bingoList, numbersToCall);

      std::cout << "Part2 - Results (unmarked sum * last called num): " << bingoResults << std::endl;
   }
}

int main() {
   part_1();
   std::cout << std::endl;
   part_2();
   return 0;
}
