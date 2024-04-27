#include <iostream>
#include <sstream>
#include "Parser.h"
#include "Scanner.h"
#include "JsonElement.h"

int main() {
    std::string jsonStr = R"({
        "name":"John", 
        "age":30, 
        "isStudent":true, 
        "scores":[90, 95, 88], 
        "address":{
             "city":"New York", 
             "country":"USA"
         }
    })";


    axyz::json::Scanner scanner(jsonStr);
    axyz::json::Parser parser(scanner);
    axyz::json::JsonElement* root = parser.Parse();
    
    if (root != nullptr) {
        std::cout << "Parsed JSON Element:\n";
        std::cout << *(root->AsObject()) << std::endl;
        delete root;
    }
    else {
        std::cerr << "Failed to parse JSON string!" << std::endl;
    }

    return 0;
}