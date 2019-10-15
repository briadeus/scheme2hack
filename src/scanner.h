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

const std::string IDENTIFIER_LETTER = "([a-z])";

const std::string IDENTIFIER_GROUP_INTIAL =
    "(" + IDENTIFIER_LETTER + "|[\\!\\$%&\\*/\\:<>=~_\\?\\^])";

const std::string IDENTIFIER_GROUP_SUBSEQUENT = "([\\.\\+\\-])";

const std::string IDENTIFIER_DIGIT = "([0-9])";

const std::string IDENTIFIER =
    IDENTIFIER_GROUP_INTIAL + "{1}((" + IDENTIFIER_GROUP_INTIAL + "|" +
    IDENTIFIER_DIGIT + "|" + "\\.|\\+|-" + ")*|\\+|-|(\\.\\.\\.))";

const std::string NUMBERS = "(\\+|-)";

const std::string TOKENS_REGEX =
    IDENTIFIER + "|" + IDENTIFIER_DIGIT + "+" + "|\\(|\\)|" + NUMBERS;

//"(\\w+)|([\\{\\}\(\\)\\[\\]\\.,;+\\-*/&\\|<>=~])"; //

// Definitions terminals
const std::string TR_LET_SYNTAX = "let-syntax";
const std::string TR_LET_REC_SYNTAX = "letrec-syntax";
const std::string TR_DEFINE = "define";
const std::string TR_DEFINE_SYNTAX = "define-syntax";

// Expressions terminals
const std::string TR_QUOTE = "quote";
const std::string TR_LAMBDA = "lambda";
const std::string TR_IF = "if";
const std::string TR_SET = "set!";

// Derived-Expressions terminals
const std::string TR_BEGIN = "begin";
const std::string TR_AND = "and";
const std::string TR_OR = "or";
const std::string TR_CASE = "case";
const std::string TR_COND = "cond";
const std::string TR_DELAY = "delay";
const std::string TR_DO = "do";
const std::string TR_LET = "let";
const std::string TR_LET_STAR = "let*";
const std::string TR_LET_REC = "letrec";
const std::string TR_QUASIQUOTE = "quasiquote";

const std::vector<std::string> KEYWORDS_SORTED = {TR_AND,     TR_BEGIN,
                                                  TR_CASE,    TR_COND,
                                                  TR_DEFINE,  TR_DEFINE_SYNTAX,
                                                  TR_DELAY,   TR_DO,
                                                  TR_IF,      TR_LAMBDA,
                                                  TR_LET,     TR_LET_STAR,
                                                  TR_LET_REC, TR_LET_REC_SYNTAX,
                                                  TR_OR,      TR_QUASIQUOTE,
                                                  TR_QUOTE,   TR_SET};

enum class TokenType { keyword, identifier, numVal, stringVal };

class Scanner {
private:
  std::ifstream sourceFile;
  std::vector<std::string>::iterator bufferIterator;
  std::vector<std::string> tokensBuffer;
  std::regex tokenRegex = std::regex(TOKENS_REGEX);

public:
  Scanner(std::string sourceFile);
  ~Scanner();
  bool tokenizeChunk(std::string line);
  bool hasNext();
  std::string nextToken();
  TokenType getTokenType(std::string token);
};

#endif // SCHEME_2_HACK_SCANNER_H_