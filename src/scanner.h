/*
 * First part of the Compiler's Frontend
 */

#ifndef SCHEME_2_HACK_SCANNER_H_
#define SCHEME_2_HACK_SCANNER_H_


#include <vector>
#include <string>
#include <fstream>
#include <regex>

//(\\\"[^\\\"]*\\\")|(\\w+)|([\\{\\}\(\\)\\[\\]\\.,;+\\-*/&\\|<>=~])
const std::string TOKENS_REGEX = "(\\w+)|([\\{\\}\(\\)\\[\\]\\.,;+\\-*/&\\|<>=~])"; //

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