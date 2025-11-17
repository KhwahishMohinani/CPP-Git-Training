#include "Instagram.h"
#include "FileHandler.h"
#include "UserManager.h"
#include "PostManager.h"
#include "constants.h"
#include "InputHandler.h"
#include <iostream>
#include <limits>

void Instagram::run()
{
    fileHandler = new FileHandler(USERS_FILE_PATH, POSTS_FILE_PATH);
    userManager = new UserManager(fileHandler);
    postManager = new PostManager(fileHandler);

    std::cout << SEPARATOR2;
    int choice;
    do
    {
        choice = getValidInt(MAIN_MENU);
        switch (choice)
        {
        case 1:
        {
            signUpMenu();
            break;
        }
        case 2:
        {
            signInMenu();
            break;
        }
        case 3:
        {
            std::cout << EXITING;
            break;
        }
        default:
        {
            std::cout << INVALID_CHOICE;
            break;
        }
        }
    } while (choice != 3);

    deleteAllData();
    delete fileHandler;
    delete userManager;
    delete postManager;
}

int Instagram::getValidInt(const std::string &prompt)
{
    InputHandler inputHandlerObject;
    IInputHandler *inputHandler = &inputHandlerObject;
    std::string input;
    int value;
    while (true)
    {
        std::cout << prompt;
        std::cin >> input;
        if (inputHandler->isValidInt(input, value) && value >= 0)
        {
            return value;
        }
        std::cout << INVALID_INPUT;
    }
}

void Instagram::signUpMenu()
{
    std::string username, password, fullname;
    std::cout << ENTER_USERNAME;
    std::cin >> username;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << ENTER_PASSWORD;
    std::cin >> password;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << ENTER_FULL_NAME;
    std::getline(std::cin, fullname);
    bool status = userManager->signUp(username, password, fullname);
    std::cout << SEPARATOR2;
    if (status)
    {
        std::cout << ACCOUNT_CREATION_SUCCESS;
    }
    else
    {
        std::cout << USERNAME_NOT_AVAILABLE;
    }
    std::cout << SEPARATOR2;
}

void Instagram::signInMenu()
{
    std::cout << SEPARATOR2;
    std::string username, password, fullname;
    std::cout << ENTER_USERNAME;
    std::cin >> username;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << ENTER_PASSWORD;
    std::cin >> password;
    int errorCode = userManager->signIn(username, password);
    if (errorCode == INVALID_USERNAME)
    {
        std::cout << INVALID_USERNAME_MESSAGE;
    }
    else if (errorCode == INVALID_PASSWORD)
    {
        std::cout << INVALID_PASSWORD_MESSAGE;
    }
    else
    {
        std::cout << SIGNED_IN_SUCCESS;
        IUser *user = userManager->getUserAccount(username);
        signedInUserMenu(user);
    }
}

void Instagram::signedInUserMenu(IUser *user)
{
    bool userDeleted = false;
    int choice;
    do
    {
        std::cout << SEPARATOR2;
        choice = getValidInt(SIGNED_IN_USER_MENU);
        switch (choice)
        {
        case 1:
            userDeleted = profileMenu(user);
            break;
        case 2:
            viewPostMenu(user);
            break;
        case 3:
            viewAllPosts();
            break;
        case 4:
            viewLikesMenu(user);
            break;
        case 5:
            std::cout << SEPARATOR2;
            std::cout << SIGNING_OUT;
            std::cout << SEPARATOR2;
            break;
        default:
            std::cout << INVALID_CHOICE;
            break;
        }
    } while (choice != 5 && !userDeleted);

    if (userDeleted)
        std::cout << RETURNING_TO_MAIN_MENU;
}

bool Instagram::profileMenu(IUser *user)
{
    bool accountDeleted = false;
    int choice;
    do
    {
        std::cout << SEPARATOR2;
        choice = getValidInt(PROFILE_MENU);
        switch (choice)
        {
        case 1:
            editProfileMenu(user);
            break;
        case 2:
            viewProfileMenu(user);
            break;
        case 3:
            createPostMenu(user);
            break;
        case 4:
            deletePostMenu(user);
            break;
        case 5:
            viewUserPostsMenu(user);
            break;
        case 6:
            accountDeleted = deleteUserMenu(user);
            break;
        case 7:
            break;
        default:
            std::cout << INVALID_CHOICE;
            break;
        }
    } while (choice != 7 && !accountDeleted);

    return accountDeleted;
}

void Instagram::viewPostMenu(IUser *user)
{
    int postId = getValidInt(ENTER_POST_ID);

    std::cout << SEPARATOR2;
    IPost *post = postManager->getPost(postId);
    if (!post)
    {
        std::cout << POST_NOT_FOUND;
        return;
    }

    std::cout << CONTENT << post->getPostContent() << "\n";
    std::cout << POST_ID << post->getPostId() << " | ";
    std::cout << USERNAME << post->getUsername() << " | ";
    std::cout << TIMESTAMP << post->getTimestamp() << "\n";
    std::cout << LIKES << post->getLikeCount() << "\n";

    bool alreadyLiked = post->hasLiked(user->getUsername());
    int choice;

    if (alreadyLiked)
    {
        std::cout << SEPARATOR1;
        choice = getValidInt(ALREADY_LIKED_UNLIKE_PROMPT);
        if (choice == 1)
        {
            postManager->removeLike(post, user->getUsername());
            std::cout << SEPARATOR1;
            std::cout << POST_UNLIKED;
        }
    }
    else
    {
        choice = getValidInt(LIKE_POST_PROMPT);
        if (choice == 1)
        {
            postManager->addLike(post, user->getUsername());
            std::cout << POST_LIKED;
        }
    }
}

