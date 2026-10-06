#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>

#include "file_handler.h"
#include "cli_basic.h"

void init(std::string path)
{
  std:: cout << "Windshield starting to init ... ";
  
  {
    std::ofstream config(path+"/windshield.txt");
    config << "include_path = 'include/'";
  }

  std::cout << "done" << std::endl;
}

int main(int argc, char* argv[])
{
  if (std::string_view(argv[1]) == "init")
  {
    init(std::filesystem::current_path().string());
  }
  else if (std::string_view(argv[1]) == "gen" || std::string_view(argv[1]) == "generate")
  {
    if (argc == 3)
    {
      // const std::string file(std::filesystem::absolute(argv[2]));
      // std::vector<FuncDec> funcs = function_declaration(file);
      // for (auto i : funcs)
      // {
      //   std::cout << "Declaration: " << i.declaration << "\nDestination: " << i.destination << std::endl;
      // }
      gen(argv[2]);
    }
    else if (argc < 3) std::cout << "Expected filename" << std::endl;
    else if (argc > 3) std::cout << "Expected 2 arguments, got " << argc-1 << std::endl;
  }
  else if (std::string_view(argv[1]) == "test") {
    // new_header("include/test.h", "", "TEST_H");
    // append_header("include/cli_basic.h", "void test(int test_num)");
  }
  else if (std::string_view(argv[1]) == "version" | std::string_view(argv[1]) == "-v" | std::string_view(argv[1]) == "--version") {
    version();
  }
  else {
    std::cout << "Args: " << argc << std::endl;
  }
  return 0;
}

