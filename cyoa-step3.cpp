#include <iostream>
#include <cstdio>
#include <fstream>  //ifstream
#include <sstream>  //stringstream
#include <cstdlib>
#include <limits>
#include "story.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <directory>" << std::endl;
        return EXIT_FAILURE;
    }

    Story story;
    story.readFromFile(argv[1]);
    story.findWinningPaths();

    if (story.winningPaths.empty()) {
        std::cout << "This story is unwinnable!" << std::endl;
    } else {
        for (size_t i = 0; i < story.winningPaths.size(); ++i) {
            for (size_t j = 0; j < story.winningPaths[i].size(); ++j) {
                if (j > 0) std::cout << ",";
                std::cout << story.winningPaths[i][j].first;
                if (story.winningPaths[i][j].second != -1) { // Check if it's not a win page
                    std::cout << "(" << story.winningPaths[i][j].second << ")";
                }
            }
            std::cout << "(win)" << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
