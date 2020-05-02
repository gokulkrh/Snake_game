# Guide

First install SDL2, open up a new terminal, copy and paste the command 'sudo apt-get install libsdl2-dev'.(if you are having issues installing, fix it on your own).

I made this game on ubuntu and didn't test it on windows, but it should work on windows since SDL is cross-platform, you may need to modify the code.

### To run the game(on linux)
Open up a terminal window, cd into the directory where the snake.c file is and run 'gcc snake.c -lSDL2main -lSDL2' to compile the program if you are using gcc compiler, otherwise figure it out on your own.

If everything goes well you can play the game by typing ./a.out into the terminal

Use arrow keys to control the snake, If the snake hits the boundary or itself the game exits and displays the score on the terminal.

### NOTE: 
This is my first attempt in making a game in C, so you may find the code to be less readable.  
I used this video as a guide to make the game (https://www.youtube.com/watch?v=AaGK-fj-BAM)  
If you find it hard to understand the code, your better off watching the video.  


Feel free to modify and use the code :)

