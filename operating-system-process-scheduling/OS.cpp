// OS.cpp :  file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
using namespace std;
#include <list>
#include <cmath>

int hashkey(int page_number, int proccess_id,int size) {
    long long sum = 0;
    sum = page_number ^ proccess_id;
    return (int)(sum % size);//to keep in the size of the RAM
}
//the info given by the CPU is logical_number / page number and process id 
struct frame {
    int frame_ID;
    bool valid;
    int process_id;
    int page_number;
    frame() {
        frame_ID = -1;
        valid = false;
        process_id=-1;
        page_number=-1;
    }
};
template <class t>
struct HashNode {

    t data;
    HashNode<t>* next;
    HashNode() {
        data = t();
        next = nullptr;
    }

};
//page_id is the pyhical adress also called as the frame
//page_number is the page _logical answer;

template <int size,class t>
class Hashtable {
    HashNode<t>* Table [size];
    int page_size;
    int no_of_physical_frames;
    int frame;
public:
    Hashtable(int x, int y) { for (int i = 0; i < size; i++) { Table[i] = nullptr; }
    page_size = x;
    no_of_physical_frames = y;
    frame = 0;
    
    }
    int insert(int proccess_id, int page_number) {
        if (frame >= no_of_physical_frames){
            return -1;
    }
        int index = hashkey(page_number, proccess_id, size);
        HashNode<t>* x = new HashNode<t>();
        x->data.frame_ID = frame++;
        x->data.page_number = page_number;
        x->data.process_id = proccess_id;
        x->data.valid = true;


        if (Table[index] == nullptr) {
            Table[index] = x;
        }
        else {
            x->next = Table[index];
            Table[index]= x;
        }
        return 0;
    }


    int search(int proccess_id, int page_number) {
        int index = hashkey(page_number, proccess_id,size);
        if (Table[index] == nullptr) {
            return -1;
        }
        else {
            HashNode<t>* temp = Table[index];
            while(temp!=nullptr){
                if (temp->data.process_id == proccess_id && temp->data.page_number == page_number && temp->data.valid==true) {
                    return temp->data.frame_ID;
                }
                else {
                    temp = temp->next;
                }
            }
        }
        return -1;
    }
    int get_page_size() {
        return this->page_size;
    }

};



int main()
{
    Hashtable<128, frame> map(4096, 64); //this means that we have 64 frames each of 4096 bytes;
    int checker;
    int id = 533076;
    int size_of_doc = 19662;
    int size= map.get_page_size();
    int pages = ceil((float)size_of_doc / size);

    cout << "Inserting the process " << id << " into the virtual table\n";
    for (int i = 0; i < pages; i++) {
       checker= map.insert(id, i);
       if (checker == -1) {
           cout << "The physical memory is filled\n";
           break;
       }
    }
    int c = 0;
    cout << "Displaying the frame id being used by process "<<id<<endl;
    for (int i = 0; i < pages; i++) {
       checker= map.search(id, i);
       if (checker != -1) {
           c++;
           cout << checker<<endl;
       }
    }
   int fragmentation=( c* size)-size_of_doc;
    cout << "Internal fragmentation is equal to "<<fragmentation<<endl;
  

    
}
