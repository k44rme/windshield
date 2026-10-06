#pragma once

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> read_config();

struct FuncDec {
  std::string declaration;
  std::string destination;
};

std::vector<FuncDec> function_declaration(const std::string &);

void new_header(FuncDec &, std::string);
void append_header(FuncDec &);

#endif // FILE_HANDLER_H
