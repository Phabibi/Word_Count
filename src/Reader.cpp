#include "../include/Reader.h"
reader::reader(std::string _filename)
{
   //the open function will throw an exception if fails to read 
   file.open(_filename, std::ifstream::in);
   filename = _filename;

   std::cout << "stream was set up for the following file name: " << filename << std::endl; 
}

reader::~reader() {
    file.close();
    std::cout << "closing file" << std::endl;
};

std::unordered_map<std::string, int> reader::read_words()
{
    std::unordered_map<std::string, int> word_map;
    if(!file.is_open())
    {
        throw std::runtime_error("file stream is not set up properly");
    }
    //stream is set up and we can read
    std::string word;
    while(file >> word)
    {
        word_map[word] += 1;
    }
    std::cout << "read the file succesfully" << std::endl;

    return word_map; 
}