#ifndef CONSTANTS_H
#define CONSTANTS_H

const char USERS_FILE_PATH[] = "data/users.json";
const char POSTS_FILE_PATH[] = "data/posts.json";
const char MAIN_MENU[] = "--------Welcome to Instagram--------\n1. Sign up\n2. Sign in\n3. Exit\nEnter your choice: \n";
const char INVALID_INPUT[] = "Invalid Input. Please try again\n";
const char EXITING[] = "Exiting...\n";
const char INVALID_CHOICE[] = "Invalid choice\n";
const char SEPARATOR1[] = "\n----------------------\n";
const char SEPARATOR2[] = "\n==============================================\n";
const char ENTER_USERNAME[] = "Enter username: ";
const char ENTER_PASSWORD[] = "Enter password: ";
const char ENTER_FULL_NAME[] = "Enter your full name: ";
const char ACCOUNT_CREATION_SUCCESS[] = "Account created Successfully\n";
const char USERNAME_NOT_AVAILABLE[] = "Username not available\n";
const char INVALID_USERNAME_MESSAGE[] = "Invalid Username\n";
const char INVALID_PASSWORD_MESSAGE[] = "Incorrect password\n";
const char SIGNED_IN_SUCCESS[] = "Signed in successfully\n";
const char SIGNED_IN_USER_MENU[] = "1. Go to profile\n2. View a post\n3. View all posts\n4. View likes on a post\n5. Sign Out\nEnter your choice: ";
const char SIGNING_OUT[] = "Signing out...\n";
const char PROFILE_MENU[] = "1. Edit Profile\n2. View Profile\n3. Create Post\n4. Delete Post\n5. View my posts\n6. Delete Account\n7. Back\nEnter your choice: ";
const char ENTER_POST_ID[] = "Enter post id: ";
const char RETURNING_TO_MAIN_MENU[] = "Returning to main menu...\n";
const char POST_NOT_FOUND[] = "Post not found.\n";
const char CONTENT[] = "Content = ";
const char USERNAME[] = "Username = ";
const char TIMESTAMP[] = "Timestamp = ";
const char POST_ID[] = "Post ID = ";
const char LIKES[] = "Likes = ";
const char FULL_NAME[] = "Full Name = ";
const char ALREADY_LIKED_UNLIKE_PROMPT[] = "You have already liked this post.\nDo you want to unlike it?\n1. Yes\n2. No\nEnter your choice: ";
const char POST_UNLIKED[] = "Post Unliked\n";
const char POST_LIKED[] = "Post Liked\n";
const char LIKE_POST_PROMPT[] = "Do you want to like this post?\n1. Yes\n2. No\nEnter your choice: ";
const char NO_POSTS_AVAILABLE[] = "No posts available.\n";
const char ALL_POSTS[] = "---------- All Posts ----------\n";
const char EDIT_PROFILE_MENU[] = "\n------ Edit Profile ------\n1. Change Full Name\n2. Change Password\n3. Go Back\nEnter your choice: ";
const char ENTER_NEW_FULL_NAME[] = "Enter new full name: ";
const char FULL_NAME_UPDATE_SUCCESS[] = "Full name updated successfully!\n";
const char ENTER_NEW_PASSWORD[] = "Enter new password: ";
const char PASSWORD_UPDATE_SUCCESS[] = "Password updated successfully!\n";
const char ENTER_CAPTION[] = "Enter the caption for your post: ";
const char YOUR_PROFILE[] = "---------Your Profile---------\n";
const char CAPTION_NOT_EMPTY[] = "Caption cannot be empty\n";
const char POST_CREATION_SUCCESS[] = "Post created successfully! Post id: ";
const char POST_CREATION_FAILED[] = "Failed to create post\n";
const char ERROR_ONLY_DELETE_OWN_POSTS[] = "You can only delete your own posts\n";
const char POST_DELETION_SUCCESS[] = "Post deleted successfully.\n";
const char POST_DELETION_FAILED[] = "Failed to delete post.\n";
const char YOUR_POSTS[] = "---------Your Posts---------\n";
const char USER_HAS_NO_POSTS[] = "You have not created any posts yet.\n";
const char ENTER_POST_ID_VIEW_LIKES[] = "Enter the post id to view likes: ";
const char NO_LIKES_ON_POST[] = "No likes yet on this post.\n";
const char USERS_LIKES_POST[] = "\n--- Users who liked this post ---\n";
const char PROMPT_CONFIRM_DELETE_ACCOUNT[] = "Are you sure you want to delete your account?\n1. Yes\n2. No\nEnter your choice: ";
const char ACCOUNT_DELETION_SUCCESS[] = "Your account and all posts have been deleted successfully\n";
const char ACCOUNT_DELETION_FAILURE[] = "Failed to delete user\n";
const char ACCOUNT_DELETION_CANCELLED[] = "Account deletion cancelled\n";
const char MSG_NO_POSTS_CREATED[] = "You have not created any posts yet.\n";
const char USERNAME_LABEL[] = "username";
const char PASSWORD_LABEL[] = "password";
const char FULLNAME_LABEL[] = "fullname";
const char POST_ID_LABEL[] = "postId";
const char TIMESTAMP_LABEL[] = "timestamp";
const char LIKERS_LABEL[] = "likers";
const char CONTENT_LABEL[] = "content";
const char INVALID_JSON[] = "{ invalid json ]";

const char TEST_USERNAME1[] = "User1";
const char TEST_PASSWORD1[] = "Password1";
const char TEST_ENCODED_PASSWORD1[] = "Sdvvzrug4";
const char TEST_FULLNAME1[] = "User1 Full Name";
const char TEST_USERNAME2[] = "User2";
const char TEST_USERNAME3[] = "User3";
const char TEST_PASSWORD2[] = "Password2";
const char TEST_FULLNAME2[] = "User2 Full Name";
const char TEST_CONTENT1[] = "Hello world";
const char TEST_TIMESTAMP[] = "2025-11-16 11:42:15";
const char TEST_USERS_FILE[] = "test_users.json";
const char TEST_POSTS_FILE[] = "test_posts.json";

const int TEST_POST1_ID = 15;
const int TEST_POST2_ID = 16;
const int TEST_POST3_ID = 17;

enum SignInStatus
{
    SIGN_IN_SUCCESS,
    INVALID_USERNAME,
    INVALID_PASSWORD
};

#endif
