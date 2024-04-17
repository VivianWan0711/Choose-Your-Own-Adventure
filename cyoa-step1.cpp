#include <cstdio>
#include <fstream>  //ifstream
#include <sstream>  //stringstream
#include <iostream>
#include <cstdlib>
#include "story.h"

using namespace std;
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <directory>" << std::endl;
        return EXIT_FAILURE;
    }

    Story story;
    story.readFromFile(argv[1]);
    story.displayStory();

    return EXIT_SUCCESS;
}