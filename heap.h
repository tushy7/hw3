#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  int m;
  PComparator c;
  std::vector<T> heap;

};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c): m(m), c(c)
{}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{}

template <typename T, typename PComparator>
void Heap<T,PComparator>:: push(const T& item) 
{
  heap.push_back(item);
  int index = heap.size() - 1; //start all the way at the back, and compare forwards 

  while (index != 0) {
    if (c(heap[index], heap[(index - 1)/m])) { //if the added item is smaller than its parent, then swap bc building min-heap by default
      std::swap(heap[index], heap[(index - 1)/m]);
      index = (index - 1)/m; //change index to the swapped index bc that's where you're comparing against
    }
    else { //if parent is smaller than child, just get out bc you're in correct position
      break;
    }
  }

}

template <typename T, typename PComparator>
bool Heap<T,PComparator>:: empty() const 
{
  return (heap.size()==0);
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>:: size() const
{
  return heap.size();
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return heap[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("empty");
  }
  std::swap(heap[0], heap[heap.size() - 1]); //move the last item to the front so you can pop_back 
  heap.pop_back(); //get rid of item 

  size_t index = 0; //start at the front then look down the tree
  while (index * m + 1 < heap.size()) 
  {
    size_t best = index * m + 1; //start at the first one and look through all children nodes to see where to put the node
    for (int i = 2; i <=m; i++)
    {
      size_t child = index * m+i;
      if (child < heap.size() && c(heap[child],heap[best])) //this means the child is smaller than the best index, so swap them
      {
        best = child;
      }
    }
    if (!c(heap[best], heap[index])) //means that best is larger than index, so already in the right spot
    {
      break;
    }
    std::swap(heap[index], heap[best]); //swap if you found a better node to make it fit
    index = best; //update the the best node each iteration 
  }
}

#endif

