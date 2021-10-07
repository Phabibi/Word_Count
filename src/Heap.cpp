#include "../include/Heap.h"
//defualt constructor
heap::heap(){}

heap::heap(std::unordered_map<std::string, int> word_map){
    //start inserting the map into the queue 
    for(auto words : word_map)
    {
        pq.push(words);
    }
    std::cout << "constructed the heap successfully" << std::endl;
}

heap::~heap(){}

void heap::insert(key_value word){
    pq.push(word);
    std::cout << "pushed: " << word.first << " : " << word.second << std::endl;
}

void heap::pop(){
    if(pq.empty())
    {
        std::cout << "the queue is empty cannot pop" << std::endl;
        return;
    }
    pq.pop();
}

int heap::size(){
    return pq.size();
}

bool heap::empty(){
    return pq.empty();
}

key_value heap::top(){
    return pq.top();
}

void heap::write_to_file(){
    //make a copy of the heap
    std::priority_queue<key_value, std::vector<key_value>, compare> pq_copy = pq; 

    std::ofstream output("output_single_thread.txt", std::ofstream::out | std::ofstream::trunc);
    //pop from the top of the heap into our results array
    while(!pq_copy.empty())
    {
        key_value words = pq_copy.top();
        pq_copy.pop();
        output << words.first << "  " << words.second << std::endl;
    }

    output.close();

}