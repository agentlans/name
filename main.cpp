/*
    NAME: Name Abbreviation Maker Executable
    Generates acronyms and abbreviations based on your keywords

    Copyright 2019 Alan Tseng

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <limits>
#include <cassert>

/* Splits string according to pattern and returns result.
pattern[i] = 1 means that str will be cut between characters i and i+1. */
std::vector<std::string> split(std::string str, int pattern)
{
	assert(str.size() > 0);
	std::vector<std::string> result;
	std::string temp = "";
	int i = 0;
	while (pattern) {
		temp += str[i];
		// If cut pattern is 1 then make a cut
		if (pattern % 2) {
			result.push_back(temp);
			temp = "";
		}
		pattern >>= 1;
		i++;
	}
	// Include the rest of the string
	auto rest_of_string = str.substr(i, std::string::npos);
	if (rest_of_string != "") {
		result.push_back(rest_of_string);
	}
	return result;
}

// Capitalizes the first few letters of x
std::string capitalize(std::string x, int num_letters) {
	auto xb = x.begin();
	std::for_each(xb, xb+num_letters, [](char &c) {
		c = ::toupper(c);
	});
	return x;
}

// Returns vector of words in word_list that have the given prefix.
// Assumes word_list is sorted.
std::vector<std::string> look_up(std::string prefix, const std::vector<std::string> word_list) {
	int pl = prefix.size();
	std::vector<std::string> matches;
	for (const auto &word : word_list) {
		if (word.substr(0, pl) == prefix) {
			matches.push_back(capitalize(word, pl));
			continue;
		}
		if (word.substr(0, pl) > prefix) break;
	}
	return matches;
}

// Exception we throw when we can't expand acronym with splitted words
class CantExpandException : public std::exception
{
	const char *what() const throw()
	{
		return "No valid expansions for this word.";
	}
};

// Expands the parts of a string using the given sorted word list
std::vector<std::vector<std::string>>
expand_parts(std::vector<std::string> parts, const std::vector<std::string> &word_list)
{
	std::vector<std::vector<std::string>> result;
	for (const auto &part : parts) {
		auto possible_words = look_up(part, word_list);
		if (possible_words.size() == 0) {
			throw CantExpandException();
		}
		result.push_back(possible_words);
	}
	return result;
}

// Cuts string into consecutive substrings and finds expansions for each substring
// using the words from word_list
std::vector<std::vector<std::vector<std::string>>>
split_and_expand(std::string str, const std::vector<std::string> &word_list)
{
	int ss = str.size();
	int max_pattern = 1 << ss;
	std::vector<std::vector<std::vector<std::string>>> results;
	for (int pattern = 0; pattern < max_pattern; ++pattern) {
		auto parts = split(str, pattern);
		try {
			auto expansion = expand_parts(parts, word_list);
			results.push_back(expansion);
		} catch (const CantExpandException &e) {
			// Go to next pattern if we can't expand this pattern
			continue;
		}
	}
	return results;
}

// Joins vector of strings separated by delimiter
std::string join(std::vector<std::string> vec, std::string delimiter)
{
	std::string temp = "";
	auto ve = vec.end();
	for (auto p = vec.begin(); p < ve; ++p) {
		if (p != ve-1) {
			temp += (*p + delimiter + " ");
		} else {
			temp += *p;
		}
	}
	return temp;
}

// Reads a file containing list of words
std::vector<std::string> read_word_list(std::string filename, const int max_word_len = 10)
{
	std::string line;
	std::ifstream f (filename);
	// Store the words in vector
	std::vector<std::string> results;
	if (f.is_open()) {
		while (getline(f, line)) {
			if (line != "" && line.size() <= max_word_len) {
				results.push_back(line);
			}
		}
		f.close();
		return results;
	} else {
		throw "Can't open file " + filename;
	}
}

// Shows results of splitting a string and expanding each part as a single string
std::string write_output(
std::vector<std::vector<std::vector<std::string>>> result)
{
	std::string temp = "";
	// Number each expansion
	int counter = 1;
	for (const auto &pattern : result) {
		temp += (std::to_string(counter) + ". \n");
		for (const auto &expansion : pattern) {
			temp += "- " + join(expansion, ",") + "\n";
		}
		temp += "\n";
		counter++;
	}
	// Remove the last character and return
	return temp.substr(0, temp.size()-1);
}

int main(int argc, char* argv[])
{
	// Parse command line parameters
	std::string keyword_file, dict_file;
	switch (argc) {
		case 2:
			keyword_file = argv[1];
			dict_file = "google-10000-english.txt";
			break;
		case 3:
			keyword_file = argv[1];
			dict_file = argv[2];
			break;
		default:
			std::cout << "Usage: csign keyword_file [dictionary_file]" << std::endl;
			exit(1);
	}

	// Open the files containing the words
	auto dictionary = read_word_list(dict_file, 10); // Only short words (< 10 letters)
	auto word_list = read_word_list(keyword_file, std::numeric_limits<int>::max());
	std::sort(word_list.begin(), word_list.end());

	// See whether which words in dictionary can form meaningful acronyms and print results
	for (const auto &word : dictionary) {
		auto expansions = split_and_expand(word, word_list);
		auto result = write_output(expansions);
		if (result != "") {
			std::cout << "## " << capitalize(word, word.size()) << "\n" << std::endl;
			std::cout << result << std::endl;
		}
	}

	return 0;
}

