#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <cctype>
using namespace std;

string GetLine() {
  string line;
  getline(cin, line);
  return line;
}

void OpenUserFile(ifstream& input) {
  while(true) {
    cout << "Enter filename: ";
    string filename = GetLine();

    input.open(filename.c_str());
    if(input.is_open()) return;

    cout << "Sorry, I can't find the file " << filename << endl;
    input.clear();
  }
}

string GetFileContents(ifstream& input) {
  string result;

  string line;
  while(getline(input, line))
    result += line + "\n";
  
  return result;
}

set<string> LoadKeywords() {
  ifstream input("keywords.txt");
  set<string> result;

  string keyword;
  while(input >> keyword)
    result.insert(keyword);

  return result;
}

void PreprocessString(string& text) {
  for(size_t k = 0; k < text.size(); ++k)
    if(ispunct(text[k]) && text[k] != '_') text[k] = ' ';
}

map<string, size_t> GenerateKeywordReport(string fileContents) {
  set<string> keywords = LoadKeywords();

  PreprocessString(fileContents);

  stringstream tokenizer;
  tokenizer << fileContents;

  map<string, size_t> result;

  string word;
  while(tokenizer >> word)
    if (keywords.count(word))
      ++result[word];

  return result;
}

int main() {
  /* Prompt the user for a valid file and open it as a stream */
  ifstream input;
  OpenUserFile(input);

  /* Generate the report based on the contents of the file */
  map<string, size_t> report = GenerateKeywordReport(GetFileContents(input));

  /* Print a summary. */
  for (map<string, size_t>::iterator itr = report.begin(); itr!= report.end(); ++itr)
    cout << "Keyword " << itr->first << " occurred " << itr->second << " times." << endl;
}