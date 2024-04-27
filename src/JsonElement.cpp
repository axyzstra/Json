#include "JsonElement.h"
#include "Error.h"
#include <sstream>

namespace axyz
{
    namespace json
    {
        
        void JsonElement::value(JsonObject* object) {
            type_ = Type::Json_Object;
            value_.value_object = object;
        }

        
        void JsonElement::value(JsonArray* array) {
            type_ = Type::Json_Array;
            value_.value_array = array;
        }

        
        void JsonElement::value(std::string* str) {
            type_ = Type::Json_String;
            value_.value_string = str;
        }


        
        void JsonElement::value(float number) {
            type_ = Type::Json_Number;
            value_.value_number = number;
        }


        
        void JsonElement::value(bool b) {
            type_ = Type::Json_Bool;
            value_.value_bool = b;
        }

        JsonObject* JsonElement::AsObject() {
            return value_.value_object;
        }

        
        JsonArray* JsonElement::AsArray() {
            return value_.value_array;
        }

        
        std::string* JsonElement::AsString() {
            return value_.value_string;
        }

        
        float JsonElement::AsNumber() {
            return value_.value_number;
        }

        
        bool JsonElement::AsBool() {
            return value_.value_bool;
        }


        

        std::string JsonElement::Dumps() {
            std::stringstream ss;
            switch (type_)
            {
            case Type::Json_Object: {
                ss << *(value_.value_object);
                break;
            }
            case Type::Json_Array: {
                ss << *(value_.value_array);
                break;
            }
            case Type::Json_String: {
                ss << '\"' << *(value_.value_string) << '\"';
                break;
            }
            case Type::Json_Number: {
                ss << std::to_string(value_.value_number);
                break;
            }
            case Type::Json_Bool: {
                ss << (value_.value_bool == true ? "true" : "false");
                break;
            }
            case Type::Json_Null:
                ss << "null";
            default:
                Error("Invaild!!!");
                break;
            }
            return ss.str();
        }

        std::ostream& operator<<(std::ostream& os, const JsonObject& object) {
            os << "{\n\t";
            size_t size = object.size();
            int index = 0;
            for (auto iter = object.begin(); iter != object.end(); iter++) {
                os << '\"' << iter->first << '\"' << " : " << iter->second->Dumps();
                if (index != (size - 1)) {
                    os << ", \n\t";
                }
                index++;
            }
            os << "\n}";

            return os;
        }

        std::ostream& operator<<(std::ostream& os, const JsonArray& array) {
            os << "[";
            size_t size = array.size();
            int index = 0;
            for (auto iter = array.begin(); iter != array.end(); iter++) {
                os << (*iter)->Dumps();
                if (index != (size - 1)) {
                    os << ", ";
                }
                index++;
            }
            os << "]";
            return os;
        }

        
    } // namespace json
    
} // namespace axyz
