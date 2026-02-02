# CPPeers Social Network

## Repo简介

**CPPeers** 是一个基于 C++ 开发的简单社交网络系统，支持从文本文件加载帖子数据、按用户或标签搜索帖子、以及查找最热门的标签。

**目标**：提供一个命令行社交网络平台，用户可以加载和管理帖子数据，进行各种查询操作。

**主要功能**：
- 从文本文件加载用户和帖子数据
- 按用户名查询帖子
- 按标签（hashtag）查询帖子
- 查找最热门的标签

**技术栈**：
- **语言**：C++
- **部署**：支持 Docker 容器化构建与运行

**项目结构**：
- `main.cpp` - 主程序入口，包含菜单和用户交互逻辑
- `Network.cpp/h` - 网络类，管理用户、帖子和标签数据
- `User.cpp/h` - 用户类
- `Post.cpp/h` - 帖子类
- `Tag.cpp/h` - 标签类
- `*.txt` - 示例数据文件

## 题目Prompt

I'm making a basic social media network in C++, where users can input a text file containing posts, search the posts by user or hashtag, or find the most popular hashtag. Please create a function in 'main.cpp' that allows the user to create a post and add it to the database. The function should prompt the user for their username, then prompt them for their message content. If all inputs are valid, the function should register the user in the database if they are new, and add the post to the database, with a new post ID that is higher than any other post in the database. Add this function as an option in the main menu print statement, and add it as a case in the 'main' function in 'main.cpp'. Additionally, could you add comments to the 'loadFromFile' function in 'Network.cpp' that explain how it differentiates between users and posts? This function takes in a file path, and adds new users and posts to the database accordingly.

## PR链接

https://github.com/cishu13/b570_pre/pull/1
