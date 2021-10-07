# Word_Count

## Introduction 
The following repo implements both a parallel and sequential solution to the word count problem using unordered hash map and heap priority queue. Given a space separated input text file, the program will output a text file with the following format <Word  Frequency> where frequencies are in a desc order. There are 3 main components to this implementation, the Reader, Heap and Writer.
  
## Reader
  The reader class is fairly straightforward, using the std::ifstream, the given input file is read line by line and words are inserted into an std::unordered_map where the **keys** are the words and the **values** are the frequencies of each word. I decided to use an unordered_map as opposed to a map in this implementation since the order of the keys are not important hence using an unordered_map guarantees a O(1) look up.
  
## Heap
  The Heap class is essentially a wrapper for the std::priority_queue however, since we would want to compare the frequencies of each word with each other as oppose to their keys, I implemented a compare struct which overwrites the _()_ operator inorder to compare the values of 2 key_value pairs. Furthermore I decided to use a heap priority_queue inorder to sort the frequencies in a desc order which is done in O(n log n). The **write_to_file** function implements a sequential solution to pop from the priority_queue and write to a file.
  
 ## Writer
  The Writer class implements a multithreaded consumer/producer solution inorder to read from the heap into a buffer and write to an output file. The producer thread pops from the heap into a buffer which is implemented using a std::queue while data is still available. The second thread (Consumer) as long as the queue is not empty and data is available writes to an output file. I used a std::mutex with std::unique_lock to lock the critical section and conditional variable to notify when data is available to consume.
  
## Time Analysis
   The solution to this problem will always be bounded by the sorting of the frequencies, since we are using a heap priority_queue, the insertion and popping from the heap will be done in O(log n) time, since we are doing this for all the  words in the file (n), the time complexity comes to O(N log N). Although insertion into the unordered_map has a worst case of O(N) in case of hash collisions, we are still bounded by O(N log N). 
  
   Since the problem required a multithreaded approach, I tried to pinpoint the places where multithreading would actually optimize the sequential solution. There are 3 main parts to this solution:
      1. Reading from a file to a map
      2. Inserting Key_values into the heap to sort the frequencies.
      3. Writing to the output file

  for step 1: a possible multithreaded solution would be to read the file in chunks where multiple threads will read different chunks and join at the end. The problem with this approach is that we are still bounded by disk access thus there won't be much performance gain and the implementation would be a bit complicated. 

  for step 1-2: another possible solution would be to have a thread read from the file and writes to the map while another thread keeps track of the heap. After spending some time figuring this solution out, I realized that it is a bit complicated since I needed a way to have a reference for each spot in the heap so I could easily update/remove any key_value as the other thread is reading the file. Since this is not possible to do with stl::priotity_queue, I wanted to keep the code clean and less complicated thus I decided not to go with this approach. 
  
  for step 2-3: at this step we have the heap with all the words in a desc order based on their frequencies and we just need to write them to the file. A possible solution would be to have a thread read from the heap into a buffer while another thread writes from the buffer to the output file at the same time. I decided to go with this solution as it was the most straightforward approach. 

 ## Multithread vs Sequential
  I decided to time both solutions in order to see if there was any performance gain. These were the result for the input file provided:
       multithreaded time: 8.00587 ms</br>
       single_threaded time: 14.6517ms
       
  We can observe that the multithreaded has performance gain. 
 
 ## Conclusion
 Although the multithreaded solution does yield performance gains, I believe my solution is not very optimal and if steps 1-2 were to be implemented in parallel, there would be more performance gain. 
