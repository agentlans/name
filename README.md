# NAME: Name Abbreviation Maker Executable
Generates acronyms and abbreviations based on your keywords

## Install
Need C++ compiler and `make`. Just download this repository and run `make`. An executable file called `name` will be created in directory.

## Use

### Inputs
- keywords file (one line for each keyword describing your product)
- (optional) dictionary file containing meaningful words that can be used as acronyms.
  If this file isn't provided, then the program will use `google-10000-english.txt` file by default.

### Run
This runs the program and saves the results to a file called `Results.md`. May take a few minutes.
```bash
./name keywords.txt google-10000-english.txt > Results.md
```

### Output
Output is in Markdown format. File contains possible acronyms and keywords that match the letters in the acronym.
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

## Author, license
Copyright (C) 2019 Alan Tseng

License: GPL v3

