# include <iostream>
# include <fstream>
# include <sstream>
# include <stdexcept>
# include "Network.h"

using std::string, std::vector, std::ifstream, std::istringstream, std::stringstream;

Network::Network() : users({}), posts({}), tags({}) {}

void Network::loadFromFile(string fileName) {
    ifstream file(fileName);

// Check if the file is open
    if (!file.is_open()) {
        throw std::invalid_argument("Unable to open file");
    }

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string type;
        ss >> type;

        if (type == "User") {
            string userName;
            ss >> userName;
            if (ss.fail()) {
                throw std::runtime_error("Runtime Error");
            }

            try {
                addUser(userName);
            } catch (const std::invalid_argument& e) {
                throw std::runtime_error("Runtime Error");
            }
        } else if (type == "Post") {
            unsigned int id;
            string text;
            string userName;

            ss >> id;
            ss >> userName;

        // Read the rest of the line as text
            getline(ss, text);

        // Handle potential errors
            if (ss.fail() || text.empty()) {
                throw std::runtime_error("Runtime Error");
            }

        // Remove leading whitespace from text
            text = text.substr(1);

            try {
                addPost(id, userName, text);
            } catch (const std::invalid_argument& e) {
                throw std::runtime_error("Runtime Error");
            }
        } else {
        // Handle unexpected input
            throw std::runtime_error("Runtime Error");
        }
    }

    file.close();
}

void Network::addUser(string userName) {
    string string = userName;
  //letters to lowercase
    for(unsigned int i = 0; i < string.length(); i++) {
        string[i] = tolower(string[i]);
    }
  //does the username exist
    for(unsigned int i = 0; i < users.size(); i++){
        if(users[i] -> getUserName() == string){
            throw std::invalid_argument("username already exists");
        }
    }
    //user constructor, dont catch exceptions
    User *newUser = new User(userName); //creates user
  
    this -> users.push_back(newUser); //adds user

    std::cout << "Added User " << userName << std::endl;
}

void Network::addPost(unsigned int postId, string userName, string postText) {
    int userexists = 0;
    for (unsigned int i = 0; i < users.size(); i++) {
        if (userName == users.at(i)->getUserName()) {
            userexists = 1;
        }
    }
    if (userexists == 0) {
        throw std::invalid_argument("There is no user with this name");
    }

    bool postcheck = false;
    for (unsigned int i = 0; i < posts.size(); i++) {
        if (postId == posts.at(i)->getPostId()) {
            postcheck = true;
        }
    }
    if (postcheck) {
        throw std::invalid_argument("Id for post already exists");
    }

    Post* post = new Post(postId, userName, postText);
    posts.push_back(post);

    for (unsigned int j = 0; j < users.size(); j++) {
        if (userName == users.at(j)->getUserName()) {
            users.at(j)->addUserPost(post);
        }
    }
    vector<string> posttags = post->findTags();

    for (unsigned int a = 0; a < posttags.size(); a++) {
        for (unsigned int b = 0; b < tags.size(); b++) {
            if (posttags.at(a) == tags.at(b)->getTagName()) {
                tags.at(b)->addTagPost(post);
            }
        }
        try {
            Tag* ptag = new Tag(posttags.at(a));
            tags.push_back(ptag);
            ptag->addTagPost(post);
        } catch (const std::invalid_argument& e) {
            continue;
        }
    }
    std::cout << "Added Post " << postId << " by " << userName << std::endl;
}

vector<Post*> Network::getPostsByUser(string userName) {
    if (userName.empty()) {
        throw std::invalid_argument("Username is empty");
    }

    for (unsigned int i = 0; i < users.size(); ++i) {
        if (userName == users[i]->getUserName()) {
            return users[i]->getUserPosts();
        }
    }

    throw std::invalid_argument("Username not found in the network");
    
}

vector<Post*> Network::getPostsWithTag(string tagName) {
    if (tagName == " ") {
        throw std::invalid_argument("Username Error");
    }
    for (unsigned int i = 0; i < tags.size(); ++i) {
        if (tags[i]->getTagName() == tagName) {
            return tags[i]->getTagPosts();
        }
    }
    throw std::invalid_argument("Username Error");
}

vector<string> Network::getMostPopularHashtag() {
    vector<string> popHashtags;

        unsigned int b = 0;

    for(unsigned int i = 0; i < tags.size(); i++) {
        if(b< tags.at(i) -> getTagPosts().size()) {
            b = tags.at(i) -> getTagPosts().size();
        }
    }


    for(unsigned int i = 0; i < tags.size(); i++) {
        if(b == tags.at(i)->getTagPosts().size()) {
            popHashtags.push_back(tags.at(i)->getTagName());
        }
    }

    return popHashtags;
}

Network::~Network() {
    for (unsigned int i = 0; i < users.size(); ++i) {
        delete users.at(i);
    }

    for (unsigned int i = 0; i < tags.size(); ++i) {
        delete tags.at(i);
    }
    
    for (unsigned int i = 0; i < posts.size(); ++i) {
        delete posts.at(i);
    }
}