#pragma once

// helpers
template<typename Out>
void split(const std::string &s, char delim, Out result);
std::vector<std::string> split(const std::string &s, char delim);
void scriptExecutor(string command, int col, int row, MineSweeper* m);
string infoMinefield(MineSweeper* m);

// main
void startGamefunction(int& order);
void firstScriptTransfer(int& col, int& row, string& command, MineSweeper* m);
void ingameTransfer(MineSweeper *m);