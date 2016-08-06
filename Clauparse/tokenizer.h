/* `tokenizer.h`
 * By: Ivan Rubinson (c) 2016
 * Licensed under the Lesser GNU Public License v3.
 */
#ifndef CLAUPARSE_TOKENIZER_H_INCLUDED
#define CLAUPARSE_TOKENIZER_H_INCLUDED

#include <vector>
#include <string>

namespace ClauParse
{
	struct Token
	{
		enum Type
		{
			LABEL,
			EQUALS,
			BLOCK_OPEN,
			BLOCK_CLOSE,
			TYPE_COUNT
		} type;
		std::string value;
		
		Token(const Type type, const std::string value) :
			type(type),
			value(value)
		{
		}
	};

	std::vector<Token> tokenizeLine(const std::string str);
}

#endif
