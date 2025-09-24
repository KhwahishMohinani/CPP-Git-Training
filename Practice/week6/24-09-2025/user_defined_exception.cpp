#include <iostream>
#include <filesystem>
#include <exception>

class VideoPlayerException : public std::exception
{
    const char *err_msg;

public:
    VideoPlayerException(const char *msg)
        : err_msg(msg)
    {
    }
    const char *what() const throw() // The base class std::exception::what() has this exact signature: virtual const char* what() const noexcept;
    {
        return err_msg;
    }
};

int main()
{
    try
    {
        std::string file_path = "path to video file";

        if (!std::filesystem::exists(file_path))
        {
            throw VideoPlayerException("File doesn't exist\n");
        }
        else
        {
            // play the video
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what();
    }
    return 0;
}