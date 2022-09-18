#include <iostream>
#include <string>
#include <regex>
#include "Node.h"
#include<fstream>
using namespace std;

int main()
{
    fstream input("input.txt");
    if (input.is_open())
    {
        string input_string;
        getline(input, input_string);

        Node node(input_string, 1);

        cout << "Orinal text: " << input_string << "\n";

        string answer = node.ReturnAsString();
        cout << "Zip text: " << answer << "\n";

        ofstream output("output.txt");
        output << answer;

    }
    
}
