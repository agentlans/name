# NAME: Name Abbreviation Maker Executable
Generates acronyms and abbreviations based on your keywords

## Install
Need C++ compiler and `make`.

1. Download this repository and run `make`.
2. An executable file called `name` will be created in the directory.

## Use

Inputs:
- keywords file (one line for each keyword describing your product). Try to include words that start with vowels or other common English letters like T, N, S, H, R, D, L.
- (optional) dictionary file containing meaningful words that can be used as acronyms.
  If this file isn't provided, then the program will use `google-10000-english.txt` file by default.

Run:

This runs the program on `keywords.txt` and saves the results to `Results.md`. May take a few minutes.
```bash
./name keywords.txt google-10000-english.txt > Results.md
```

Output:

Output is in Markdown format and contains possible acronyms and keywords that match the letters in the acronym.

Example:
```
## PAGE

1. 
- Phrase, Program
- Abbreviation, Acronym, Acrostic, Algorithm, Alias, Application, Automatic
- GEnerator

2. 
- Phrase, Program
- Abbreviation, Acronym, Acrostic, Algorithm, Alias, Application, Automatic
- Generator
- Electronic, Epithet, Execution
```

## Author, license, acknowledgements
Copyright (C) 2019 Alan Tseng

License: GPL v3

google-10000-english.txt file is from https://github.com/first20hours/google-10000-english