void Instagram::viewAllPosts()
{
    const auto &posts = postManager->getAllPosts();
    std::cout << SEPARATOR2;

    if (posts.empty())
    {
        std::cout << NO_POSTS_AVAILABLE;
        return;
    }

    std::cout << ALL_POSTS;

    for (const auto &pair : posts)
    {
        IPost *post = pair.second;

        std::cout << CONTENT << post->getPostContent() << "\n";
        std::cout << POST_ID << post->getPostId() << " | ";
        std::cout << USERNAME << post->getUsername() << " | ";
        std::cout << TIMESTAMP << post->getTimestamp() << " | ";
        std::cout << LIKES << post->getLikeCount() << "\n";
        std::cout << SEPARATOR1;
    }
}

void Instagram::editProfileMenu(IUser *user)
{
    int choice;
    do
    {
        std::cout << SEPARATOR2;
        choice = getValidInt(EDIT_PROFILE_MENU);
        switch (choice)
        {
        case 1:
        {
            std::string newFullName;
            std::cout << ENTER_NEW_FULL_NAME;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(std::cin, newFullName);
            userManager->editProfile(user, "", newFullName);
            std::cout << FULL_NAME_UPDATE_SUCCESS;
            break;
        }
        case 2:
        {
            std::string newPassword;
            std::cout << ENTER_NEW_PASSWORD;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(std::cin, newPassword);
            userManager->editProfile(user, newPassword, "");
            std::cout << PASSWORD_UPDATE_SUCCESS;
            break;
        }
        case 3:
        {
            break;
        }
        default:
        {
            std::cout << INVALID_CHOICE;
            break;
        }
        }
    } while (choice != 3);
}

void Instagram::viewProfileMenu(IUser *user)
{
    std::cout << SEPARATOR2;
    std::cout << YOUR_PROFILE;
    std::cout << USERNAME << user->getUsername() << "\n";
    std::cout << FULL_NAME << user->getFullName() << "\n";
}

void Instagram::createPostMenu(IUser *user)
{
    std::string caption;

    std::cout << SEPARATOR2;
    std::cout << ENTER_CAPTION;
    std::getline(std::cin >> std::ws, caption);

    if (caption.empty())
    {
        std::cout << CAPTION_NOT_EMPTY;
        return;
    }

    IPost *post = postManager->createPost(user->getUsername(), caption);

    if (post)
    {
        postManager->addPost(post);
        std::cout << POST_CREATION_SUCCESS << post->getPostId() << "\n";
    }
    else
    {
        std::cout << POST_CREATION_FAILED;
    }
}

void Instagram::deletePostMenu(IUser *user)
{
    std::cout << SEPARATOR2;

    int postId = getValidInt(ENTER_POST_ID);

    IPost *post = postManager->getPost(postId);

    if (!post)
    {
        std::cout << POST_NOT_FOUND;
        return;
    }

    if (user->getUsername() != post->getUsername())
    {
        std::cout << ERROR_ONLY_DELETE_OWN_POSTS;
    }

    else
    {
        bool success = postManager->removePost(post);

        if (success)
        {
            postManager->deletePost(post);
            std::cout << POST_DELETION_SUCCESS;
        }
        else
        {
            std::cout << POST_DELETION_FAILED;
        }
    }
}

void Instagram::viewUserPostsMenu(IUser *user)
{
    std::map<int, IPost *, std::greater<int>> userPosts = postManager->getUserPosts(user->getUsername());
    std::cout << SEPARATOR2;

    if (userPosts.empty())
    {
        std::cout << MSG_NO_POSTS_CREATED;
        return;
    }

    std::cout << YOUR_POSTS;
    for (auto &[id, post] : userPosts)
    {
        std::cout << CONTENT << post->getPostContent() << "\n";
        std::cout << POST_ID << id << " | ";
        std::cout << TIMESTAMP << post->getTimestamp() << " | ";
        std::cout << LIKES << post->getLikeCount();
        std::cout << SEPARATOR1;
    }
}

void Instagram::viewLikesMenu(IUser *user)
{
    std::cout << SEPARATOR2;
    int postId = getValidInt(ENTER_POST_ID_VIEW_LIKES);

    IPost *post = postManager->getPost(postId);

    if (!post)
    {
        std::cout << POST_NOT_FOUND;
    }
    else
    {
        const auto &likers = post->getLikers();

        if (likers.empty())
        {
            std::cout << NO_LIKES_ON_POST;
            return;
        }

        std::cout << USERS_LIKES_POST;

        for (const auto &liker : likers)
        {
            std::cout << "- " << liker << "\n";
        }
    }
}

bool Instagram::deleteUserMenu(IUser *user)
{
    std::cout << SEPARATOR2;
    bool success = false;

    int choice = getValidInt(PROMPT_CONFIRM_DELETE_ACCOUNT);

    switch (choice)
    {
    case 1:
    {
        postManager->removePostsByUser(user->getUsername());
        postManager->removeLikesByUser(user->getUsername());
        bool userDeleted = userManager->deleteAccount(user);

        if (userDeleted)
        {
            std::cout << SEPARATOR2;
            std::cout << ACCOUNT_DELETION_SUCCESS;
            std::cout << SEPARATOR2;
            success = true;
        }
        else
        {
            std::cout << ACCOUNT_DELETION_FAILURE;
        }
        break;
    }

    case 2:
    {
        std::cout << ACCOUNT_DELETION_CANCELLED;
        break;
    }
    default:
    {
        std::cout << INVALID_CHOICE;
        break;
    }
    }

    return success;
}

void Instagram::deleteAllData()
{
    postManager->deleteAllPosts();
    userManager->deleteAllUsers();
}
