# Minishell
##### __The goal of this project is to create a shell. My small Bash in C.__
---

### Features
- builtins: ``echo``, ``cd``, ``pwd``, ``export``, ``unset``, ``env``, ``exit``
- command separator: ``;`` 
- quotes: ``'`` ``"``
- redirects: ``<`` ``>`` ``>>``
- pipes: ``|``
- environment variable: ``$``
- exit status: ``$?``
- ``ctrl-C`` ``ctrl-D`` ``ctrl-\``
- termcaps:
    - up and down keys to navigate through the command history
    - edit the command (inline, not in history)
    
### Prerequisites
    - Makefile
    - GCC
    - libncurses5-dev (termcaps)

### Usage
    - make && ./minishell
    
### Steps
    1. lexing (= lexical analysis):
        - separate the input into tokens
        - tag them (builtin, executable, pipe, text ...)
    2. parsing:
        - determine the relationship between tokens to
        - establish the order of execution of the commands
    3. execution:
        - redirects
        - pipes
    4. termcaps (terminal capability):
        -  library and database which enables programs to use display computer terminals in a device-independent manner
    5. tests

![](https://github.com/eteillet/08-Minishell_/minishell.png)