#include "Parser.h"
#include "Error.h"


namespace axyz
{
    namespace json
    {
        JsonElement* Parser::Parse() {
            // 从扫描器中得到第一个 token
            Scanner::JsonToken token = scanner_.Scan();
            switch (token)
            {
            case Scanner::JsonToken::BEGIN_OBJECT: {
                JsonElement* element = new JsonElement();
                JsonObject* object = ParserObject();
                element->value(object);
                return element;
            }
            case Scanner::JsonToken::BEGIN_ARRAY: {
                JsonElement* element = new JsonElement();
                JsonArray* array = ParserArray();
                element->value(array);
                return element;
            }
            case Scanner::JsonToken::VALUE_STRING: {
                JsonElement* element = new JsonElement();
                element->value(new std::string(scanner_.GetString()));
                return element;
            }
            case Scanner::JsonToken::VALUE_NUMBER: {
                JsonElement* element = new JsonElement();
                element->value(scanner_.GetNumber());
                return element;
            }
            case Scanner::JsonToken::LINERAL_TRUE: {
                JsonElement* element = new JsonElement();
                element->value(true);
                return element;
            }
            case Scanner::JsonToken::LINERAL_FALSE: {
                JsonElement* element = new JsonElement();
                element->value(false);
                return element;
            }
            
            default:
                Error("Invalid! No Element!!!");
            }
            return nullptr;
        }


        /**
         * { "": } 
         */
        JsonObject* Parser::ParserObject() {
            JsonObject* object = new JsonObject();
            Scanner::JsonToken token = scanner_.Scan();
            if (token == Scanner::JsonToken::END_OBJECT) {
                return object;
            }
            scanner_.Rollback();

            while (true) {
                token = scanner_.Scan();
                if (token != Scanner::JsonToken::VALUE_STRING) {
                    Error("key must be string");
                }
                std::string key = scanner_.GetString();
                token = scanner_.Scan();
                if (token != Scanner::JsonToken::NAME_SEPARATOR) {
                    Error("Expected ':' in object");
                }
                (*object)[key] = Parse();
                token = scanner_.Scan();
                if (token == Scanner::JsonToken::END_OBJECT) {
                    break;
                }
                if (token != Scanner::JsonToken::VALUE_SEPARATOR) {
                    Error("Expected ',' in object!");
                }
            }
            return object;
        }


        JsonArray* Parser::ParserArray() {
            JsonArray* array = new JsonArray();
            Scanner::JsonToken token = scanner_.Scan();
            if (token == Scanner::JsonToken::END_ARRAY) {
                return array;
            }
            scanner_.Rollback();
            while (true) {
                array->push_back(Parse());
                token = scanner_.Scan();
                if (token == Scanner::END_ARRAY) {
                    break;
                }
                if (token != Scanner::VALUE_SEPARATOR) {
                    Error("Expected ',' in array");
                }
            }
            return array;
        }
    } // namespace json
    
} // namespace axyz


