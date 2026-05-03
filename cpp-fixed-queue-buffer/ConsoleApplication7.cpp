#include <iostream>
#include<C:\oops_folder\ConsoleApplication7\Queue.h>
using namespace std;

int main() {
    Queue<int> myQueue;


    
    myQueue.Insert(10);
    myQueue.Insert(20);
    myQueue.Insert(30);

    
    if (myQueue.getFront() != nullptr) {
        cout << "Front element is: " << myQueue.getFront()->getData() << endl;
    }

   
    while (!myQueue.isEmpty()) {
        cout << "Deleting: " << myQueue.getFront()->getData() << endl;
        myQueue.Delete();
    }

    myQueue.Delete();

    return 0;
}