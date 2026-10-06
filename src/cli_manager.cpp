#include <cctype>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "../include/cli_basic.h"
#include "../include/file_handler.h"

std::string generate_definition(const std::string &name) {
  std::string result = name;

  for (char &c : result) {
    c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    if (c == '-')
      c = '_';
  }

  result += "_H";

  return result;
}

void gen(const std::string &file_name) {
  std::cout << "Starting to read recived file ... ";
  std::vector<FuncDec> functions = function_declaration(file_name);
  std::filesystem::path path = file_name;
  std::string name = path.stem().string();

  std::vector<std::string> config = read_config();
  std::string include;
  for (size_t i = 0; i < config.size(); i++) {
    if (config[i].find("include_path = ") == 0) {
      std::string temp = "include_path = '";
      include = config[i].substr(temp.size());
      if (include.back() == '\'')
        include.pop_back();

      break;
    }
  }

  std::cout << "done" << std::endl;

  std::cout << "Writing data ... ";
  for (std::size_t i = 0; i < functions.size(); i++) {
    functions[i].destination.insert(0, include);
    if (std::filesystem::path(functions[i].destination).is_relative()) {
      functions[i].destination.insert(0, "/");
      functions[i].destination.insert(0,
                                      std::filesystem::current_path().string());
    }
    std::cout << "\n[Debug] Destination: " << functions[i].destination
              << std::endl;
    if (std::filesystem::exists(functions[i].destination)) {
      append_header(functions[i]);
    } else {
      new_header(functions[i], generate_definition(name));
    }
  }
  std::cout << "done" << std::endl;
}

void version() {
  std::cout << "Windshield 1.0.0\nCreated by k44rme\nRespository: "
               "https://github.com/k44rme/windshield"
            << std::endl;
}
