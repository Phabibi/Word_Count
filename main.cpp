#include "src/Reader.cpp"
#include "src/Writer.cpp"

int main(){
    /*would write unit tests if i had a bitmore time */
    reader word_reader("./test_inputs/wordlist.txt");
    //reader word_reader("./test_inputs/testwords.txt");
    //reader word_reader("./test_inputs/testnumbers.txt");

    //read the words and construct a frequency map
    std::unordered_map<std::string, int> word_map = word_reader.read_words();
    //initilize a heap of the words and frequencies to have them in a desc order 
    heap m_heap(word_map);
    //initlize a writer to write the words and their frequencies to a file in a producer/consumer multithreaded
    writer writer(m_heap);

    /*multi threaded*/
    auto t1 = std::chrono::high_resolution_clock::now();
    writer.write();
    auto t2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> res = t2 - t1;    

    std::cout << "multithreaded time: " << res.count() << " ms" << std::endl;

    /*single threaded*/
    auto t1_ = std::chrono::high_resolution_clock::now();
    m_heap.write_to_file();
    auto t2_ = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> res_ = t2_ - t1_;    

    std::cout << "single_threaded time: " << res_.count() << "ms" <<  std::endl;

    return 0;
}