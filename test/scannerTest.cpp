#include "../src/scanner.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <regex>
#include <vector>

TEST(ScannerTest, matchesInitialIdentifier) {

  const std::vector<std::string> INITIALS = {"!", "$", "%", "&", "/", "*", ":",
                                             "<", "=", ">", "?", "~", "_", "^"};
  const std::regex regExpression(IDENTIFIER);

  const std::string identifier = "sum-of-squares";

  std::smatch sm;

  std::string line;

  for (auto it = INITIALS.begin(); it != INITIALS.end(); ++it) {
    auto initial = *it;
    line = "(+(- 10 7))( " + initial + identifier + " 2 param ))";
    std::regex_search(line.cbegin(), line.cend(), sm, regExpression);

    EXPECT_EQ(initial + identifier, sm[0].str());
  }

  for (auto it = INITIALS.begin(); it != INITIALS.end(); ++it) {
    auto initial = *it;
    line = "(+(- 10 7))( " + initial + initial + identifier + " 2 param ))";
    std::regex_search(line.cbegin(), line.cend(), sm, regExpression);

    EXPECT_EQ(initial + initial + identifier, sm[0].str());
  }

  for (auto it = INITIALS.begin(); it != INITIALS.end(); ++it) {
    auto initial = *it;
    line = "(+(- 10 7))( " + initial + identifier + initial + " 2 param ))";
    std::regex_search(line.cbegin(), line.cend(), sm, regExpression);

    EXPECT_EQ(initial + identifier + initial, sm[0].str());
  }
}

TEST(ScannerTest, matchesSubsequentIdentifier) {

  const std::vector<std::string> SUBSEQUENTS = {".", "+", "-", "6", "42"};
  const std::regex regExpression(IDENTIFIER);
  const std::string identifier = "sum-of-squares";

  std::smatch sm;

  std::string line;

  for (auto it = SUBSEQUENTS.begin(); it != SUBSEQUENTS.end(); ++it) {
    auto initial = *it;
    line = "(+(- 10 7))( " + identifier + initial + identifier + " 2 param ))";
    std::regex_search(line.cbegin(), line.cend(), sm, regExpression);

    EXPECT_EQ(identifier + initial + identifier, sm[0].str());
  }
}

TEST(ScannerTest, matchesDotstIdentifier) {
  const std::vector<std::string> INITIALS = {"!", "$", "%", "&", "/", "*", ":",
                                             "<", "=", ">", "?", "~", "_", "^"};
  const std::string dots = "...";
  const std::regex regExpression(IDENTIFIER);

  const std::string identifier = "sum-of-squares";

  std::smatch sm;

  std::string line;

  for (auto it = INITIALS.begin(); it != INITIALS.end(); ++it) {
    auto initial = *it;
    line = "(+(- 10 7))( " + initial + dots + " 2 param ))";
    std::regex_search(line.cbegin(), line.cend(), sm, regExpression);

    EXPECT_EQ(initial + dots, sm[0].str());
  }

  for (auto it = INITIALS.begin(); it != INITIALS.end(); ++it) {
    auto initial = *it;
    line = "(+(- 10 7))( " + initial + identifier + dots + " 2 param ))";
    std::regex_search(line.cbegin(), line.cend(), sm, regExpression);

    EXPECT_EQ(initial + identifier + dots, sm[0].str());
  }
}

TEST(ScannerTest, matchKeyWord) {

  const std::regex regExpression(IDENTIFIER);

  std::smatch sm;
  std::string line;

  for (auto it = KEYWORDS_SORTED.begin(); it != KEYWORDS_SORTED.end(); ++it) {
    auto keyword = *it;

    line = "(+(- 10 7))( " + keyword + " 2 param ))";
    std::regex_search(line.cbegin(), line.cend(), sm, regExpression);

    EXPECT_EQ(keyword, sm[0].str());
  }
}

TEST(ScannerTest, matchBrackets) {

  const std::string programm = "(define (square x) (* x x))";
  const std::regex regExpression(TOKENS_REGEX);

  std::smatch sm;

  std::regex_search(programm.cbegin(), programm.cend(), sm, regExpression);

  EXPECT_EQ("(", sm[0].str());
}

TEST(ScannerTest, matchProgramm) {

  const std::string programm = "(define (square x) (* x x))";

  const std::vector<std::string> tokens = {
      "(", "define", "(", "square", "x", ")", "(", "*", "x", "x", ")", ")"};

  const std::regex regExpression(TOKENS_REGEX);
  std::smatch sm;

  auto line_begin =
      std::sregex_iterator(programm.begin(), programm.end(), regExpression);
  auto line_end = std::sregex_iterator();

  std::sregex_iterator regexIterator = line_begin;

  int iter = 0;
  while (regexIterator != line_end) {
    std::smatch match = *regexIterator;

    std::string token = match.str();
    EXPECT_EQ(tokens[iter++], token);

    regexIterator++;
  }
}

TEST(ScannerTest, matchComplexProgramm) {

  const std::string programm =
      "(define (sum/display lst) (do ((remaining lst (cdr remaining)) "
      "(final-sum 0 (+ final-sum (car remaining)))) ((null? remaining) "
      "final-sum) (display (car remaining)) (newline))) ";

  const std::vector<std::string> tokens = {
      "(",     "define",    "(",         "sum/display",
      "lst",   ")",         "(",         "do",
      "(",     "(",         "remaining", "lst",
      "(",     "cdr",       "remaining", ")",
      ")",     "(",         "final-sum", "0",
      "(",     "+",         "final-sum", "(",
      "car",   "remaining", ")",         ")",
      ")",     ")",         "(",         "(",
      "null?", "remaining", ")",         "final-sum",
      ")",     "(",         "display",   "(",
      "car",   "remaining", ")",         ")",
      "(",     "newline",   ")",         ")",
      ")"};

  const std::regex regExpression(TOKENS_REGEX);
  std::smatch sm;

  auto line_begin =
      std::sregex_iterator(programm.begin(), programm.end(), regExpression);
  auto line_end = std::sregex_iterator();

  std::sregex_iterator regexIterator = line_begin;

  int iter = 0;
  while (regexIterator != line_end) {
    std::smatch match = *regexIterator;

    std::string token = match.str();
    EXPECT_EQ(tokens[iter++], token);

    regexIterator++;
  }
}
