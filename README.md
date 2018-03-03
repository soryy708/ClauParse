# ClauParse
C++ library for parsing files from the Clausewitz Engine.

Licensed under the LGPLv3. See: `LICENSE`.

---

## Usage:

```
void print(ClauParse::Data::Node* origin, const unsigned int indent = 0);

int main()
{
    ClauParse::Data data;
    data = ClauParse::parseFile("example.gui");
    print(data.begin());
    return 0;
}

void print(ClauParse::Data::Node* origin, const unsigned int indent)
{
	if (origin == nullptr)
		return;
	
	for (unsigned int i = 0; i < indent; ++i)
		std::wcout << L"  ";
	std::wcout << origin->name << L" = ";
	
	if (origin->children.size() > 1)
	{
		std::wcout << L"{" << std::endl;
		for (auto i : origin->children)
		{
			print(&i, indent + 1);
		}
		for (unsigned int i = 0; i < indent; ++i)
			std::wcout << L"  ";
		std::wcout << L"}" << std::endl;
	}
	else
	{
		if (origin->children.size() == 1)
		{
			std::wcout << origin->children[0].name << std::endl;
		}
		else
		{
			std::wcout << L"NaN" << std::endl;
		}
	}
}
```  

---

## TODO:

- Add checks to improve messages given by `ParsingException`.
- Add checks to open files in a safer manner.
- Optimize. (Run profiler. Consider move semantics.)

---
