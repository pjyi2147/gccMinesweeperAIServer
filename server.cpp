#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

#include "json.hpp"
#include "minesweeper.h"

using boost::asio::ip::tcp;
using namespace std;
using json = nlohmann::json;

/// helpers
// code from the link
// string split
template<typename Out>
void split(const std::string &s, char delim, Out result) {
  std::stringstream ss;
  ss.str(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    *(result++) = item;
  }
}

std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, std::back_inserter(elems));
  return elems;
}

void scriptExecutor(string line, MineSweeper* m)
{
  vector<string> tokens;
  tokens = split(line, ' ');
  
  string command = tokens[0];
  int col = stoi(tokens[1]);
  int row = stoi(tokens[2]);
  
  if (command == "E")
  {
    m->revealTile(col, row);
  }
  if (command == "F")
  {
    m->setFlag(col, row);
  }
  if (command == "D")
  {
    m->revealDoubleClick(col, row);
  }
}

string infoMinefield(MineSweeper* m)
{
  json infoMinefieldJson;
  infoMinefieldJson["win"] = m->returnWin();
  infoMinefieldJson["GameEnd"] = m->returnGameEnd();
  infoMinefieldJson["mineField"] = m->returnMineState();

  return infoMinefieldJson.dump();
}

/// main
void startGamefunction(int& order)
{
  cout << "Server boot up on port 1234" << endl;
  try
  {
    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1234));

    tcp::socket socket(io_service);
    acceptor.accept(socket);

    cout << "Client connected" << endl;

    // read
    boost::array<char, 10> buf;
    boost::system::error_code error;
    size_t len = socket.read_some(boost::asio::buffer(buf), error);
    auto order_str = string(buf.begin(), buf.begin() + len);

    order = stoi(order_str);

    cout << "Message read:" << order << endl;
    
    // write
    cout << "writing messages..." << endl;
    json message_json;
    switch (order)
    {
    case 1:
      message_json["col"] = 9;
      message_json["row"] = 9;
      message_json["mineNum"] = 10;
      break;
    case 2:
      message_json["col"] = 16;
      message_json["row"] = 16;
      message_json["mineNum"] = 40;
      break;
    case 3:
      message_json["col"] = 30;
      message_json["row"] = 16;
      message_json["mineNum"] = 99;
      break;
    }
    auto message = message_json.dump();
    boost::system::error_code ignored_error;
    boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

void firstScriptTransfer(int& col, int& row, string& command, MineSweeper* m)
{
  cout << "Server boot up on port 1234" << endl;
  try
  {
    // boot up
    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1234));

    tcp::socket socket(io_service);
    acceptor.accept(socket);

    cout << "Client connected" << endl;

    // read
    boost::array<char, 512> buf;
    boost::system::error_code error;
    size_t len = socket.read_some(boost::asio::buffer(buf), error);
    auto order_str = string(buf.begin(), buf.begin() + len);
    auto json_rec = json::parse(order_str);
    
    col = json_rec["col"];
    row = json_rec["row"];
    command = json_rec["command"];

    // execute
    m->createMinefield(col, row);

    // write
    cout << "writing messages..." << endl;
    
    auto message = infoMinefield(m);
    boost::system::error_code ignored_error;
    boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

void ingameTransfer(MineSweeper *m)
{
  cout << "Server boot up on port 1234" << endl;
  try
  {
    // boot up
    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1234));

    tcp::socket socket(io_service);
    acceptor.accept(socket);

    cout << "Client connected" << endl;

    // read
    boost::array<char, 512> buf;
    boost::system::error_code error;
    size_t len = socket.read_some(boost::asio::buffer(buf), error);
    auto order_str = string(buf.begin(), buf.begin() + len);
    cout << "Message received: " << order_str << endl;
    
    auto orders = json::parse(order_str);

    vector<string> commands = orders["orders"];

    for (auto& command : commands)
    {
      scriptExecutor(command, m);
    }

    // write
    cout << "writing messages..." << endl;

    auto message = infoMinefield(m);
    boost::system::error_code ignored_error;
    boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}
