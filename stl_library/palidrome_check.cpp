#include <string>
#include <cctype>
#include <sstream>
#include <vector>

using namespace std;

bool IsNotAlpha(char ch)
{
  return !isalpha(ch);
}

bool IsPalindrome(string input)
{
  input.erase(remove_if(input.begin(), input.end(), IsNotAlpha), input.end());

  transform(input.begin(), input.end(), input.begin(), ::toupper);

  return equal(input.begin(), input.begin() + input.size() / 2, input.rbegin());
}

bool IsNotAlphaOrSpace(char ch)
{
  return !isalpha(ch) && !isspace(ch);
}

bool IsWordPalindrome(string input)
{
  input.erase(remove_if(input.begin(), input.end(), IsNotAlphaOrSpace), input.end());

  transform(input.begin(), input.end(), input.begin(), ::toupper);

  stringstream tokenizer(input);
  vector<string> tokens;

  tokens.insert(tokens.begin(), istream_iterator<string>(tokenizer), istream_iterator<string>());

  return equal(tokens.begin(), tokens.begin() + tokens.size() / 2, tokens.rbegin());
}