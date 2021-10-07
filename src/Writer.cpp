#include "../include/Writer.h"

writer::writer(heap _pq) : word_writer{"output.txt"} {
    //initilize the heap
    word_heap = _pq;
}

writer::~writer(){
    word_writer.close();
}

void writer::read_to_buff()
{
    while(!word_heap.empty())
    {
        //lock the critical section
        std::unique_lock<std::mutex> lock(mutex);
        cond.wait(lock, [](){ return true; });

        //push it into the buffer and pop it from the heap
        buffer.push(word_heap.top());
        word_heap.pop();

        cond.notify_all();
    }
}

void writer::write_to_file()
{
 while(!word_heap.empty())
    {
        //lock the critical section
        std::unique_lock<std::mutex> lock(mutex);
        cond.wait(lock, [this](){ return !buffer.empty(); });

        //look at the front of the queue, pop and read to the output file
        auto top = buffer.front();
        buffer.pop();
       
        word_writer << top.first << "   " << top.second << "\n";

        cond.notify_all(); 
    }
    
    //write the leftovers to the file
    while(!buffer.empty())
    {
        auto top = buffer.front();
        word_writer << top.first << "   " << top.second << "\n";
        buffer.pop();
    }
}

void writer::write()
{
    writer_thread = std::thread(&writer::write_to_file,this);
    reader_thread = std::thread(&writer::read_to_buff,this);

    writer_thread.join();
    reader_thread.join();

    std::cout << "outputs are written to output.txt" << std::endl;
    return;
}