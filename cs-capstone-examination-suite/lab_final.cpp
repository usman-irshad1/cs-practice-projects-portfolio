// lab_final.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <unordered_map>
#include <list>
#include <string>
#include <vector>
#include<utility>
#include <queue>
#include<map>
#include "trie.h"
#include"heap.h"
#include"Huffman.h"
#include<algorithm>
using namespace std;






struct User {
    int user_id;
    string name;
    int f_count;
    vector<string> interest;
    vector<string> activity_id;
    
    User() {
        f_count = 0;
    }
};

struct Activity {
    string id;
    int user_id;
    string category;
    int time;
    string venue;
    int max;
    int current;
    string post_context;
    int status;


    int report_count;
    bool operator<(const Activity& other) const {
        return status  >other.status;
    }
};

// 0 is peniding 1 is apprroced and 2 is removed maeaning it has been preocessed;

class POST_Backend {
unordered_map<string , Activity> Activity_Storage;
unordered_map<pair<string, int>, Activity> venue_Storage;
unordered_map<string, vector<string>>  catorgory_database;
unordered_map<int, User> User_activity;
map<int, Activity > sorter;
Trie search_names;

public:
    POST_Backend() {}





    void addCatorogy(string id, string catogory) {

        if (Activity_Storage.find(id) == Activity_Storage.end()) {

            cout << "The activity does not exist in the Storage";
        }
        else {
            Activity_Storage.at(id).category = catogory;
            catorgory_database[catogory].push_back(id);

        }
    }


    void delete_registartion(int id, string actitity) {
        auto it = User_activity.find(id);
        if (it == User_activity.end()) { return; }
        else {
        
                Activity_Storage.find(actitity)->second.current--;
            
                for (auto temp = it->second.activity_id.begin(); temp != it->second.activity_id.end(); temp++) {
                    if (*temp == actitity) {
                        it->second.activity_id.erase(temp);                 
                    }
                }
        }
    
    }

    bool time_confilcts(int user_id) {

        auto it = User_activity.find(user_id);
        if (it == User_activity.end()) { return true; }
        else
        {
            int timer = 0;
            for (auto temp = it->second.activity_id.begin(); temp != it->second.activity_id.end(); temp++) {
                auto time = Activity_Storage.find(*temp);
                timer = time->second.time;
                for (auto temp1 = temp; temp1 != it->second.activity_id.end(); temp1++) {
                    if (timer == Activity_Storage.find(*temp1)->second.time) {
                        cout << "The activity " << Activity_Storage.find(*temp1)->second.id << "is confilicting with" << Activity_Storage.find(*temp)->second.id << endl;
                        return false;
                    }
                }     
            }
            return true;
        }

    }

    bool venue_check(string id,int time) {
        pair<string, int> key = make_pair(id, time);
        auto temp= venue_Storage.find(key);
        if (temp != venue_Storage.end()) {
            venue_Storage[key] = Activity_Storage.find(id)->second;
            return true;
        }
        else {
            cout << "The venue is alreadu reserved";
            return false;
        }
    }
    
    void register_for_acivity(int user_id, string id) {
        if (Activity_Storage.find(id)->second.current < Activity_Storage.find(id)->second.max) { return; }
        if (User_activity.find(user_id) == User_activity.end()) {
            User temp;
            temp.activity_id.push_back(id);
            User_activity[user_id] = temp;
            return;
        }
        else {
            User_activity[user_id].activity_id.push_back(id);
            bool flag=time_confilcts(user_id);
            if (!flag) {
                User_activity[user_id].activity_id.pop_back();
                cout << "cant be scheduled";
            }
            else {
                cout<<"scheduled";
                Activity_Storage.find(id)->second.current++;
            }
        }
    }




    Activity* access(string Activity) {
        if (Activity_Storage.find(Activity) == Activity_Storage.end()) {
            cout << "The activity does not exist in the Storage";
            return nullptr;
        }
        else {
            return &(Activity_Storage.at(Activity));
        }
    }


   
   
    void add_Activity(string post_id, Activity x) {
       bool flag= venue_check(post_id, x.time);
       if (flag) {
           Activity_Storage[post_id] = x;
           Activity& it = Activity_Storage[post_id];
           it.id = post_id;

           catorgory_database[x.category].push_back(it.id);


       }
    }


