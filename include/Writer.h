#include <queue>
#include <mutex>
#include <fstream>
#include <thread>
#include <iostream>
#include <chrono>


#include <condition_variable>
#include "../src/Heap.cpp"

class writer
{
    public:
        //constructor and destructor
        writer(heap _pq);
        ~writer();
        //produces the words
        void write_to_file();
        //puts them into the heap
        void read_to_buff();
        //writes to the outpute file multithreaded
        void write();

    private:
        // threads
        std::thread writer_thread;
        std::thread reader_thread;

        //conditional variable to notify threads
        std::condition_variable cond;
        //mutex lock
        std::mutex mutex;
        //Queue buffer of key values to be written to the file
        std::queue<key_value> buffer;
        //write to the output file
        std::ofstream word_writer;
        // custom heap to insert eh words with their frequencies
        heap word_heap;

};