#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <set>
#include <queue>
#include <limits>
#include "page.h"

class Story {
private:
    std::map<int, Page> pages;
    
    void processLine(const std::string& line,const std::string& directory) {
        if (line.empty()) {return;       
        //exit(EXIT_FAILURE);   
        }
        else{
        std::istringstream iss(line);
        int pageNum;
        char pageType, separator,colon;
        std::string filePath, choiceText;
        int choiceNum;

        iss >> pageNum >> separator;
/*This line reads data from the string stream iss, which contains the contents of the line.
pageNum: The stream extracts an integer value first and stores it in pageNum. This value is expected to represent the page number.
separator: Then it extracts a single character and stores it in separator. This character is likely expected to be a delimiter in the line, such as a comma or colon.
pageType: Finally, it extracts another character and stores it in pageType. This character likely indicates the type of the page (e.g., normal, win, lose).
*/
        if(separator=='@'){
            iss >> pageType;
        
        //0@N:page0.txt
        //if (pageType == 'N' || pageType == 'L' || pageType == 'W') {
        
            iss.ignore(1, ':') >> filePath;  // ignores one character up to (and including) a colon character ':' and then reads the subsequent data
            if (filePath == "") {
                std::cerr << "Wrong story format" << std::endl;
            }                                        
            Page newPage(pageNum, directory + "/" + filePath);
            //this->addPage(Page(num, pageType, directory + "/" + line_back));
            if (pageType == 'L') newPage.isLose = true;
            if (pageType == 'W') newPage.isWin = true;
            addPage(newPage);
        } else {            
        //0:1:I am ready for this story!           pagetype is int                  
            // This is a choice for an existing page
            iss >> choiceNum >> colon;           
            //choiceNum= int(pageType);
            //iss.ignore(1, ':') >> choiceText;
            //reads the next integer value from the string stream iss (which contains the content of the current line) and stores it in choiceNum
            getline(iss, choiceText);                 
            //reads the remainder of the string stream iss after the choice number and stores it in choiceText. This is done using getline, which reads characters from the string stream until it encounters a newline character. 
            //pages[pageNum].addChoice(choiceText);
            pages[pageNum].addChoice(choiceNum, choiceText);
        }
        }
    }
    
    
    //step2
  bool validatePageReferences() const {
    for (std::map<int, Page>::const_iterator it = pages.begin(); it != pages.end(); ++it) {
      const std::vector<std::pair<size_t, std::string> >& choices = it->second.getChoices();
      for (size_t i = 0; i < choices.size(); ++i) {
        if (pages.find(choices[i].first) == pages.end()) {
          return false;
        }
      }
    }
    return true;
  }

  bool validatePageReachability() const {
    std::set<int> reachablePages;
    std::queue<int> toVisit;
    toVisit.push(0); // Start from page 0

    while (!toVisit.empty()) {
      int current = toVisit.front();
      toVisit.pop();
      reachablePages.insert(current);

      const std::vector<std::pair<size_t, std::string> >& choices = pages.find(current)->second.getChoices();
      for (size_t i = 0; i < choices.size(); ++i) {
        if (reachablePages.find(choices[i].first) == reachablePages.end()) {
          toVisit.push(choices[i].first);
        }
      }
    }

    for (std::map<int, Page>::const_iterator it = pages.begin(); it != pages.end(); ++it) {
      if (it->first != 0 && reachablePages.find(it->first) == reachablePages.end()) {
        return false;
      }
    }
    return true;
  }

  bool validateWinLosePages() const {
    bool hasWin = false, hasLose = false;
    for (std::map<int, Page>::const_iterator it = pages.begin(); it != pages.end(); ++it) {
      if (it->second.isWin) {
        hasWin = true;
      }
      if (it->second.isLose) {
        hasLose = true;
      }
    }
    return hasWin && hasLose;
  }
  
  
  

public:
    std::vector<std::vector<std::pair<int, int> > > winningPaths;
    
