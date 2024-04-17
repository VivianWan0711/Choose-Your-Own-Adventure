
#include <cstdio>
#include <fstream>  //ifstream
#include <sstream>  //stringstream
#include <cstdlib>
#include <limits>
#include "story.h"
using namespace std;

bool isValidChoice(int choice, const std::vector<std::pair<size_t, std::string> > &choices) {
    for (size_t i = 0; i < choices.size(); ++i) {
        if (choices[i].first == static_cast<size_t>(choice)) {  // Cast choice to size_t
            return true;
        }
    }
    return false;
}

int getUserChoice(const std::vector<std::pair<size_t, std::string> > &choices) { 
  int choice;
  while (true) {
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (std::cin.fail() || !isValidChoice(choice, choices)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid choice. Please try again." << std::endl;
      continue;
    }
    return choice;
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
      std::cerr << "wrong argument" << std::endl;
      return EXIT_FAILURE;
  }

  Story story;
  story.readFromFile(argv[1]);
  //story.validateStory(); 

    if (!story.verifyStory()) {
        std::cerr << "Story verification failed." << std::endl;
        return EXIT_FAILURE;
    }

    story.startAdventure();

    return EXIT_SUCCESS;
}
