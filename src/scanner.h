/*
 * First part of the Compiler's Frontend
 */

#ifndef SCHEME_2_HACK_SCANNER_H_
#define SCHEME_2_HACK_SCANNER_H_

#include <fstream>
#include <regex>
#include <string>
#include <vector>

/** Note: Case is insignificant in symbols so that, for example,
 *  newspaper, NewsPaper, and NEWSPAPER all represent the same identifier.
 */

// Identifiers matchers, may denote variable, identifier, symbol
const std::string IDENTIFIER_GROUP_INTIAL = "([\\!\\$%&\\*/\\:<>=~_])";

const std::string IDENTIFIER_GROUP_SUBSEQUENT = "([\\.\\+\\-])";

const std::string IDENTIFIER_LETTER = "([a-z])";

const std::string IDENTIFIER_DIGIT = "([0-9])";

const std::string IDENTIFIER_DOT = "(\\.[3])"; // FIXME test ...

//(\\\"[^\\\"]*\\\")|(\\w+)|([\\{\\}\(\\)\\[\\]\\.,;+\\-*/&\\|<>=~])
const std::string TOKENS_REGEX =
    "(\\w+)|([\\{\\}\(\\)\\[\\]\\.,;+\\-*/&\\|<>=~])"; //

// Definitions terminals
const std::string TR_BEGIN = "begin";
const std::string TR_LET_SYNTAX = "let-syntax";
const std::string TR_LET_REC_SYNTAX = "letrec-syntax";
const std::string TR_DEFINE = "define";
const std::string TR_DEFINE_SYNTAX = "define-syntax";

// Expressions terminals
const std::string TR_QUOTE = "quote";
const std::string TR_LAMBDA = "lambda";
const std::string TR_IF = "if";
const std::string TR_SET = "set!";

class Scanner {
private:
  std::ifstream sourceFile;
  std::vector<std::string>::iterator bufferIterator;
  std::vector<std::string> tokensBuffer;
  std::regex tokenRegex = std::regex(TOKENS_REGEX);

  bool tokenizeChunk(std::string line);

public:
  Scanner(std::string sourceFile);
  ~Scanner();
  bool hasNext();
  std::string nextToken();
};

#endif // SCHEME_2_HACK_SCANNER_H_