#include <map>
#include <set>
#include <string>
using namespace std;

struct NFA {
  multimap<pair<int, char>, int> transitions;
  set<int> acceptingStates;
  int startState;
};

bool SimulateNFA(NFA& nfa, string input) {
  set<int> currStates;
  currStates.insert(nfa.startState);

  for(string::iterator itr = input.begin(); itr != input.end(); ++itr) {
    set<int> nextStates;
    for(set<int>:: iterator state = currStates.begin(); state != currStates.end(); ++state) {
      pair<multimap<pair<int, char>, int>::iterator, multimap<pair<int, char>, int>::iterator> transitions = nfa.transitions.equal_range(make_pair(*state, *itr));
      for(; transitions.first != transitions.second; ++transitions.first)
        nextStates.insert(transitions.first->second);
    }
    currStates = nextStates;
  }

  for(set<int>::iterator itr = currStates.begin(); itr != currStates.end(); ++itr)
    if(nfa.acceptingStates.count(*itr)) return true;
  return false;

}