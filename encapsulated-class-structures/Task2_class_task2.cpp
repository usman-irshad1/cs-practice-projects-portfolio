// Task2_class_task2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"Header1.h"

using namespace std;
template <int size>
class Airlines {
    Graph<string, size> spirit;
public:
    Airlines() : spirit(true) {}

    void insertNode(string vertex){
        spirit.insertVertex(vertex);
    }

    void insertRoute(string vertex, string vertex1, int distance ) {
        int a = spirit.getIndex(vertex);
        int b = spirit.getIndex(vertex1);
        spirit.makeEdge(a, b, distance);
    }

    void deleteAirport(string verte) {
        spirit.DeleteVertex(verte);
    }

    void deleteFlight(string vertex, string vertex1) {
        spirit.DeleteEdge(vertex, vertex1);
    }

    void FlightExist(string a, string b) {
        spirit.edgeExist(a, b);
    }

    void Display() {
        spirit.bfs();
    }
    void display_Flights_of_Airoprt(string a) {
        spirit.display_edge_of_index(a);
    
    }

    void shortestPath(string vertex, string vertex2){
        spirit.shortest_Path_btw2_vericex(vertex, vertex2);
    }


    void incomingflight(string t) {
        spirit.Incoming(t);
    }

    void displayStats() {
        cout << "\n--- Flight Network Statistics ---" << endl;
        cout << "Total Airports : " << spirit.getVertex() << endl;
        cout << "Total Flight Routes : " << spirit.No_Of_Edges() << endl;
    }

    void mostSimplePath(){
        Graph<string, size> boeing=spirit.minimumSpanningtree();
        boeing.bfs();
    }
};







int main() {

    Airlines<10> spiritAirlines;

    spiritAirlines.insertNode("KHI"); // Karachi
    spiritAirlines.insertNode("LHE"); // Lahore
    spiritAirlines.insertNode("ISB"); // Islamabad
    spiritAirlines.insertNode("USA"); // Dubai

    spiritAirlines.insertRoute("KHI", "USA", 1200);
    spiritAirlines.insertRoute("KHI", "LHE", 1230);
    spiritAirlines.insertRoute("KHI", "ISB", 1203);
    spiritAirlines.insertRoute("LHE", "ISB", 300);
    spiritAirlines.insertRoute("ISB", "KHI", 1100);

    cout << "--- Flight Network Overview ---" << endl;
    spiritAirlines.Display();
    cout << endl;

    cout << "--- Checking Specific Airport Connections ---" << endl;
    spiritAirlines.display_Flights_of_Airoprt("KHI");
    spiritAirlines.display_Flights_of_Airoprt("LHE");

    cout << "\nDeleting flight from KHI to LHE..." << endl;
    spiritAirlines.deleteFlight("KHI", "LHE");
    spiritAirlines.display_Flights_of_Airoprt("KHI");
    cout << endl;

    spiritAirlines.shortestPath("LHE", "USA");

    spiritAirlines.incomingflight("USA");
    cout << endl << endl;
    spiritAirlines.displayStats();

    cout << endl<<endl;
    spiritAirlines.mostSimplePath();
    return 0;
}