#ifndef TOY_PARSER_H_
#define TOY_PARSER_H_

#include <memory>
#include <stack>

#include "ast.h"
#include "lexer.h"
#include "parser_gen.h"
#include "token.h"

namespace toy {

/**
 *  LL(1) parser.
 *
 * Uses the parsing table generated by the ParserGenerator,
 * the result of the parse is an AST which is built by executing
 * semantic actions encoded in the grammar.
 */
class Parser {
 public:
  Parser() = delete;
  Parser(Lexer& lexer, const ParserGenerator& pgen);
  std::shared_ptr<ASTNode> Parse();

 private:
  Lexer& lexer_;
  ParserGenerator pgen_;
  Token prev_token_;
  std::stack<Symbol> symbol_stack_;
  void InverseRhsMultiplePush(Symbol top, Symbol tk);
  void SkipErrors(Symbol& top, Token& tk);

  // Stack holding AST nodes while semantic acitons are executed
  // If parsing is successful, contains only one node (ProgNode) on top
  std::stack<std::shared_ptr<ASTNode>> semantic_stack_;
  void ExecuteSemanticAction(const std::string& action);
  void StartAction();
  void EndAction(std::string action);
  void PushAction(const std::string& action);
  void OpAction();
  void EndSignAction();
  void EndScopeResAction(std::string action);
};

}  // namespace toy

#endif  // TOY_PARSER_H_