/* `clauparse.h`
* By: Ivan Rubinson (c) 2016
* Licensed under the Lesser GNU Public License v3.
*/
#ifndef CLAUPARSE_CLAUPARSE_H_INCLUDED
#define CLAUPARSE_CLAUPARSE_H_INCLUDED

#include <vector>
#include <exception>
#include <string>

namespace ClauParse
{
	class Data
	{
	public:
		/* `Node`
		 * is a node in an n-element tree.
		 */
		struct Node
		{
			std::string name;
			std::vector<Node> children;
			Node* parent;

			Node(Node* parent, std::string name = "") :
				parent(parent),
				name(name)
			{
			}
			Node() :
				parent(nullptr)
			{
			}
		};

	private:
		Node data_start;

	public:
		Node* begin() { return &data_start; }

		Data()
		{
		}

		Data(Node node) :
			data_start(node)
		{
		}
	};

	/* `parseFile`
	 * Parses a file at given `path`, and returns `Data`.
	 * May throw `std::runtime_error` if it fails to read from the file.
	 * Possible causes:
	 * - File does not exist
	 * - File is locked by another process
	 * May also throw `ParsingException` if the file is malformed.
	 */
	Data parseFile(const char* path);

	/* `ParsingException`
	* Is thrown when a file is malformed.
	* Make sure that you're parsing the right file.
	* If it's the right file but it's still misformed,
	* it can be caused by a mistake in the file.
	* A file might have a mistake for many reasons, including:
	* - A mistake when editing by hand
	* - A system failure during a write operation
	*/
	class ParsingException : public std::exception
	{
	private:
		const char* error;

	public:
		const char* what() const throw() { return error; }

		ParsingException(const char* error) : error(error) {}
	};
}

#endif
