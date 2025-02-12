# ShellChess
Shell Chess is a text based brute force chess program for the Linux Terminal.


Extract for ARM 64-Bit Linux:  
`tar -xJf shellchess-linux-arm64-1.0.tar.xz`

Extract for Intel or AMD 64-Bit Linux:  
`tar -xJf shellchess-linux-x86_64-1.0.tar.xz`


A new directory *ShellChess* will be created.


For starting the binary program:  
`cd ShellChess && ./chess`


Just enter the move you want to make in small letters: **e2e4**


Enter the command **side** to play the black pieces.


For a much weaker opponent, enter **dpth** and after pressing Return, a number between **1** (very weak) and **3** (novice) with Return.


To make it faster, you can compile the program like this:  
`clang -O3 -flto -o chess chess.c && strip chess`


To benchmark modified code, perform the following commands:  
- **dpth** should be set to a matching depth maybe **10**  
- **extn** should be off to disable move extension  
- **rand** should be off to disable random moves  
- **book** should be off to disable book openings  
- **test** starts the calculation of a test position


"Every chess master was once a beginner."
(Irving Chernev)

Keywords: shell, chess, game, board, linux, text, play, terminal, cli, unicode
