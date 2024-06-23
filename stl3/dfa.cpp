#include <map>
#include <set>
#include <string>
using namespace std;

struct DFA {
  map<pair<int, char>, int> transitions;
  set<int> acceptingStates;
  int startState;
};

bool SimulateDFA(DFA &d, string input) {
  int currState = d.startState;
  for(string::iterator itr = input.begin(); itr != input.end(); ++itr) {
    currState = d.transitions[make_pair(currState, *itr)];
  }
  return d.acceptingStates.find(currState) != d.acceptingStates.end();
}