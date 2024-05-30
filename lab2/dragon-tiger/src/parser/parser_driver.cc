#include "parser_driver.hh"
#include "../utils/errors.hh"
#include "tiger_parser.hh"
#include "../ast/evaluator.hh"

bool ParserDriver::parse(const std::string &f) {
  file = f;
    lex_begin();
    yy::tiger_parser parser(*this);
    parser.set_debug_level(trace_parser);
    int res = parser.parse();
    lex_end();

    if (res == 0 && eval_mode) {
        if (result_ast) {
            ast::eval::Evaluator evaluator;
            result_ast->accept(evaluator);
            std::cout << evaluator.result << std::endl;
        } else {
            utils::error(yy::location(), "Parsing succeeded, but no AST was produced.");
        }
    }

    return res == 0;
}
