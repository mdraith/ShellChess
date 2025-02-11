# ShellChess
Shell Chess is a text based brute force chess program for the Linux Terminal.


Extract for ARM 64-Bit Linux:

tar -xJf shellchess-linux-arm64-1.0.tar.xz

Extract for Intel or AMD 64-Bit Linux:

tar -xJf shellchess-linux-x86_64-1.0.tar.xz


A new directory ShellChess will be created.


Just enter the move you want to make in small letters.


To play the black pieces enter the command 'side'.


For a much weaker opponent enter 'dpth' and after pressing Enter a number between '1' (very weak) and '3' (novice).


To make it faster you can compile like this:


clang -O3 -flto -o chess chess.c && strip chess


To benchmark code changes do the following:

'dpth' should be set to a matching depth maybe '10' | 'extn' should be off to disable move extension | 'rand' should be off to disable random moves | 'book' should be off to disable book openings | 'test' to start the benchmark from a test position


"Every chess master was once a beginner."
(Irving Chernev)

Keywords: shell, chess, game, board, linux, text, play, terminal, cli, unicode
