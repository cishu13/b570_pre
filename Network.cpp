# include <iostream>
# include <fstream>
# include <sstream>
# include <stdexcept>
# include "Network.h"

using std::string, std::vector, std::ifstream, std::istringstream, std::stringstream;

Network::Network() : users({}), posts({}), tags({}) {}

/**
 * Loads users and posts from a file into the network database.
 * 
 * The function reads a file line by line and differentiates between users and posts
 * based on the first word (type identifier) on each line:
 * 
 * - If the line starts with "User", it's treated as a user entry.
 *   Format: "User <username>"
 *   The function extracts the username and adds it to the database.
 * 
 * - If the line starts with "Post", it's treated as a post entry.
 *   Format: "Post <postId> <username> <message content>"
 *   The function extracts the post ID, username, and message text,
 *   then adds the post to the database.
 * 
 * The differentiation is done by reading the first token from each line
 * and comparing it against "User" or "Post" string literals.
 * Any line that doesn't start with either keyword results in an error.
 * 
 * @param fileName The path to the file to load
 * @throws std::invalid_argument if the file cannot be opened
 * @throws std::runtime_error if the file format is invalid
 */
void Network::loadFromFile(string fileName) {
    ifstream file(fileName);

    // Check if the file is open
    if (!file.is_open()) {
        throw std::invalid_argument("Unable to open file");
    }

    string line;
    // Read file line by line
    while (getline(file, line)) {
        istringstream ss(line);
        string type;
        // Extract the first word to determine the type (User or Post)
        ss >> type;

        // Check if this line represents a User entry
        // User lines have format: "User <username>"
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
        } 
        // Check if this line represents a Post entry
        // Post lines have format: "Post <id> <username> <message content>"
        else if (type == "Post") {
            unsigned int id;
            string text;
            string userName;

            // Extract post ID (numeric identifier)
            ss >> id;
            // Extract username (author of the post)
            ss >> userName;

            // Read the rest of the line as the post text/message content
            getline(ss, text);

            // Handle potential errors in parsing
            if (ss.fail() || text.empty()) {
                throw std::runtime_error("Runtime Error");
            }

            // Remove leading whitespace from text (getline includes the space)
            text = text.substr(1);

            try {
                addPost(id, userName, text);
            } catch (const std::invalid_argument& e) {
                throw std::runtime_error("Runtime Error");
            }
        } else {
            // The line doesn't start with "User" or "Post"
            // Handle unexpected input - file format is invalid
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

unsigned int Network::getMaxPostId() {
    unsigned int maxId = 0;
    for (unsigned int i = 0; i < posts.size(); ++i) {
        if (posts[i]->getPostId() > maxId) {
            maxId = posts[i]->getPostId();
        }
    }
    return maxId;
}

bool Network::userExists(string userName) {
    string lowerUserName = userName;
    for (unsigned int i = 0; i < lowerUserName.length(); i++) {
        lowerUserName[i] = tolower(lowerUserName[i]);
    }
    for (unsigned int i = 0; i < users.size(); i++) {
        if (users[i]->getUserName() == lowerUserName) {
            return true;
        }
    }
    return false;
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