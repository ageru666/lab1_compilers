#include "parser_driver.hh"

int main(int argc, char *argv[]) {
  bool trace_lexer = false;
  bool trace_parser = false;
  bool eval_mode = false;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-e" || arg == "--eval") {
      eval_mode = true;
    } else if (arg == "--trace-lexer") {
      trace_lexer = true;
    } else if (arg == "--trace-parser") {
      trace_parser = true;
    } else {
      ParserDriver driver(trace_lexer, trace_parser);
      driver.eval_mode = eval_mode;
      if (!driver.parse(arg)) {
        return 1;
      }
    }
  }

  return 0;
}
