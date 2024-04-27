#ifndef _PARSER_
#define _PARSER_

#include "Scanner.h"
#include "JsonElement.h"

namespace axyz
{
    namespace json
    {
        class Parser {
        public:
            Parser(Scanner scanner) : scanner_(scanner) {}

            JsonElement* Parse();
            JsonObject* ParserObject();
            JsonArray* ParserArray();
        private:
            Scanner scanner_;
        }; 
    }; // namespace json
    
}; // namespace axyz




#endif