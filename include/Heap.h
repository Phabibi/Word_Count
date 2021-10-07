#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using key_value = std::pair<std::string, int>; 

//defines a compare operator for the heap inorder to maintain a max heap using the values of the key_values
//since std does not provide a comparision between two pairs<string, int> in a priority_queue, we need to define it ourselves
struct compare {
    //defining a new compare opretator intoder to use a heap with key_value pairs. 
    bool operator()(key_value a, key_value b)
    {
        //get the two words
        std::string word_1 = a.first;
        std::string word_2 = b.first;

        //get their frequencies 
        int word_1_freq = a.second;
        int word_2_freq = b.second;

        //if they have the same frequency then just compare the two strings alphabetically  
        if(word_1_freq == word_2_freq)
        {
            if(word_1.compare(word_2) > 0)
            {
                return true;
            }
            return false;
        }
        //just compare the frequencies
        return word_1_freq  < word_2_freq;
    }
};

/* wrapper for the stl priority queue, couldve probably designed a bit better to not have this wrapper */ 
class heap {
    public:
        //default constructor
        heap();
        ~heap();
        //constructs a the pq using the word_map frequencies in a desc order based on the values
        heap(std::unordered_map<std::string, int> word_map);

        //queue operations
        void insert(key_value word);
        void pop();
        int size();
        bool empty();
        key_value top();

        //write to an output file *single thread*
        void write_to_file();
    private:
        //max priority_queue heap with the custom compare operator to sort keys in a desc order
        std::priority_queue<key_value, std::vector<key_value>, compare> pq; 
};