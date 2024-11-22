<h1 align="center"> ⏩ <strong>Get_next_line</strong> </h1>

## 🏷️ **About the project**
> Reading a line from a fd is way too tedious

This project is about coding a function that returns a line read from a file descriptor.

## ⚙️ **Requirements**
The function must be written in C. It must compile with clang and the following flags :
- [x] -Wall
- [x] -Wextra
- [x] -Werror

⛔ *lseek(), global variables and your libft are forbidden.*

## ➡️ **Specifications**
> Try to read as little as possible each time get_next_line() is called. If you encounter a new line, you have to return the current line. Don’t read the whole file and then process each line.

We have to return each line read in the fd including the terminating `\n` character, except if we reached the end of the file.

## 🗂️ **Files to turn in**
- **get_next_line.c** will contain our main function `char *get_next_line(int fd);`.
- **get_next_line.h** will contain *at least* the prototype of our main function. And the prototypes of our other functions.
- **get_next_line_utils.c** will contain other functions to help us achieve our goal.

## 📍 **Bonus**
What to do for the bonus part:
> - Develop `get_next_line()` using only one static variable.
> - Your `get_next_line()` can manage multiple file descriptors at the same time.

The bonuses were quite easy to do. I knew I wanted to do it when I started this project so I implemented only one static variable from the start.
As for the other bonus, it is also easy to set up.

*You can compare my `get_next_line.c` code with my `get_next_line_bonus.c` code to try and understand what I did* 😉

## 🦕 **My logic**
If you want to understand my code or just see my logic step by step you can check my `get_next_line_commented.c` in the 📁 "commented".

## 🧠 **New notions**
If you have trouble understanding the subject fully and the new notions like `file descriptors` or the function `read` I highly recommand these:

- https://42-cursus.gitbook.io/guide/rank-01/get_next_line
- https://www.youtube.com/watch?v=xgDSXNOHTIA

## ♻️ **Testing**
I strongly recommand you do your own main function to test your program. *You can check mine to see what it should look like.*

Once you have your main, test it with this command line:
> cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o *executable_name*

Like specified in the subject, test your functions with different BUFFER_SIZE, for example **0**, **42**, **9999** and **10000000**.
Test it on different files, you can take the ones I created or create your own!

If you want to make sure your program works, you can use third party testers like:
- https://github.com/xicodomingues/francinette
- https://github.com/Tripouille/gnlTester
