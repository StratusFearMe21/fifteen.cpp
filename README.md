# fifteen.cpp
a sliding puzzle game for the command line powered by ncurses
# But why tho?
I have a laptop, and that laptop has a limited battery life. Luckily linux has a mode where you can only have a text based terminal, and nothing else, no Desktop enviornment, better battery life. I've found a decent 2048 game (https://github.com/tiehuis/2048-cli), but I have yet to find a sliding puzzle game that has a customizeable size, and is as light as possible, and can run in the terminal. So I made one.
# Customize board size
I couldn't figure out how to pass in command line options so the only way to change it is in the code and then to compile it again.
# Compiling
- get the dependencies
**sudo apt-get install libncurses5-dev libncursesw5-dev g++**`
- compile the code
**git clone https://github.com/StratusFearMe21/fifteen.cpp.git
cd fifteen
g++ fifteen.cpp -lncursesw -o fifteen**
# Running
**./fifteen**
