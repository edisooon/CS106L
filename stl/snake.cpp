#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
using namespace std;

/* Number of food pellets that must be eaten to win. */
const int kMaxFood = 20;

/* Constants for the different tile types. */
const char kEmptyTile = ' ';
const char kWallTile = '#';
const char kFoodTile = '$';
const char kSnakeTile = '*';

const double kWaitTime = 0.1; // Pause 0.1 seconds between frames

const string kClearCommand = "clear";

const double kTurnRate = 0.2;

/* A struct encoding a point in a two-dimensional grid. */
struct pointT {
  int row, col;
};

/* A struct containing relevant game information. */
struct gameT {
  vector<string> world; // The playing field
  int numRows, numCols; // Size of the playing field

  deque<pointT> snake;  // The snake body
  int dx, dy;           // The snake direction

  int numEaten;         // How much food we've eaten.
};

string GetLine() {
  string result;
  getline(cin, result);
  return result;
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

pointT MakePoint(int row, int col) {
  pointT result;
  result.row = row;
  result.col = col;
  return result;
}

void LoadWorld(gameT& game, ifstream& input) {
  input >> game.numRows >> game.numCols;
  game.world.resize(game.numRows);

  input >> game.dx >> game.dy;

  string dummy;
  getline(input, dummy);

  for(int row = 0; row < game.numRows; ++row) {
    getline(input, game.world[row]);
    int col = game.world[row].find(kSnakeTile);
    if(col != string::npos)
      game.snake.push_back(MakePoint(row, col));
  }

  game.numEaten = 0;
}

void InitializeGame(gameT& game) {
  srand(static_cast<unsigned int>(time(NULL)));

  ifstream input;
  OpenUserFile(input);
  LoadWorld(game, input);
}

void PrintWorld(gameT& game) {
  system(kClearCommand.c_str());
  for(int row = 0; row < game.numRows; ++row)
    cout << game.world[row] << endl;
  cout << "Food eaten: " << game.numEaten << endl;
}

bool InWorld(pointT& pt, gameT& game) {
  return pt.col >= 0 &&
          pt.row >= 0 &&
          pt.col < game.numCols &&
          pt.row < game.numRows;
}

bool RandomChance(double probability) {
  return (rand() / (RAND_MAX + 1.0)) < probability;
}

bool Crashed(pointT headPos, gameT& game) {
  return !InWorld(headPos, game) ||
          game.world[headPos.row][headPos.col] == kSnakeTile ||
          game.world[headPos.row][headPos.col] == kWallTile;
}

pointT GetNextPosition(gameT& game, int dx, int dy) {
  pointT result = game.snake.front();
  result.row += dy;
  result.col += dx;
  return result;
}

void PerformAI(gameT& game) {
  pointT nextHead = GetNextPosition(game, game.dx, game.dy);
  if(Crashed(nextHead, game) || RandomChance(kTurnRate)) {
    int leftDx = -game.dy;
    int leftDy = game.dx;

    int rightDx = game.dy;
    int rightDy = -game.dx;

    bool canLeft = !Crashed(GetNextPosition(game, leftDx, leftDy), game);
    bool canRight = !Crashed(GetNextPosition(game, rightDx, rightDy), game);

    bool willTurnLeft = false;
    if(!canLeft && !canRight)
      return;
    else if(canLeft && !canRight)
      willTurnLeft = true;
    else if(!canLeft && canRight)
      willTurnLeft = false;
    else
      willTurnLeft = RandomChance(0.5);

    game.dx = willTurnLeft ? leftDx : rightDx;
    game.dy = willTurnLeft ? leftDy : rightDy;
  }
}

void PlaceFood(gameT& game) {
  while(true) {
    int row = rand() % game.numRows;
    int col = rand() % game.numCols;

    if(game.world[row][col] == kEmptyTile) {
      game.world[row][col] = kFoodTile;
      return;
    }
  }
}

bool MoveSnake(gameT& game) {
  pointT nextHead = GetNextPosition(game, game.dx, game.dy);
  if(Crashed(nextHead, game)) return false;

  bool isFood = (game.world[nextHead.row][nextHead.col] == kFoodTile);

  game.world[nextHead.row][nextHead.col] = kSnakeTile;
  game.snake.push_front(nextHead);

  if(!isFood) {
    game.world[game.snake.back().row][game.snake.back().col] = kEmptyTile;
    game.snake.pop_back();
  }else{
    ++game.numEaten;
    PlaceFood(game);
  }
  return true;
}

void Pause() {
  clock_t startTime = clock();
  while(static_cast<double>(clock()-startTime) / CLOCKS_PER_SEC < kWaitTime);
}

void DisplayResult(gameT& game) {
  PrintWorld(game);
  if(game.numEaten == kMaxFood)
    cout << "The snake ate enough food and wins!" << endl;
  else
    cout << "Oh no! The snake crashed" << endl;
}


void RunSimulation(gameT& game) {
  /* Keep looping while we haven't eaten too much. */
  while(game.numEaten < kMaxFood) {
    PrintWorld(game); // Display the board
    PerformAI(game);  // Have the AI choose an action

    if(!MoveSnake(game))  // Move the snake and stop if we crashed
      break;
    Pause();            // Pause so we can see what's going on
  }
  DisplayResult(game);  //Tell the user what happened
}

/* The main program. Initializes the world, then runs the simulation. */
int main() {
  gameT game;
  InitializeGame(game);
  RunSimulation(game);
  return 0;
}
