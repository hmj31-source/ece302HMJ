#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "lib/Image.hpp"
#include "List.hpp"
#include "Queue.hpp"

struct State {
  int row;
  int col;
};

bool isBorderCell(int row, int col, int height, int width)
{
  return row == 0 || row == height - 1 || col == 0 || col == width -1;
}

bool isValidMove(const Image& image, int row, int col)
{
  int height = image.height();
  int width = image.width();

  if ( row < 0 || row >= height || col < 0 || col >= width) {
    return false;
  }

  return image(row, col) == WHITE;
}

int main(int argc, char *argv[])
{
  // get input/output file names from command line arguments
  if (argc != 3) {
    std::cout << "Usage: pathfinder "
              << "<first_input_filename> <second_output_filename>\n"
              << std::endl;
    return EXIT_FAILURE;
  }

  std::string input_file = argv[1];
  std::string output_file = argv[2];

  // Read input image from file
  Image image = readFromFile(input_file);

  // TODO: breadth-first search
  int height = image.height();
  int width = image.width();

  //find start red pixel and validate
  int red_count = 0;
  State start{-1, -1};

  for (int r = 0; r < height; ++r) {
    for (int c= 0; c < width; ++c) {
        Pixel p = image(r, c);
        
        if ( p == RED) {
          red_count++;
          start = {r, c};
        }
        else if(p != WHITE && p != BLACK) {
          std::cerr << "Error: invalid pixel color" << std::endl;
          return EXIT_FAILURE;
        }
    }
  }

  if (red_count == 0) {
    std::cerr << "Error: no starting red pixel" << std::endl;
    return EXIT_FAILURE;
  }

  if (red_count > 1) {
    std::cerr << "Error: multiple red pixels" << std::endl;
    return EXIT_FAILURE;
  }

  auto isBorder = [&](int r, int c) {
    return r == 0 || r == height - 1 || c ==0 || c == width -1;
  };
  if (isBorder(start.row, start.col)) {
    image(start.row, start.col) = GREEN;
    std::cout << "Solution Found" << std::endl;
  }
  
  else{
    //bfs seutp
    Queue<State, List<State>> frontier;
    std::vector<std::vector<bool>> explore(height, std::vector<bool>(width, false));

    frontier.enqueue(start);
    explore[start.row][start.col] = true;

    bool found = false;
    State goal{-1, -1};

    //bfs loop
    while(!frontier.isEmpty()) {
      State curr = frontier.peekFront();
      frontier.dequeue();

      if (image(curr.row, curr.col) == WHITE && isBorder(curr.row, curr.col)) {
        found = true;
        goal = curr;
        break;
      }

      //required order: up, down, left, right
      int dr[4] = {-1, 1, 0, 0};
      int dc[4] = {0, 0, -1, 1};

      for (int i = 0; i < 4; i++) {
        int nr = curr.row + dr[i];
        int nc = curr.col + dc[i];
        
        if (nr >= 0 && nr < height && nc >= 0 && nc < width){
          if (!explore[nr][nc] && image(nr, nc) == WHITE) {
            frontier.enqueue({nr, nc});
            explore[nr][nc] = true;
          }
        }
      }  
    }
    if (found) {
      image(goal.row, goal.col) = GREEN;
      std::cout << "Solution Found" << std::endl;
    }
    else {
      std::cout << "No Solution Found" << std::endl;
    }
  }
  // TODO: Write solution image to file
  writeToFile(image, output_file);
  return EXIT_SUCCESS;
}
