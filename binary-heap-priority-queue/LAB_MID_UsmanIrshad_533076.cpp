#include <iostream>
#include <string>
#include <C:\oops_folder\lab_mid_usman_oops\.vs\lab_mid_usman_oops.slnx\Stack.h>
#include <C:\oops_folder\lab_mid_usman_oops\.vs\lab_mid_usman_oops.slnx\BST_mid.h>
#include <C:\oops_folder\lab_mid_usman_oops\.vs\lab_mid_usman_oops.slnx\Queue.h>
#include<C:\Users\usman\OneDrive\Desktop\New folder\Assignment_1_DSA_ipod\DoubleLinkedList.h>

using namespace std;

struct StockModification {
    int quantity;
    StockModification() { quantity = 0; }
    StockModification(int n) { quantity = n; }
    friend istream& operator>>(istream& i, StockModification& g) {
        i >> g.quantity;
        return i;
    }

    friend ostream& operator<<(ostream& i, const StockModification& g) {
        i << g.quantity;
        return i;
    }
};

struct Order {
 int   order_id;
 int product_id;
 int quantity_needed;
;
 Order() { order_id = 0;
           product_id = 0;
           quantity_needed = 0;
           
 }
 Order(int a , int b, int x) {
     order_id = a;
     product_id = b;
     quantity_needed = x;
 }
 friend ostream& operator<<(ostream& i, const Order& g) {
     i << "Order Id"<< g.order_id<<endl;
     i << "Product Id" << g.product_id << endl;
     i << "Quantity ordered" << g.quantity_needed << endl;
     return i;
 }
 friend istream& operator>>(istream& i, Order& g) {
     i >> g.product_id;
     i >> g.quantity_needed;
     return i;
 }




};

struct Stock {
    int id;
    string name;
    static int id_count;
    int quanitity;
    string Category;
    Stack<StockModification> treatment;
    bool pending;
    Stock() {
        id = id_count++;
        name = "John Doe";
        quanitity = 5;
        Category = "In Stock";
        pending = false;
    }
    void displayStack() { treatment.display(); }

    bool operator<(const Stock& c) const { return id < c.id; }
    bool operator>(const Stock& c) const { return id > c.id; }
    bool operator==(const Stock& c) const { return id == c.id; }
    Stock& operator=(const Stock& d) {
        if (this != &d) {
            this->id = d.id;
            this->name = d.name;
            this->quanitity = d.quanitity;
            this->treatment = d.treatment;
        }
        return *this;
    }
    void setQuantity(int d) { quanitity = d; }
    void push(StockModification c) { treatment.push(c); }
    void pop() { treatment.pop(); }
    int getQuantity() { return quanitity; }
    friend ostream& operator<<(ostream& i, const Stock& g) {
        i << "\nName = " << g.name << endl;
        i << "ID = " << g.id << endl;
        i << "Quantity= " << g.quanitity << endl;
        i << "Category= " << g.Category << endl;
        i << "Pending = " << g.pending << endl;
        g.treatment.display();
        return i;
    }

    void setPending(bool x) { pending = x; }

    void Restock() { quanitity = quanitity + 10; }
    void UndoRestock() { quanitity = quanitity - 10; }
};

struct ActionLog {
    int type; 
    int Id;
    ActionLog(int t = 0, int id = -1) : type(t), Id(id) {}

    bool operator==(int c) const { return type == c; }

    friend ostream& operator<<(ostream& os, const ActionLog& a) {
        os << "[Type: " << a.type << ", ID: " << a.Id << "]";
        return os;
    }
};




class Amaazon {
    tree<Stock> logs;
    Stack<ActionLog> GlobalUndo;
    QUEUE<Stock> line;
    QUEUE<Stock> Pending_line;
    QUEUE<Order> orders;
    Stack<Stock> last;

public:
    Amaazon() {}

    void insertStock(Stock p) {
        logs.insert(p);
        line.enqueue(p);
        ActionLog x(1, p.id);
        GlobalUndo.push(x);
    }

