/* `tokenizer.cpp`
* By: Ivan Rubinson (c) 2016
* Licensed under the Lesser GNU Public License v3.
*/
#include <regex>
#include <algorithm>
#include "Clauparse/tokenizer.h"

namespace ClauParse
{
	/* `tokenizeLine(std::string)`
	 * Creates a container of `Token`s from a single line.
	 * Everything after a `'#'` is ignored (`#` = comment).
	 * Empty lines don't create tokens.
	 * '{' creates a token of type `BLOCK_OPEN`.
	 * '}' creates a token of type `BLOCK_CLOSE`.
	 * '=' creates a token of type `EQUALS`.
	 * Everything else creates a token of type `LABEL`.
	 * Tokens must not have empty space(s).
	 */
	std::vector<Token> tokenizeLine(const std::string str)
	{
		std::vector<Token> tokens;

		const std::regex re{ "\\s*(?:\n|(#[^\n]*)|(\\{)|(\\})|(=)|([^{}= \t\r\n]+))" };

		std::for_each(std::sregex_iterator(str.cbegin(), str.cend(), re), std::sregex_iterator(), [&](const auto& i) {
			if (i[1].length() > 0U) {
				tokens.emplace_back(Token::TYPE_COUNT, i[1]);
			}
			else if (i[2].length() > 0U) {
				tokens.emplace_back(Token::BLOCK_OPEN, std::string("{"));
			}
			else if (i[3].length() > 0U) {
				tokens.emplace_back(Token::BLOCK_CLOSE, std::string("}"));
			}
			else if (i[4].length() > 0U) {
				tokens.emplace_back(Token::EQUALS, std::string("="));
			}
			else if (i[5].length() > 0U) {
				tokens.emplace_back(Token::LABEL, i[5]);
			}
		});

		for (std::vector<Token>::iterator it = tokens.begin(); it < tokens.end(); it++)
		{
			if ((*it).type == Token::TYPE_COUNT)
			{
				tokens.erase(it, tokens.end());
				break;
			}
		}

		return tokens;
	}
}
