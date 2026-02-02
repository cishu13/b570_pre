# include <string>
# include <stdexcept>
# include "Tag.h"

using std::string, std::vector;

Tag::Tag(string tagName) : tagName(tagName), tagPosts({}) {
    // TODO: implement constructor checks
    int tagLength = tagName.length();

    if(tagLength < 2 || tagName[0] != '#' || (tagName[tagLength - 1] == '!' || tagName[tagLength - 1] == ',' || tagName[tagLength - 1] == '.' || tagName[tagLength - 1] == '?'))
    {
        throw std::invalid_argument("Invalid Tag Start/Length");
        return;
    }
    else if(tagName[1] > 122 or tagName[1] < 61)
    {
        throw std::invalid_argument("Invalid Tag First Letter");
    }

    for(int i = 0; i < tagLength; i++)
    {
        if(tagName[i] >= 41 and tagName[i] <= 90)
        {
            throw std::invalid_argument("Invalid Tag, Capitalization");
            return;
        }
    }


}

string Tag::getTagName() {
    return tagName;
}

vector<Post*>& Tag::getTagPosts() {
    return tagPosts;
}

void Tag::addTagPost(Post* post) {

    if(post == nullptr)
    {
        throw std::invalid_argument("Invalid Post");
        return;
    }

    tagPosts.push_back(post);
}
