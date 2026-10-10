#include <cctype>
#include <cstddef>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../include/cli_basic.h"
#include "../include/file_handler.h"

using std::cout, std::endl, std::runtime_error;
using std::string, std::vector, std::size_t, std::filesystem::path;

string generate_definition(const string &name) {
  string result = name;

  for (char &c : result) {
    c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    if (c == '-')
      c = '_';
  }

  result += "_H";

  return result;
}

void gen(const string &file_name) {
  cout << "Starting to read recived file ... ";
  vector<FuncDec> functions = function_declaration(file_name);
  path path = file_name;
  string name = path.stem().string();
  bool absolute_path = true;
  bool add_include_path = true;

  vector<string> config = read_config();
  string include;
  for (size_t i = 0; i < config.size(); i++) {
    if (config[i].find("include_path = ") == 0) {
      string temp = "include_path = '";
      include = config[i].substr(temp.size());
      if (include.back() == '\'')
        include.pop_back();
    }

    if (config[i].find("ws_absolute_path") == 0) {
      string temp = "ws_absolute_path = ", x;
      x = config[i].substr(temp.size());

      if (x != "true" || x != "false") {
        runtime_error("\nError: Windshield config contains incorrect "
                      "config. The 'ws_absolute_path' variable should "
                      "have a bool type.");
      }
    }
  }

  cout << "done" << endl;

  cout << "Writing data ... ";
  for (std::size_t i = 0; i < functions.size(); i++) {
    if (add_include_path) {
      functions[i].destination.insert(0, include);
    }
    if (absolute_path) {
      if (std::filesystem::path(functions[i].destination).is_relative()) {
        functions[i].destination.insert(0, "/");
        functions[i].destination.insert(
            0, std::filesystem::current_path().string());
      }
    }
    if (std::filesystem::exists(functions[i].destination)) {
      append_header(functions[i]);
    } else {
      new_header(functions[i], generate_definition(name));
    }
  }
  cout << "done" << endl;
}

void version() {
  cout << "Windshield 1.0.0\nCreated by k44rme\nRespository: "
          "https://github.com/k44rme/windshield"
       << endl;
}
