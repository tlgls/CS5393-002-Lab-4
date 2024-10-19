#include <iostream>
#include <vector>
#include <stdexcept>

class PriorityQ {
private:
    std::vector<int> heap; // Heap implemented as a vector

    // helper functions to get the parent index of current node
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; } // helper function to get the left child node index of the current node
    int rightChild(int i) { return 2 * i + 2; } // helper function to get the right child node index of the current node

    // function to move the element at index 'i' up the heap to restore the heap property
    void heapifyUp(int i) {
        // while the current node is not the root and violates the heap property
        while (i > 0 && heap[parent(i)] > heap[i]) {
            std::swap(heap[i], heap[parent(i)]); // swaps current node with its parent
            i = parent(i); // moves current index to parent
        }
    }

    void heapifyDown(int i) {
        int left = leftChild(i); // gets index of left child
        int right = rightChild(i); // right child
        int smallest = i; // assuming current index is smallest

        if (left < heap.size() && heap[left] < heap[smallest]) // if left child smaller than current node, update smallest
            smallest = left;
        if (right < heap.size() && heap[right] < heap[smallest]) // if right child smaller than current node, update smallest
            smallest = right;

        if (smallest != i) { // if smallest is not the current node, swap and continues heapifying down
            std::swap(heap[i], heap[smallest]);
            heapifyDown(smallest); // recursively heapify down
        }
    }

public:
    // checks if the priority queue is empty
    bool empty() {
        return heap.empty();
    }

    // returns the size of the priority queue
    int size() {
        return heap.size();
    }

    // returns the element with the highest priority (min element)
    int top() {
        if (empty()) {
            throw std::runtime_error("Priority Q is empty."); // exception for if trying to get top of empty heap
        }
        return heap.front(); // top of heap
    }

    // inserts an element into the heap
    void push(int value) {
        heap.push_back(value); // adds new element to end of heap
        heapifyUp(heap.size() - 1); // restores heap property by moving the new element up
        std::cout << "Inserted " << value << " into the PriorityQ.\n";
    }

    // removes the element with the highest priority
    void pop() {
        if (empty()) {
            throw std::runtime_error("Priority Q is empty."); // exception for if trying to remove from an empty heap
        }
        std::swap(heap.front(), heap.back()); // swaps top element with last element
        heap.pop_back(); // removes last element (original top element)
        if (!empty()) {
            heapifyDown(0);
        }
    }

    // prints the current contents of the heap
    void print() {
        if (empty()) {
            std::cout << "Priority Q is empty.\n";
        } else {
            std::cout << "PriorityQ contents: ";
            for (int val : heap) {
                std::cout << val << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    try {
        PriorityQ pq; // creates instance of priorityQ class
        
        // Initial dataset
        std::vector<int> dataset = {50, 30, 10, 40, 20, 100, 70, 90, 60, 80};
        std::cout << "Original dataset: "; // prints original dataset
        for (int value : dataset) {
            std::cout << value << " ";
        }
        std::cout << "\n";

        // insert elements into the priority queue
        std::cout << "\nInserting elements into the PriorityQ:\n";
        for (int value : dataset) {
            pq.push(value);
            pq.print();
        }

        // displays the size of the PriorityQ
        std::cout << "\nSize of PriorityQ: " << pq.size() << "\n";

        // removes elements one by one
        std::cout << "\nRemoving elements from PriorityQ:\n";
        while (!pq.empty()) {
            pq.print();
            pq.pop();
            std::cout << "Is PriorityQ Empty? " << (pq.empty() ? "Yes\n" : "No\n");
        }

        // trying to pop from an empty queue (exception handling)
        pq.pop(); // this will throw an exception

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
