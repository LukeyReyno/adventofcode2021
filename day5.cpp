#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

class Point {
   public:
      int x;
      int y;

      Point() {
         x = 0;
         y = 0;
      }

      Point(int xVal, int yVal) {
         x = xVal;
         y = yVal;
      }

      bool operator==(const Point& other) {
         return this->x == other.x && this->y == other.y;
      }

      void printPoint() {
         std::cout << "(" << x << ", " << y << ")" << std::endl;
      }
};

class Line {
   public:
      Point p1;
      Point p2;

      // (x increment, y increment)
      int slope[2];

      Line(Point start, Point finish) {
         p1 = start;
         p2 = finish;

         if (p1.x == p2.x) {
            slope[0] = 0;
            slope[1] = (p1.y < p2.y) ? 1 : -1;;
         }
         else {
            slope[0] = (p1.x < p2.x) ? 1 : -1;
            slope[1] = ((p1.y < p2.y) ? 1 : -1) * abs((p2.y - p1.y) / (p2.x - p1.x));
         }
      }
};

void printMatrix(std::vector<std::vector<int>> grid) {
   std::cout << "{" << std::endl;
   for (auto row : grid) {
      for (auto col : row) {
         std::cout << col << " ";
      }
      std::cout << std::endl;
   }
   std::cout << "}" << std::endl;
}

std::vector<Line> parsePoints(std::fstream* file) {
   std::vector<Line> lineList;
   std::string fileLine = "";
   std::string currentVal;

   while (getline(*file, fileLine)) {
      std::stringstream stream(fileLine);
      std::vector<Point> linePoints;
      while (getline(stream, currentVal, ' ')) {
         int commaIndex = currentVal.find_first_of(',');
         if (commaIndex == std::string::npos)
            continue;
         int xVal = stoi(currentVal.substr(0, commaIndex));
         int yVal = stoi(currentVal.substr(commaIndex + 1));
         Point p(xVal, yVal);
         linePoints.push_back(p);
      }
      Line l(linePoints[0], linePoints[1]);
      lineList.push_back(l);
   }

   return lineList;
}

int max(int v1, int v2, int v3) {
   if (v1 > v2 && v1 > v3)
      return v1;
   else if (v2 > v3)
      return v2;
   return v3;
}

std::vector<int> findMaxPoints(std::vector<Line> lineList) {
   int maxXVal = 0;
   int maxYVal = 0;

   for (Line l : lineList) {
      maxXVal = max(maxXVal, l.p1.x, l.p2.x);
      maxYVal = max(maxYVal, l.p1.y, l.p2.y);
   }

   std::vector<int> results = {maxXVal, maxYVal};
   return results;
}

std::vector<std::vector<int>> initializeMatrix(int xBound, int yBound) {
   std::vector<std::vector<int>> matrix;
   for (int i = 0; i < yBound + 1; i++) {
      std::vector<int> row;
      for (int j = 0; j < xBound + 1; j++) {
         row.push_back(0);
      }
      matrix.push_back(row);
   }

   return matrix;
}

// Part 1 version only considers horizontal and vertical lines
void fillGrid(std::vector<std::vector<int>>* grid, std::vector<Line> lineList) {
   for (Line l : lineList) {
      // Check Slope
      if (l.slope[0] == 0 || l.slope[1] == 0) {
         Point currPoint = l.p1;
         while (!(currPoint == l.p2)) {
            (&(grid->at(currPoint.y)))->at(currPoint.x) += 1;
            currPoint.x += l.slope[0];
            currPoint.y += l.slope[1];
         }
         (&(grid->at(currPoint.y)))->at(currPoint.x) += 1;
      }
   }
}

// Part 2 version considers all slopes
void fillGrid_part2(std::vector<std::vector<int>>* grid, std::vector<Line> lineList) {
   for (Line l : lineList) {
      // Check Slope
      Point currPoint = l.p1;
      while (!(currPoint == l.p2)) {
         (&(grid->at(currPoint.y)))->at(currPoint.x) += 1;
         currPoint.x += l.slope[0];
         currPoint.y += l.slope[1];
      }
      (&(grid->at(currPoint.y)))->at(currPoint.x) += 1;
   }
}

// Count values in grid greater than or equal to given x
int countValues(std::vector<std::vector<int>> grid, int x) {
   int result = 0;
   for (int row = 0; row < grid.size(); row++) {
      for (int col = 0; col < grid[0].size(); col++) {
         if (grid[row][col] >= x)
            result++;
      }
   }

   return result;
}

void part_1() {
   std::fstream myfile;
   std::string fileName = "input_day5";
   myfile.open(fileName, std::ios::in);

   std::vector<Line> lList = parsePoints(&myfile);
   std::vector<int> gridBounds = findMaxPoints(lList);
   std::vector<std::vector<int>> grid = initializeMatrix(gridBounds[0], gridBounds[1]);
   fillGrid(&grid, lList);
   //printMatrix(grid);
   int count = countValues(grid, 2);

   std::cout << "Part1 - Results (sum of grid values >= 2 [horiz and vert only]): " << count << std::endl;
}

void part_2() {
   std::fstream myfile;
   std::string fileName = "input_day5";
   myfile.open(fileName, std::ios::in);

   std::vector<Line> lList = parsePoints(&myfile);
   std::vector<int> gridBounds = findMaxPoints(lList);
   std::vector<std::vector<int>> grid = initializeMatrix(gridBounds[0], gridBounds[1]);
   fillGrid_part2(&grid, lList);
   //printMatrix(grid);
   int count = countValues(grid, 2);

   std::cout << "Part2 - Results (sum of grid values >= 2): " << count << std::endl;
}

int main() {
   //part_1();
   std::cout << std::endl;
   part_2();
   return 0;
}