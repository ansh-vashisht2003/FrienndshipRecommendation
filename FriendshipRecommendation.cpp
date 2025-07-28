#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <memory>
#include <sstream>

using namespace std;

struct User {
    string name;
    int age;
    string city;
    vector<string> interests;
    unordered_set<string> friends;
};

class SocialNetwork {
private:
    unordered_map<string, shared_ptr<User>> users;

    static void displayUser(const User& user) {
        cout << "Name: " << user.name << ", Age: " << user.age
             << ", City: " << user.city << "\nInterests: ";
        for (const auto& interest : user.interests) cout << interest << ", ";
        cout << "\nFriends: ";
        for (const auto& f : user.friends) cout << f << ", ";
        cout << "\n";
    }

public:
    void addUser(const string& name, int age, const string& city, const vector<string>& interests) {
        if (users.count(name)) {
            cout << "User already exists.\n";
            return;
        }
        auto user = make_shared<User>(User{name, age, city, interests});
        users[name] = user;
        cout << name << " added successfully.\n";
    }

    void addFriendship(const string& a, const string& b) {
        if (a == b || !users.count(a) || !users.count(b)) {
            cout << "Invalid friendship request.\n";
            return;
        }
        users[a]->friends.insert(b);
        users[b]->friends.insert(a);
        cout << a << " and " << b << " are now friends.\n";
    }

    void removeFriendship(const string& a, const string& b) {
        if (!users.count(a) || !users.count(b)) return;
        users[a]->friends.erase(b);
        users[b]->friends.erase(a);
        cout << "Friendship between " << a << " and " << b << " removed.\n";
    }

    void showProfile(const string& name) {
        if (!users.count(name)) {
            cout << "User not found.\n";
            return;
        }
        displayUser(*users[name]);
    }

    void recommendByMutuals(const string& name) {
        if (!users.count(name)) return;
        unordered_map<string, int> mutualCounts;

        for (unordered_set<string>::const_iterator it = users[name]->friends.begin(); it != users[name]->friends.end(); ++it) {
            const string& f = *it;
            for (unordered_set<string>::const_iterator fit = users[f]->friends.begin(); fit != users[f]->friends.end(); ++fit) {
                const string& fof = *fit;
                if (fof != name && users[name]->friends.count(fof) == 0)
                    mutualCounts[fof]++;
            }
        }

        vector<pair<string, int>> sorted(mutualCounts.begin(), mutualCounts.end());
        sort(sorted.begin(), sorted.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });

        cout << "Mutual friend recommendations for " << name << ":\n";
        for (vector<pair<string, int>>::const_iterator it = sorted.begin(); it != sorted.end(); ++it)
            cout << "- " << it->first << " (" << it->second << " mutual friends)\n";
    }

    void recommendByInterest(const string& name) {
        if (!users.count(name)) return;
        unordered_map<string, int> score;
        const vector<string>& myInterests = users[name]->interests;

        for (unordered_map<string, shared_ptr<User>>::const_iterator it = users.begin(); it != users.end(); ++it) {
            const string& otherName = it->first;
            const shared_ptr<User>& otherUser = it->second;

            if (otherName == name || users[name]->friends.count(otherName)) continue;

            int match = 0;
            for (size_t i = 0; i < myInterests.size(); ++i) {
                if (find(otherUser->interests.begin(), otherUser->interests.end(), myInterests[i]) != otherUser->interests.end())
                    match++;
            }
            if (match > 0) score[otherName] = match;
        }

        vector<pair<string, int>> sorted(score.begin(), score.end());
        sort(sorted.begin(), sorted.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });

        cout << "Interest-based friend recommendations for " << name << ":\n";
        for (vector<pair<string, int>>::const_iterator it = sorted.begin(); it != sorted.end(); ++it)
            cout << "- " << it->first << " (" << it->second << " shared interests)\n";
    }

    void listUsersInCity(const string& city) {
        cout << "Users in " << city << ":\n";
        for (unordered_map<string, shared_ptr<User>>::const_iterator it = users.begin(); it != users.end(); ++it) {
            const shared_ptr<User>& user = it->second;
            if (user->city == city)
                cout << "- " << user->name << " (Age: " << user->age << ")\n";
        }
    }

    void mutualFriends(const string& a, const string& b) {
        if (!users.count(a) || !users.count(b)) return;
        cout << "Mutual friends:\n";
        for (unordered_set<string>::const_iterator it = users[a]->friends.begin(); it != users[a]->friends.end(); ++it) {
            if (users[b]->friends.count(*it))
                cout << "- " << *it << "\n";
        }
    }
};

vector<string> splitInterests(const string& input) {
    stringstream ss(input);
    string word;
    vector<string> result;
    while (getline(ss, word, ',')) {
        word.erase(remove_if(word.begin(), word.end(), ::isspace), word.end());
        if (!word.empty()) result.push_back(word);
    }
    return result;
}

int main() {
    SocialNetwork sn;
    int choice;
    string a, b, city, interests;
    int age;

    while (true) {
        cout << "\n--- Social Network Menu ---\n"
             << "1. Add User\n2. Add Friendship\n3. Remove Friendship\n4. Show Profile\n"
             << "5. Recommend by Mutual Friends\n6. Recommend by Interests\n"
             << "7. Show Mutual Friends\n8. List Users by City\n9. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                getline(cin, a);
                cout << "Enter age: ";
                cin >> age;
                cin.ignore();
                cout << "Enter city: ";
                getline(cin, city);
                cout << "Enter interests (comma-separated): ";
                getline(cin, interests);
                sn.addUser(a, age, city, splitInterests(interests));
                break;
            case 2:
                cout << "Enter two usernames: ";
                cin >> a >> b;
                sn.addFriendship(a, b);
                break;
            case 3:
                cout << "Enter two usernames: ";
                cin >> a >> b;
                sn.removeFriendship(a, b);
                break;
            case 4:
                cout << "Enter username: ";
                cin >> a;
                sn.showProfile(a);
                break;
            case 5:
                cout << "Enter username: ";
                cin >> a;
                sn.recommendByMutuals(a);
                break;
            case 6:
                cout << "Enter username: ";
                cin >> a;
                sn.recommendByInterest(a);
                break;
            case 7:
                cout << "Enter two usernames: ";
                cin >> a >> b;
                sn.mutualFriends(a, b);
                break;
            case 8:
                cout << "Enter city name: ";
                cin.ignore();
                getline(cin, city);
                sn.listUsersInCity(city);
                break;
            case 9:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}