    void ProcessStock() {
    Order asked;
    cout << "\n\tFirst input the Product id and then the amount of product you want to move\t\n";
    cin >> asked;
    Stock x;
    x.id= asked.product_id;
    StockModification t;
    node<Stock>* n = logs.search(x);
    
    if (n->getData().getQuantity() >= asked.quantity_needed) {
        if (n != nullptr) {
            n->getData().push(t);
        }
        else { cout << "Does not exist"; return; }
        ActionLog x1(2, x.id);
        GlobalUndo.push(x1);
        if (Pending_line.search(x)) {
            if (Pending_line.front().id == asked.product_id) {
                last.push(Pending_line.front());
                Pending_line.dequeue();
                int rem = n->data.getQuantity();
                rem=rem-asked.quantity_needed;
                if (n != nullptr) n->data.setQuantity(rem);
            }
        }
        else {
            if (!line.isEmpty() && line.front().id == asked.product_id) {
                cout << "Here";
                last.push(line.front());
                line.dequeue();
                int rem = n->data.getQuantity();
                rem = rem - asked.quantity_needed;
                if (n != nullptr) n->data.setQuantity(rem);
            }
        }
    }
       else {
           cout << "\n\tNot enough stock\n";
           n->data.setPending(true);
           Stock s;
           s= n->getData();
           last.push(line.front());
           line.dequeue();
           cout << "Displaying pending line";
           Pending_line.enqueue(s);
           Pending_line.display();
       }
    }



    void display() {
        logs.displayPreOrder();

    }

    void popHistory_of_1Stock(int id) {
        Stock p;
        p.id = id;
        node<Stock>* n = logs.search(p);
        if (n != nullptr) n->getData().pop();
    }

    
    void process() {
    
    }

    //void addOrder(Order p) {
    //orders.push(p)
    //}


   void Undo() {
       cout << "Undoing";
       if (GlobalUndo.isEmpty()) return;
        ActionLog c = GlobalUndo.pop();

        if (c == 2) {
            if (!last.isEmpty()) {
                Stock p2 = last.pop();
                line.enqueue(p2);
                node<Stock>* p1 = logs.search(p2);
                if (p1 != nullptr) {
                    int rem = p1->data.getQuantity();
                    rem--;
                    if (p1 != nullptr) p1->data.setQuantity(rem);
                    p1->data.pop();
                }
            }
        }
        else if (c == 1) {
            Stock dummy;
            dummy.id = c.Id;
            line.deleteEnd();
            logs.delete_node(dummy);
        }
        else if (c == 3) {
            logs.insert(last.pop());
        }
        else if (c == 4) {
            Stock dummy;
            dummy.id = c.Id;
            node<Stock>* g=logs.search(dummy);
            g->data.UndoRestock();
        }
    }

    void display_undos() {
        GlobalUndo.display();
    }


    void discontinue_item(int i) {
        Stock d;
        d.id = i;
        node<Stock>* f  = logs.search(d);
        Stock x = f->data;
        ActionLog x1(2, x.id);
        GlobalUndo.push(x1);
        last.push(x);
        logs.delete_node(d);
        logs.displayInOrder();
    }


    void ReEnterStock(int i) {
        Stock d;
        d.id = i;
        node<Stock>* f = logs.search(d);
        Stock x = f->data;
        f->data.Restock();
        ActionLog x1(4, x.id);
        GlobalUndo.push(x1);
    }

    void displayUrgent() { Pending_line.display(); }
    void displayLine() { line.display(); }
};

int Stock::id_count = 0;


    int main() {
        Amaazon hub;

        
        Stock p1, p2, p3;
        p1.name = "Laptops";
        p2.name = "Phones";
        p3.name = "Headphones";

      
        StockModification stockAtBeginning(0);
        p2.push(stockAtBeginning);
        p2.push(stockAtBeginning);

        
        hub.insertStock(p1);
        hub.insertStock(p2);
        hub.insertStock(p3);
        hub.display();
        hub.ProcessStock();
        hub.display();
        hub.display_undos();
        hub.ReEnterStock(1);
        hub.display();
        hub.discontinue_item(1);
        cout << "Undoing";
        hub.Undo();
        

 
        hub.display();
        p1.displayStack();
        

        return 0;
    }