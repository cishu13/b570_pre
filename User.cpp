# include <string>
# include <stdexcept>
# include "User.h"
# include <iostream>

using std::string, std::vector, std::cout, std::endl;

User::User(string userName) : userName(userName), userPosts({}) {
    // TODO: implement constructor check
    //empty check
    if(userName == "")
    {
        throw(std::invalid_argument("Invalid Username"));
        return;
    }
    //first char is a letter check
    else if((int) userName[0] > 122 or (int)userName[0] < 61)
    {
        throw(std::invalid_argument("Invalid Username"));
        return;
    }

    //uppercase check
    for(int i = 0; i < userName.length(); i++)
    {
        if(userName[i] >= 41 and userName[i] <= 90)
        {
            throw std::invalid_argument("Invalid Username");
            return;
        }
    }
}

string User::getUserName() {
    return userName;
}

vector<Post*>& User::getUserPosts() {
    // TODO: implement getter
    return userPosts;
}

void User::addUserPost(Post* post) {
    
    if(post == nullptr)
    {
        throw std::invalid_argument("Invalid Post");
        return;
    }

    userPosts.push_back(post);
    return;
}
