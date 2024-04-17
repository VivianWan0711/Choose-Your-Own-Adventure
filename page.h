#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
using namespace std;

class Page {
public:
    size_t pageNumber;
    vector<string> context;   
    vector<pair<size_t, string> > choices;
    bool isWin, isLose;
    //bool isWin() const { return isWin; }
    //bool isLose() const { return isLose; }
    //vector<pair<string, long int> > variables;

    //Page() : pageNumber(-1), isWin(false), isLose(false) {}
    //Page(int num) : pageNumber(num), isWin(false), isLose(false) {}

    Page() :
        pageNumber(0),
        //pageType('N'),
        context(vector<string>()),
        choices(vector<pair<size_t, string> >()),
        //conditions(vector<pair<string, long int> >()),
        //variables(vector<pair<string, long int> >()),
        isWin(false), isLose(false){}
    Page(size_t pageNumber, string filename) :
        pageNumber(pageNumber),
        //pageType(pageType),
        context(vector<string>()),
        choices(vector<pair<size_t, string> >()),
        isWin(false), isLose(false)
        //conditions(vector<pair<string, long int> >()),
        //variables(vector<pair<string, long int> >()) 
        {
            cout << "Attempting to open file: " << filename << endl;
            ifstream file(filename.c_str());
            if (!file) {
              std::cerr << "cannot open file\n" << std::endl;
            }
            string line;
            while (getline(file, line)) {               
              context.push_back(line);
            }
            file.close();                 //？？？
        /*It initializes the Page object with the given page number, page type, and a list of lines (context) read from a file.
        The constructor takes three parameters: pageNum (of type size_t), pageType (a char), and filename (a string).
        It initializes several vectors: context, choices, conditions, and variables.
        The constructor attempts to open the file specified by filename. If it fails to open the file (!file), it calls an error function with NO_FILE.
        If the file opens successfully, it reads each line from the file and adds it to the context vector.*/
        }
/*
    void addText(const std::string& line) {               //没call这个函数    text为空
        context.push_back(line);   
    }

    void addChoice(const std::string& choice) {
        choices.push_back(choice);
    }
    */

    void addChoice(size_t n, string s) { choices.push_back(make_pair(n, s)); }

    void display() const {
        std::cout << "Page " << pageNumber << "\n==========\n";
        //std::cout << text << "\n";
        for (size_t i = 0; i < context.size(); i++) {
          cout << context[i] << endl;
        }
        if (!isWin && !isLose) {
            std::cout << "\n";        
            std::cout << "What would you like to do?\n";
            std::cout << "\n";
            for (size_t i = 0; i < choices.size(); ++i) {
                std::cout << " " << i + 1 << ". " << choices[i].second << "\n";
            }
        } else {
            std::cout << (isWin ? "\nCongratulations! You have won. Hooray!\n" : "\nSorry, you have lost. Better luck next time!\n");
        }
    }
    
  
    //std::vector<std::pair<size_t, std::string> > getChoices() const { return choices; }
    const std::vector<std::pair<size_t, std::string> >& getChoices() const {
        return choices;
    }

/*
    bool isValidChoice(size_t choice) {
        for (size_t i = 0; i < choices.size(); ++i) {
            if (choices[i].first == choice) {
                return true;
            }
        }
        return false;
    }
*/
    
    /*
    int getDestination(size_t choice) {
        for (size_t i = 0; i < choices.size(); ++i) {
            if (choices[i].first == choice) {
                return choices[i].first;
            }
        }
        return -1;  // Return an invalid page number if the choice is not found
    }
    */
    
    
    int getDestination(size_t choice) {
        return choices[choice-1].first;  // Return an invalid page number if the choice is not found
    }
    
/*    
bool isValidChoice(int choice) const {
    std::cerr << "choice is： " << choice << std::endl;
    std::cerr << "choices size is： " << choices.size() << std::endl;
    for (size_t i = 0; i < choices.size(); ++i) {
        std::cerr << "choices[" << i << "]first is： " << choices[i].first << std::endl;
        if (static_cast<int>(choices[i].first) == choice) {
            return true;
        }
    }
    return false;
}
*/

};