# include <iostream>
# include <string>
# include <stdexcept>
# include "Network.h"

using std::cout, std::cin, std::endl, std::string, std::vector;

void printMenu() {
    cout << "Welcome to CPPeers" << endl;
    cout << "The options are: " << endl;
    cout << "1. load data file and add information" << endl;
    cout << "2. show posts by user" << endl;
    cout << "3. show posts with hashtag" << endl;
    cout << "4. show most popular hashtag" << endl;
    cout << "5. create a new post" << endl;
    cout << "9. quit" << endl;
    cout << "--------> Enter your option: ";
}

void processLoad(Network& cppeers) {
    string fileName = "";
    cout << "Enter filename: ";
    cin >> fileName;
    cppeers.loadFromFile(fileName);
}

void processPostsByUser(Network& cppeers) {
    string username= "";
    cout<<"Enter username: ";
    cin>>username;
    vector<Post*> userPos = cppeers.getPostsByUser(username);
    for(unsigned int i = 0; i < userPos.size(); i++){
        for(unsigned int j = 0; j < userPos[i]->getPostText().size(); j++){
            cout << userPos[i] -> getPostText().at(j);
        }
        cout << endl;
    }
    
}

void processPostsWithHashtags(Network& cppeers) {
    string tagName = "";
    cout << "Enter tagname: ";
    cin >> tagName;
    vector<Post*> postsWHashtags = cppeers.getPostsWithTag(tagName);
    for(unsigned int i = 0; i < postsWHashtags.size(); i++){
        for(unsigned int j = 0; j < postsWHashtags[i]->getPostText().size(); j++){
            cout << postsWHashtags[i] -> getPostText().at(j);
        }
        cout << endl;
    }
    

}

void processMostPopularHashtag(Network& cppeers) {
    vector<string> popularHT = cppeers.getMostPopularHashtag();
    for(unsigned int i = 0; i < popularHT.size(); i++){
        cout << popularHT.at(i) << endl;
    }
}

void processCreatePost(Network& cppeers) {
    string username = "";
    string messageContent = "";
    
    // Prompt user for username
    cout << "Enter username: ";
    cin >> username;
    
    // Validate username is not empty
    if (username.empty()) {
        cout << "Error: Username cannot be empty." << endl;
        return;
    }
    
    // Clear input buffer before reading message content
    cin.ignore();
    
    // Prompt user for message content
    cout << "Enter message content: ";
    getline(cin, messageContent);
    
    // Validate message content is not empty
    if (messageContent.empty()) {
        cout << "Error: Message content cannot be empty." << endl;
        return;
    }
    
    // Register user if they are new
    if (!cppeers.userExists(username)) {
        try {
            cppeers.addUser(username);
        } catch (const std::exception& e) {
            cout << "Error adding user: " << e.what() << endl;
            return;
        }
    }
    
    // Generate new post ID (higher than any existing post)
    unsigned int newPostId = cppeers.getMaxPostId() + 1;
    
    // Add the post to the database
    try {
        cppeers.addPost(newPostId, username, messageContent);
        cout << "Post created successfully!" << endl;
    } catch (const std::exception& e) {
        cout << "Error creating post: " << e.what() << endl;
    }
}

int main() {

    try {
        Network cppeers;

        int choice = 0;

        do {
            printMenu();
            cin >> choice;
            switch(choice) {
                case 1: {
                    processLoad(cppeers);
                    break;
                }
                case 2: {
                    processPostsByUser(cppeers);
                    break;
                }
                case 3: {
                    processPostsWithHashtags(cppeers);
                    break;
                }
                case 4: {
                    processMostPopularHashtag(cppeers);
                    break;
                }
                case 5: {
                    processCreatePost(cppeers);
                    break;
                }
            }
        } while (choice != 9);
    } catch (std::exception& exc) {
        std::cout << exc.what() << endl;
    }

    return 0;
}