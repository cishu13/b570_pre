# include <iostream>
# include <string>
# include <stdexcept>
# include <vector>
# include "Post.h"

using std::string, std::vector, std::cout, std::endl;

Post::Post(unsigned int postId, string userName, string postText) : postId(postId), userName(userName), postText(postText) {
    if (postId == 0 || userName == "" || postText == "") {
        throw std::invalid_argument("post constructor: invalid parameter values");
    }
}

unsigned int Post::getPostId() {
    return postId;
}

string Post::getPostUser() {
    return userName;
}

string Post::getPostText() {
    return postText;
}

//cleans up the tag into standardized words (lowercase, no punc)
void tagClean(string& tagString){

    //makes a copy for transformation
    string cleanString = tagString;
    int length = tagString.length();
    
    //converts to lowercase
    for(int i = 0; i < length; i++)
    {
        cleanString[i] = tolower(cleanString[i]);
    }

    //removes punctuation
    //! , . ?

    //incriments from back of string
    int index = length - 1;
    char currentValue = cleanString[index];
    //goes until we hit a non punctuation or the #
    while(((currentValue == '!') or (currentValue == ',') or (currentValue == '.') or (currentValue == '?')) and (index > 0)) 
    {
        //deletes all punctuation
        cleanString.erase(index);
        index--;
        currentValue = cleanString[index];      
    }

    tagString = cleanString;

    return;
}

vector<string> dupliRemove(vector<string> tagList)
{
    vector<string> newList = {};

    int tagListSize = tagList.size();
    bool inList = false;

    //for each tag in taglist,
    for(int i = 0; i < tagListSize; i++)
    {

        //check each tag in newList
        for(int j = 0; j < newList.size(); j++)
        {
            //compare the two tags
            if(newList.at(j).compare(tagList.at(i)) == 0)
            {
                //if they are the same, say so
                inList = true;
            }
        }      

        //after we finish comparing
        if(not inList)
        {
            newList.push_back(tagList.at(i));
        }  
    }

    return newList;
}

vector<string> Post::findTags() {
    // TODO: extracts candidate tags based on occurrences of # in the post

    //variable declaration
    vector<string> tags; //vector of all tags
    int postLength = postText.length(); //length of the text
    string wordString; //used to analyze words in the for loop
    char currentChar;

    if(postLength < 1)
    {
        return tags;
    } 

    //goes through each char of postLenght
    for(int i = 0; i < postLength + 1; i++)
    {   
        currentChar = postText[i];
        //while still a word and still in the file
        if((currentChar != ' ') and (i != postLength))
        {
            //add to wordString
            wordString += currentChar;
        }
        else //when we hit a space
        {
            if(wordString.length() < 1)
            {
                wordString.clear();
            }
            else if(wordString[0] == '#')
            {
                tags.push_back(wordString);
            }
            wordString.clear();
        }
    }

    for(int i = 0; i < tags.size(); i++)
    {
        tagClean(tags.at(i));
    }

    tags = dupliRemove(tags);
    

    return tags;
}
