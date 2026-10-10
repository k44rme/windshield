#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../include/file_handler.h"

using std::cout, std::endl, std::runtime_error, std::string, std::vector;

vector<FuncDec> function_declaration(const string &file_name) {
  const string file(std::filesystem::absolute(file_name));
  vector<FuncDec> functions = {};
  {
    std::ifstream f;
    f.open(file);

    if (!f) {
      runtime_error("\nError: Failed to open requested file\nFile: " +
                    file_name);
    }

    string s;
    while (std::getline(f, s)) {
      string dest;
      if (s.find("// #ws ") == 0) {
        string temp = "// #ws ";
        dest = s.substr(temp.size());

        FuncDec current;
        current.destination = dest;

        string next;
        if (std::getline(f, next)) {
          if (next.back() == '{') {
            next.back() = ';';
          } else if (next.back() == ')') {
            next.push_back(';');
          }
          current.declaration = next;
        } else {
          throw runtime_error(
              "\nError: Failed to find the function declarations in " +
              file_name);
        }

        functions.push_back(current);
        continue;
      }
    }
    return functions;
  }
}

void new_header(FuncDec &obj, string definition) {

  if (definition.empty()) {
    runtime_error("\nError: Failed to generate definiton");
  }

  //  cout << "\n[Debug] Recived data:\n\tDefinition: " << definition
  //  << "\n\tDestination: " << obj.destination
  //  << "\n\tDeclaration: " << obj.declaration << endl;

  {
    std::ofstream header(obj.destination);

    if (!header) {
      runtime_error(
          "\nError: Requested destination is invalid.\nDestination: " +
          obj.destination);
    } else if (!header.is_open()) {
      runtime_error("\nError: Failed to open file: " + obj.destination);
    } else {
      cout << "\n[Debug] Writing content to the new header ... " << endl;
      header << "#pragma once\n\n"
             << "#ifndef " << definition << "\n"
             << "#define " << definition << "\n\n"
             << "// #ws declarations start\n\n"
             << obj.declaration;

      //      if (!obj.declaration.empty() && obj.declaration.back() != '\n')
      //        header << '\n';

      header << "\n\n// #ws declarations end\n\n"
             << "#endif // " << definition << "\n";
      header.close();
    }
  }
}

void append_header(FuncDec &obj) {
  vector<string> lines;

  //  vector<string> config = read_config();
  //  string include;
  //  for (size_t i = 0; i < config.size(); i++) {
  //    if (config[i].find("include_path")) {
  //      string temp = "include_path = ";
  //      include = config[i].substr(temp.size());
  //    }
  //  }

  {
    std::ifstream file(obj.destination);
    if (!file) {
      runtime_error("\nError: Failed to find a header");
    } else if (!file.is_open()) {
      runtime_error("\nError: Failed to open file: " + obj.destination);
    } else {
      string line;

      while (std::getline(file, line)) {
        lines.push_back(line);
      }
    }

    file.close();
  }

  size_t start_span = 0, end_span = 0;

  for (size_t i; i < lines.size(); i++) {
    //   start_span = lines.at(i).find("// #ws declarations start");
    //   end_span = lines.at(i).find("// #ws declarations end");
    if (lines[i] == "// #ws declarations start") {
      start_span = i;
    } else if (lines[i] == "// #ws declarations end") {
      end_span = i;
    } else {
      runtime_error("\nError: Declaration markers are not found!");
    }
  }

  if (start_span == 0 || end_span == 0) {
    cout << "failed" << endl;
    runtime_error(
        "\nError: Failed to find 'declaration section', which should "
        "contains '// #ws declarations start' and '// #ws declarations end' "
        "strings!");
  }
  lines.insert(lines.begin() + end_span, obj.declaration);

  {
    std::ofstream out(obj.destination, std::ios::trunc);
    if (out.is_open()) {
      for (auto current : lines) {
        out << current << "\n";
      }
    }

    out.close();
  }
}

vector<string> read_config() {
  vector<string> strings = {};
  {
    string path = std::filesystem::absolute("windshield.txt");
    std::ifstream config(path);

    if (!config) {
      cout << "failed" << endl;
      runtime_error("\nError: Failed to find Windshield config!\nType "
                    "'windshield init' command to init windshield.");
    }

    string s;
    while (std::getline(config, s)) {
      if (!s.empty()) {
        strings.push_back(s);
      }
    }
    config.close();
  }
  return strings;
}
