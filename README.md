<h1 align="center"> ⏩ <strong>Get_next_line</strong> </h1>

## 🏷️ **About the project**
> Reading a line from a fd is way too tedious

This project is about coding a function that returns a line read from a file descriptor.

## ⚙️ **Requirements**
The function must be written in C. It must compile with clang and the following flags :
- [x] -Wall
- [x] -Wextra
- [x] -Werror

lseek(), global variables and your libft are forbidden.

## ➡️ **Difference with the original printf**
> Don't implement the buffer management of the original printf

We have to handle the following conversions: cspdiuxX% for our mandatory part.

## 📍 **Bonus**
What to do for the bonus part:
> - Manage any combination of the following flags: ’-0.’ and the field minimum width under all conversions.
> - Manage all the following flags: ’# +’ (Yes, one of them is a space)

I started to do the bonus when my madatory part worked perfectly which is a **BIG** mistake. As stated in the subject :
> If you plan to complete the bonus part, think about the implementation of your extra features from the start. This way, you will avoid the pitfalls of a naive approach.

Doing the bonus meant re-doing all my functions so I gave up.
You can still see part of my code for the bonus, it can give you hints on how to do it. Just check `ft_check_flags_bonus.c`.

## 🧠 **New notions**
If you have trouble understanding the subject fully and the new notions like `file descriptors` or `read` I highly recommand these:

- https://42-cursus.gitbook.io/guide/rank-01/get_next_line
- https://www.youtube.com/watch?v=xgDSXNOHTIA

It really helped me understand the subject better.

## ♻️ **Testing**
I strongly recommand you do your own main function to test your program. *You can check mine to see what it should look like.*

Once you have your main, test it with this command line:
> cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o *executable_name*

Like explicited in the subject, test your functions with different BUFFER_SIZE, for example **0**, **42**, **9999** and **10000000**.
Test it on different files, you can take the ones I created or create your own!

If you want to make sure your program works, you can use third party testers like:
- https://github.com/xicodomingues/francinette
- https://github.com/Tripouille/gnlTester
