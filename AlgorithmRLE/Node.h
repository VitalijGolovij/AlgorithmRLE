#include <string>
#include <vector>

class Node
{
public:
	Node(std::string base, int num_repeats);
	std::string ReturnAsString();
private:
	int num_repeats_ = 1;
	std::string base_;
	std::vector<Node> child_;
};
