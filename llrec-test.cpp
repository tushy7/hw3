#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
#include <vector>

using namespace std;

/**
 * Reads integers (separated by whitespace) from a file
 * into a linked list.
 *
 * @param[in] filename
 *  The name of the file containing the data to read
 * @return
 *  Pointer to the linked list (or NULL if empty or the
 *  file is invalid)
 */
Node* readList(const char* filename);

/**
 * Prints the integers in a linked list pointed to
 * by head.
 */
void print(Node* head);

/**
 * Deallocates the linked list nodes
 */
void dealloc(Node* head);


Node* readList(const char* filename)
{
    Node* h = NULL;
    ifstream ifile(filename);
    int v;
    if( ! (ifile >> v) ) return h;
    h = new Node(v, NULL);
    Node *t = h;
    while ( ifile >> v ) {
        t->next = new Node(v, NULL);
        t = t->next;
    }
    return h;
}

void print(Node* head)
{
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void dealloc(Node* head)
{
    Node* temp;
    while(head) {
        temp = head->next;
        delete head;
        head = temp;
    }
}

// -----------------------------------------------
//   Add any helper functions or
//   function object struct declarations
// -----------------------------------------------
bool is_even(int a){
    return !(a%2);
}

struct IsOdd
{
    bool operator()(int num) {
        return (num % 2) != 0;
    }
};

struct IsLessEquals
{
	int num2;
	IsLessEquals(int val) : num2(val){}
    bool operator()(int num1) {
        return (num1 <= num2);
    }
};

Node * makeList(std::vector<int> const & content)
{
	Node * head = nullptr;
	Node * tail = nullptr;

	for(auto v : content)
	{
		if(head == nullptr) {
			head = new Node(v,nullptr);
			tail = head;
		}
		else {
			tail->next = new Node(v,nullptr);
			tail = tail->next;
		}

	}
	return head;
}




int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }

    // -----------------------------------------------
    // Feel free to update any code below this point
    // -----------------------------------------------
    Node* head = readList(argv[1]);
    cout << "Original list: ";
    print(head);

    // Test out your linked list code
    Node* list = makeList({2, 4, 8, 3});
	Node* small = (Node*) &list; // set to a non-null address
	Node* large = (Node*) &list; // set to a non-null address

    llpivot(list, small, large, 5);

    print(small);
    print(large);
    print(list);

    list = makeList({2, 4, 8, 3});
    print(list);
    IsLessEquals islessequals(5);
    list = llfilter(list, islessequals);
    // Test out your linked list code

    print(list);
    print(large);

    dealloc(large); dealloc(small); dealloc(list);
    
    return 0;

}