    void searchbycatogort(string x) {
        auto it = catorgory_database.find(x);
        if (it == catorgory_database.end()) {
            cout << "The hashtag " << x << " cant be found";
        }
        else {
            for (auto temp = it->second.begin(); temp != it->second.end(); temp++) {
                cout << *temp<<endl;
            }
        }
    
    }
    void search_and_rank_catreofy_activitues(string x) {
        priority_queue<pair<int, string>> sorter;
        auto it = catorgory_database.find(x);
        if (it == catorgory_database.end()) {
            cout << "The catorgory " << x << " cant be found";
        }
        else {
            for (auto temp = it->second.begin(); temp != it->second.end(); temp++) {
                pair<int, string> engengment= { Activity_Storage.at(*temp).current , *temp };
                sorter.push(engengment);
            }
        }

        while (sorter.size() != 0) {
            cout << sorter.top().second;
            sorter.pop();
        }

    }

    void search_and_rank_Popularity_by_catorgort() {
        priority_queue<pair<int, string>> sorter;
        for (auto temp = catorgory_database.begin(); temp != catorgory_database.end(); temp++) {
            int score=0;
            for (auto it = temp->second.begin(); it != temp->second.end(); it++) {
                score += Activity_Storage[*it].current;
        }
            pair engamegemt = { score, temp->first };
            sorter.push(engamegemt);
        }

        while (sorter.size() != 0) {
            cout << sorter.top().second;
            sorter.pop();
        }
    }

    void rankby_time() {
        
        for (auto it = Activity_Storage.begin(); it != Activity_Storage.end(); it++) {

            sorter[it->second.time] = it->second;
        }
        for (auto t = sorter.begin(); t != sorter.end(); t++) {
            cout << t->second.id << endl;
            cout << t->second.category << endl;
            cout << t->second.time << endl;
            cout << t->second.venue<< endl;
        
        }
    
    }


    void search_users(string x) {
       
        vector<string> matches = search_names.getWordsWithPrefix(x);

      
        if (matches.empty()) {
            cout << "No users found with prefix: " << x << endl;
            return;
        }

       
        for (const string& name : matches) {
            cout << "- " << name << endl;
        }
    }


    void generate_system_report() {
        cout << "\nSYSTEM REPORT " << endl;

        rankby_time();
        search_and_rank_Popularity_by_catorgort();
    }
     void recommend_activites(int id){
         auto temp=User_activity.find(id);
         for (auto it = temp->second.interest.begin(); it != temp->second.interest.end(); it++) {
             search_and_rank_catreofy_activitues(*it);
         }


     }
   
};


int main() {
    POST_Backend instagram;
    int choice;
    string p_id, content, tag, search_prefix;

    while (true) {
        cout << "\n--- Activities Backend ---" << endl;
        cout << "1. Create Activity (Auto-Approved)\n";
        cout<<"2 for recommendations";
        cout << "4. View Activity Details\n";
        cout << "5. Update Activity Content\n";
        cout << "6. Delete User Activity\n";
        cout << "7. Search Users by Prefix (Trie)\n";
        cout << "8. Generate System Report\n";
        cout << "9. Exit\n";
        cout << "Enter choice: \n";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 9) break;

        switch (choice) {
        case 1: {
            Activity new_post;
            cout << "Enter Post ID: \n";
            cin >> p_id;
            cout << "Enter Catorgory: \n";
            cin.ignore();
            getline(cin, new_post.category);
            cout << "Enter a hashtag: \n";
            cin >> tag;
            new_post.status = 1;
            new_post.report_count = 0;
            instagram.add_Activity(p_id, new_post);
            break;
        }
      
        case 4: {
            cout << "Enter  ID: \n";
            cin >> p_id;
            Activity* retrieved = instagram.access(p_id);
            if (retrieved) {
                cout << "\n--- Details ---\n";
                cout << "User: " << retrieved->id << "\n";
                cout << "Catrogiry: " << retrieved->category << endl;
                cout << "Registered: " << retrieved->current << endl;
            }
            break;
        }
        case 5: {
            //cout << "Enter Post ID: \n";
            //cin >> p_id;
            //cout << "Enter new content: \n";
            //cin.ignore();
            //getline(cin, content);
            //instagram.update(p_id, content);
            //break;
        }
        case 6: {
            cout << "Enter User ID: \n";
            int i;
            cin >> i;
            cout << "enter categhory";
            string x;
            cin >> x;
            instagram.delete_registartion(i,x );
            break;
        }
        case 7: {
            cout << "Enter name prefix: \n";
            cin >> search_prefix;
            cout << "\nSearch Results:\n";
            instagram.search_users(search_prefix);
            break;
        }
        case 8: {
            instagram.generate_system_report();
            break;
        }
        default:
            cout << "\nInvalid selection.\n";
        }
    }
    return 0;
}
