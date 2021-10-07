#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class reader {
    public:
        // initilizes the reader witha spcific file name and populates the map
        reader(std::string _filename);
        //destrutor (doesnt do anything)
        ~reader();
        //reads the words into the map
        std::unordered_map<std::string, int> read_words(); 
        //returns the filename
        std::string get_filename() { return filename; }

    private:
        //fstream
        std::ifstream file; 
        //filename
        std::string filename;
};