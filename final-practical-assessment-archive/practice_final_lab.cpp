// practice_final_lab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<vector>
#include<unordered_map>
using namespace std;
struct Job_Post {

        int ID;
        int Author_ID;
        string Content;
        vector<string>  Hashtags;
        int   Engagement_Score;
        int  Report_Count;
        long long Timestamp;


        friend ostream& operator<<(ostream& os, Job_Post &x) {
            os << "Post Id = " << x.ID << "\nUserId = " << x.Author_ID << " \nContent= " << x.Content << "\nEngagement_Score = " << x.Engagement_Score << "Timestamp = " << x.Timestamp;

            return os;
        }

};

struct User{
    int id;
    string name;
    int f_count;
    int activity_score;

    float get_influence_count(){
        return f_count * 0.6 + activity_score * 0.4;
    }

};


class Handler {
    unordered_map<int,vector< Job_Post>> posts_by_user;
    unordered_map<string, vector<Job_Post>> P_by_hash;


    void DisplayPosts(int id) {
        unordered_map<int, vector< Job_Post>>::iterator it = posts_by_user.find(id);
        if (it != posts_by_user.end()) {
            for (vector<Job_Post>::iterator temp = it->second.begin(); temp != it->second.end(); temp++) {
                cout << *temp;
            }
        
        }
        else {
            cout << "The user has never posted";
        }    
    }

    void SearchbyHash(string hash) {
        unordered_map<string, vector<Job_Post>> ::iterator it = P_by_hash.find(hash);
        if (it != P_by_hash.end()) {
            for (vector<Job_Post>::iterator temp = it->second.begin(); temp != it->second.end(); temp++) {
                cout << *temp;
            }

        }
        else {
            cout << "This hashtag does not exist";
        }
    }

    void deletePost(int Author_id, int id) {
        bool c = false;
        vector <string > h;
        auto it = posts_by_user.find(Author_id);
        if (it == posts_by_user.end()) { return; }
        else {
            for (auto temp = it->second.begin(); temp != it->second.end(); temp++) {
                if (id == temp->ID) {
                    h = temp->Hashtags;
                    it->second.erase(temp);
                    c = true;
                }
            }

        }
        if (c)
        {
            for (auto move = h.begin(); move != h.end(); move++) {
            
                auto check=P_by_hash.find(*move);
                if (check != P_by_hash.end()) {
                
                    for (auto mover = check->second.begin(); mover != check->second.begin(); mover++) {
                        if (mover->ID == id) {
                            check->second.erase(mover)
                        }
                    }
                }
            }

        }
    }


};

int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
