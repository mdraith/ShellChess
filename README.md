# ShellChess
Shell Chess is a text-based brute-force chess program for the Linux Terminal.  

If you don't have Linux, try running it with the app *Termux* on your smartphone.

Extract for ARM 64-Bit Linux:  
`tar -xJf shellchess-linux-aarch64-1.0.tar.xz`

Extract for Intel or AMD 64-Bit Linux:  
`tar -xJf shellchess-linux-x86-64-1.0.tar.xz`

A new directory *ShellChess* will be created.

For starting the binary program:  
`cd ShellChess && ./chess`

Just enter the move you want to make in small letters: **e2e4**

Enter the command **side** to play the black pieces.

To weaken the opponent, enter **dpth**, press Return, and choose a number between **1** (very weak) and **3** (novice).

To make it faster, you can compile the program like this:  
`clang -O3 -flto -o chess chess.c && strip chess`

If you have modified the code and want to benchmark it, use the following settings:
- **dpth** should be set to a matching depth of maybe **10**  
- **extn** should be off to disable move extensions  
- **rand** should be off to disable random moves  
- **book** should be off to disable book openings  
- **test** starts the calculation of a test position

"Every chess master was once a beginner."
(Irving Chernev)
