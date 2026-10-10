#pragma once

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <filesystem>
#include <string>
#include <vector>

struct FuncDec {
  std::string declaration;
  std::string destination;
};

std::vector<FuncDec> function_declaration(const std::string &);
void new_header(FuncDec &, std::string definition);
void append_header(FuncDec &);
std::vector<std::string> read_config();

#endif // FILE_HANDLER_H