    void validateStory() {
        if (!validatePageReferences() || !validatePageReachability() || !validateWinLosePages()) {
            std::cerr << "Invalid story structure." << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    

    void addPage(const Page& page) {
        pages[page.pageNumber] = page;    //应该没问题
    }

    void readFromFile(const std::string& directory) {
        //std::ifstream file(directory + "/story.txt");
        std::ifstream file((directory + "/story.txt").c_str());
        if (!file) {
            std::cerr << "Error opening file." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            processLine(line, directory);
        }

        file.close();
    }       

    void displayStory() const {
        for (std::map<int, Page>::const_iterator it = pages.begin(); it != pages.end(); ++it) {
            it->second.display();
        }
    }
    
    
    
//step2
/*
    void processLine(const std::string& line,const std::string& directory) {
        std::istringstream iss(line);
        int pageNum;
        char pageType, separator,colon;
        std::string filePath, choiceText;
        int choiceNum;

        iss >> pageNum >> separator;
This line reads data from the string stream iss, which contains the contents of the line.
pageNum: The stream extracts an integer value first and stores it in pageNum. This value is expected to represent the page number.
separator: Then it extracts a single character and stores it in separator. This character is likely expected to be a delimiter in the line, such as a comma or colon.
pageType: Finally, it extracts another character and stores it in pageType. This character likely indicates the type of the page (e.g., normal, win, lose).

        if(separator=='@'){
            iss >> pageType;
        
        //0@N:page0.txt
        //if (pageType == 'N' || pageType == 'L' || pageType == 'W') {
        
            iss.ignore(1, ':') >> filePath;  // ignores one character up to (and including) a colon character ':' and then reads the subsequent data
            if (filePath == "") {
                std::cerr << "Wrong story format" << std::endl;
            }                                        
            Page newPage(pageNum, directory + "/" + filePath);
            //this->addPage(Page(num, pageType, directory + "/" + line_back));
            if (pageType == 'L') newPage.isLose = true;
            if (pageType == 'W') newPage.isWin = true;
            addPage(newPage);
        } else {            
        //0:1:I am ready for this story!           pagetype is int                  
            // This is a choice for an existing page
            iss >> choiceNum >> colon;           
            //choiceNum= int(pageType);
            //iss.ignore(1, ':') >> choiceText;
            //reads the next integer value from the string stream iss (which contains the content of the current line) and stores it in choiceNum
            getline(iss, choiceText);                 
            //reads the remainder of the string stream iss after the choice number and stores it in choiceText. This is done using getline, which reads characters from the string stream until it encounters a newline character. 
            //pages[pageNum].addChoice(choiceText);
            pages[pageNum].addChoice(choiceNum, choiceText);
        }
    }
*/
    
    
bool verifyStory() {
      bool hasWin = false;
      bool hasLose = false;
      std::cerr << "Pages size: " << pages.size() << std::endl;

    // Check for at least one WIN and one LOSE page
    for (std::map<int, Page>::iterator it = pages.begin(); it != pages.end(); ++it) {
        std::cerr << "2" << std::endl; 
        std::cerr << it->second.isWin << std::endl;    
        std::cerr << it->second.isLose << std::endl;           
        if (it->second.isWin) {
              std::cerr << "3" << std::endl; 
            hasWin = true;
        }
        if (it->second.isLose) {
              std::cerr << "4" << std::endl; 
            hasLose = true;
        }
              std::cerr << "\n" << std::endl;        
    }

    if (!hasWin || !hasLose) {
        std::cerr << "Error: Story must have at least one WIN and one LOSE page." << std::endl;          //到了这里
        return false;
    }

    // Check if all pages referenced by choices exist
    for (std::map<int, Page>::iterator it = pages.begin(); it != pages.end(); ++it) {
        std::vector<std::pair<size_t, std::string> >::iterator choiceIt;
        for (choiceIt = it->second.choices.begin(); choiceIt != it->second.choices.end(); ++choiceIt) {
            if (pages.find(choiceIt->first) == pages.end()) {
                std::cerr << "Error: Choice references non-existent page " << choiceIt->first << std::endl;
                return false;
            }
        }
    }

    // Check if every page (except page 0) is referenced by at least one other page's choices
    std::map<int, bool> pageReferenced;
    for (std::map<int, Page>::iterator it = pages.begin(); it != pages.end(); ++it) {
        if (it->first != 0) {
            pageReferenced[it->first] = false;
        }
    }

    for (std::map<int, Page>::iterator it = pages.begin(); it != pages.end(); ++it) {
        std::vector<std::pair<size_t, std::string> >::iterator choiceIt;
        for (choiceIt = it->second.choices.begin(); choiceIt != it->second.choices.end(); ++choiceIt) {
            if (pageReferenced.find(choiceIt->first) != pageReferenced.end()) {
                pageReferenced[choiceIt->first] = true;
            }
        }
    }

    for (std::map<int, bool>::iterator it = pageReferenced.begin(); it != pageReferenced.end(); ++it) {
        if (!it->second) {
            std::cerr << "Error: Page " << it->first << " is never referenced by any choice." << std::endl;
            return false;
        }
    }

    return true;
}

    
    void startAdventure() {
        char input[256];           //a character array (a C-style string) where the input text will be stored.
        unsigned long choice;            //specifies the maximum number of characters to read, including the null terminator
        char * endptr;
        
        int currentPage = 0;
        while (true) {                
            std::cerr << "currentPage is: " << currentPage << std::endl;
            pages[currentPage].display();
    
            if (pages[currentPage].isWin || pages[currentPage].isLose) {
                break;
            }
            std::cout << "Enter your choice, then press enter: ";            
            cin.getline(input, sizeof(input));
            choice = strtoul(input, &endptr, 10);  // Base 10 for decimal numbers   &endptr is a pointer to a char pointer. strtoul sets endptr to point to the first character in input that wasn't part of the number. This is useful for checking if the entire string was a valid number or if there were any extra characters.

            while (*endptr != '\0' || choice<=0 || (choice > pages[currentPage].choices.size())) {
              cout << "That is not a valid choice, please try again\n" << endl;
              cin.getline(input, sizeof(input));
              choice = strtoul(input, &endptr, 10);
            } 

            currentPage = static_cast<int>(pages[currentPage].choices[choice-1].first);                            
/*
            while (!(std::cin >> choice) || choice<=0 || (choice > static_cast<int>(pages[currentPage].choices.size()) ) ) {           //!(std::cin >> choice) -> cin不是int  
                //std::cin >> choice;       
                std::cerr << "choice: " << choice << std::endl;
                std::cerr << "choices size: " << pages[currentPage].choices.size() << std::endl;
                std::cout << "That is not a valid choice, please try again\n";
                std::cin.clear();
                std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            }

            std::cerr << "choice: " << choice << std::endl;   
            currentPage = static_cast<int>(pages[currentPage].choices[choice-1].first);         //会return49
*/
        }
    }
    
    const Page& getPage(size_t pageNumber) const {
        return pages.find(pageNumber)->second;
    }

    void findWinningPaths() {
        std::vector<std::pair<int, int> > currentPath;
        std::set<int> visited;
        dfs(0, currentPath, visited);  // Start DFS from page 0
    }

    void dfs(int currentPage, std::vector<std::pair<int, int> >& currentPath, std::set<int>& visited) {
        visited.insert(currentPage);

        if (pages[currentPage].isWin) {
            currentPath.push_back(std::make_pair(currentPage, -1)); // Add winning page with choice -1
            winningPaths.push_back(currentPath);
            currentPath.pop_back();
        } else {
            for (size_t i = 0; i < pages[currentPage].choices.size(); ++i) {
                int nextPage = pages[currentPage].choices[i].first;
                if (visited.find(nextPage) == visited.end()) {
                    currentPath.push_back(std::make_pair(currentPage, i + 1));  // Store page and choice number
                    dfs(nextPage, currentPath, visited);
                    currentPath.pop_back();
                }
            }
        }

        visited.erase(currentPage);
    }
};