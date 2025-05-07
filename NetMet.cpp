#include <bits/stdc++.h>
// #include <iostream>
// #include <unordered_map>
// #include <vector>
// #include <queue>
// #include <set>
#include <fstream>
#include <sstream>

using namespace std;

class NetMet {
    unordered_map<string, vector<string>> adjList;  // Adjacency list to store friendships

public:
    // Add a new user to the network
    void addUser(const string &username) {
        if (adjList.find(username) == adjList.end()) {
            adjList[username] = {};  // Create an empty list for the user
            cout << "\n---------------------------------------------------\n";
            cout << username << " added to NetMet.\n";
            cout << "---------------------------------------------------\n";
        } else {
            cout << username << " already exists.\n";
        }
    }

    void addUser2(const string &username) {
        if (adjList.find(username) == adjList.end()) {
            adjList[username] = {};  // Create an empty list for the user

        } 
    }

    // Add a friendship (an edge between two users)
    void addFriendship(const string &user1, const string &user2) {
        if (adjList.find(user1) != adjList.end() && adjList.find(user2) != adjList.end()) {
            if (user1 == user2) {
                cout << "Not valid to add yourself as a friend.\n";
            } else {
                adjList[user1].push_back(user2);
                adjList[user2].push_back(user1);
                cout << "\n---------------------------------------------------\n";
                cout << " Friendship successfully created between " << user1 << " and " << user2 << ".\n";
                cout << "---------------------------------------------------\n";
            }
        } else {
            cout << "One or both users do not exist.\n";
        }
    }

    void addFriendship2(const string &user1, const string &user2) {
        if (adjList.find(user1) != adjList.end() && adjList.find(user2) != adjList.end()) {
              adjList[user1].push_back(user2);

        }
    }

    // Remove a friendship
    void removeFriendship(const string &user1, const string &user2) {
        if (adjList.find(user1) != adjList.end() && adjList.find(user2) != adjList.end()) {
            auto &friends1 = adjList[user1];
            auto &friends2 = adjList[user2];

            // Remove user2 from user1's friend list
            friends1.erase(remove(friends1.begin(), friends1.end(), user2), friends1.end());
            // Remove user1 from user2's friend list
            friends2.erase(remove(friends2.begin(), friends2.end(), user1), friends2.end());
            cout << "\n---------------------------------------------------\n";
            cout << "Friendship removed between " << user1 << " and " << user2 << ".\n";
            cout << "---------------------------------------------------\n";
        } else {
            cout << "One or both users do not exist.\n";
        }
    }

    // Display users and their friends
    void displayNetwork() {
        cout << "\n========== NetMet Network =============\n";
        for (auto &user : adjList) {
            cout << user.first << ": ";
            for (auto &friendUser : user.second) {
                cout << friendUser << " ";
            }
            cout << endl;
        }
        cout<<"===========================================\n";
    }

    // Save the network to a file
    void saveToFile(const string &filename) {
        ofstream file(filename);
        if (file.is_open()) {
            // Save users
            for (const auto &user : adjList) {
                file << user.first << endl; // Save each user on a new line
            }
            file << "FRIENDS\n"; // Separator for friends

            // Save friendships
            for (const auto &user : adjList) {
                if (!user.second.empty()) {
                    file << user.first << ":";
                    for (const auto &friendUser : user.second) {
                        file << " " << friendUser;
                    }
                    file << endl;
                }
            }
            file.close();
            cout << "Network saved to " << filename << endl;
        } else {
            cout << "Failed to open file for saving.\n";
        }
    }

    // Load the network from a file
    void loadFromFile(const string &filename) {
        ifstream file(filename);
        if (file.is_open()) {
            adjList.clear();  // Clear the existing network before loading
            string line;

            // Load users
            while (getline(file, line) && line != "FRIENDS") {
                addUser2(line);
            }

            // Load friendships
            while (getline(file, line)) {
                stringstream ss(line);
                string username;
                getline(ss, username, ':');  // Read the username until the colon
                string friendName;

                while (ss >> friendName) {  // Read all friends
                    addFriendship2(username, friendName);
                }
            }
            file.close();
            cout << "Network loaded from " << filename << endl;
        } else {
            cout << "Failed to open file for loading.\n";
        }
    }

    // Find mutual friends between two users
    void findMutualFriends(const string &user1, const string &user2) {
        if (adjList.find(user1) != adjList.end() && adjList.find(user2) != adjList.end()) {
            set<string> friendsOfUser1(adjList[user1].begin(), adjList[user1].end());
            set<string> mutualFriends;
            for (auto &friendUser : adjList[user2]) {
                if (friendsOfUser1.find(friendUser) != friendsOfUser1.end()) {
                    mutualFriends.insert(friendUser);
                }
            }
            cout<<"---------------------------------------------------------------------------\n";
            cout << "Mutual Friends of " << user1 << " and " << user2 << "\n";
            for (auto &friendUser : mutualFriends) {
                cout << friendUser << " ";
            }
            if (mutualFriends.empty()) {
                cout << "None";
            }
            cout << endl;
            cout<<"---------------------------------------------------------------------------\n";

            
        } else {
            cout << "[Error] One or both users do not exist.\n";
        }
    }


    // Menu-driven interface  
    void menu() {
        string userInput;
        while (true) {
            cout<<"\n============== NetMet Menu ================\n";
          
            cout << "1. Add User\n";
            cout << "2. Add Friendship\n";
            cout << "3. Remove Friendship\n";
            cout << "4. Display Network\n";
            cout << "5. Save Network to File\n";
            cout << "6. Load Network from File\n";
            cout << "7. Find Mutual Friends\n";
            cout << "8. Exit\n";
            cout<<"===========================================\n";

            cout << "Select an option: ";
            cin >> userInput;

            if (userInput == "1") {
                // Add user
                string username;
                cout << "Enter username: ";
                cin >> username;
                addUser(username);
            } else if (userInput == "2") {
                // Add friendship
                string user1, user2;
                cout << "Enter first user's name: ";
                cin >> user1;
                cout << "Enter second user's name: ";
                cin >> user2;
                addFriendship(user1, user2);
            } else if (userInput == "3") {
                // Remove friendship
                string user1, user2;
                cout << "Enter first user's name: ";
                cin >> user1;
                cout << "Enter second user's name: ";
                cin >> user2;
                removeFriendship(user1, user2);
            } else if (userInput == "4") {
                // Display network
                displayNetwork();
            } else if (userInput == "5") {
                // Save network to file
                string filename;
                cout << "Enter filename to save (e.g., network.txt): ";
                cin >> filename;
                saveToFile(filename);
            } else if (userInput == "6") {
                // Load network from file
                string filename;
                cout << "Enter filename to load (e.g., network.txt): ";
                cin >> filename;
                loadFromFile(filename);

            } else if (userInput == "7") {
                // Find mutual friends
                string user1, user2;
                cout << "Enter first user's name: ";
                cin >> user1;
                cout << "Enter second user's name: ";
                cin >> user2;
                findMutualFriends(user1, user2);

            } else if (userInput == "8") {
                // Exit program
                cout << "Exiting NetMet. Goodbye!\n";
                break;
            } else {
                cout << "Invalid option. Please try again.\n";
            }
        }
    }
};

int main() {
    NetMet network;
    cout<<"===========================================\n";
    network.loadFromFile("network.txt");
    cout<<"===========================================\n";
    network.menu();  // Start the menu-driven interface
    cout<<"===========================================\n";
    network.saveToFile("network.txt");
    cout<<"===========================================\n\n";
    return 0;
}
