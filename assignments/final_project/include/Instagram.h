#ifndef INSTAGRAM_H
#define INSTAGRAM_H

#include "IUserManager.h"
#include "IPostManager.h"

class Instagram
{
private:
    IUserManager *userManager;
    IPostManager *postManager;
    IFileHandler *fileHandler;

    int getValidInt(const std::string &prompt);
    void signUpMenu();
    void signInMenu();
    void signedInUserMenu(IUser *user);
    bool profileMenu(IUser *user);
    void viewPostMenu(IUser *user);
    void viewAllPosts();
    void viewLikesMenu(IUser *user);
    void editProfileMenu(IUser *user);
    void viewProfileMenu(IUser *user);
    void createPostMenu(IUser *user);
    void deletePostMenu(IUser *user);
    void viewUserPostsMenu(IUser *user);
    bool deleteUserMenu(IUser *user);
    void deleteAllData();

public:
    void run();
};

#endif
