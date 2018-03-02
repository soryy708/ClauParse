/* `parser.cpp`
* By: Ivan Rubinson (c) 2016
* Licensed under the Lesser GNU Public License v3.
*/
#include "clauparse.h"
#include "Clauparse/tokenizer.h"
#include <fstream>
#include <string>

namespace ClauParse
{
	/* `makeNode`
	 * tokens[i].type must be Tokens::LABEL
	 * 
	 * TODO:
	 * Make more checks to improve `ParsingException` messages.
	 */
	Data::Node makeNode(std::vector<Token> tokens, unsigned int i, Data::Node* parent)
	{
		Data::Node node;

		if (i < tokens.size() && tokens.size() != 0)
		{
			node.parent = parent;

			if (tokens[i].type == Token::LABEL)
			{
				node.name = tokens[i].value;
			}
			else
			{
				throw(ParsingException("Expected LABEL"));
			}

			if (i + 2 < tokens.size()) // enough space for an EQUALS + LABEL/BLOCK
			{
				if (tokens[i + 1].type == Token::EQUALS)
				{
					unsigned int blocks;

					switch (tokens[i + 2].type) // What should `node` equal to?
					{
					case(Token::LABEL) :
						node.children.push_back(Data::Node(&node, tokens[i + 2].value));
						break;

					case(Token::BLOCK_OPEN) :
						blocks = 1;
						for (unsigned int j = i + 3; j < tokens.size() && blocks > 0; ++j)
						// j is set to right after BLOCK_OPEN,
						// runs until matching BLOCK_CLOSE, or there are no more tokens.
						{
							if (blocks == 1 && tokens[j].type == Token::LABEL && tokens[j-1].type != Token::EQUALS)
							// If tokens[j] is `node`s child, and isn't after an EQUALS.
							{
								node.children.push_back(makeNode(tokens, j, &node));
							}
							else
							// If tokens[j] isn't `node`'s child.
							{
								if (tokens[j].type == Token::BLOCK_OPEN)
								{
									++blocks;
								}
								else if (tokens[j].type == Token::BLOCK_CLOSE)
								{
									--blocks;
								}
							}
						}
						if (blocks > 0)
						{
							throw(ParsingException("A block was opened but not closed"));
						}
						break;

					default:
						throw(ParsingException("LABEL EQUALS something unexpected"));
						break;
					}
				}
				else
				{
					node.children.push_back(Data::Node(&node, ""));
				}
			}
		}
		return node;
	}
	Data::Node makeNode(std::vector<Token> tokens)
	{
		return makeNode(tokens, 0, nullptr);
	}

	Data parseFile(const char* path)
	{
		std::ifstream fin(path);
		if (fin.is_open() && fin.good()) // TODO: More checks on fin?
		{
			std::vector<Token> tokens;
			tokens.reserve(1024);

			// Read file line by line, tokenize each line, and concate all in `tokens`.
			std::string str;
			while (std::getline(fin, str))
			{
				auto line_tokens = tokenizeLine(str);
				tokens.insert(std::end(tokens), std::begin(line_tokens), std::end(line_tokens));
			}

			return Data(makeNode(tokens));
		}
		else
		{
			throw(std::runtime_error(std::string("Can't read from file: ") + path));
		}

		return Data();
	}
}
