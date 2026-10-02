#pragma once

#ifndef FILE_HANDLER_H
  #define FILE_HANDLER_H

  #include <vector>
  #include <string>
  #include <sstream>

  struct WindShield {
    std::string root_path;
    std::string include_path;
  };

  struct FuncDec {
    std::string declaration;
    std::string destination;
  };

  std::vector<FuncDec> function_declaration(const std::string&);

  void new_header(std::string, std::string, std::string);
  void append_header(std::string, std::string);
#endif // FILE_HANDLER_H
