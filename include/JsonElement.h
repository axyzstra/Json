#ifndef _JSONELEMENT_
#define _JSONELEMENT_

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>


namespace axyz {
    namespace json {

        class JsonElement;
        using JsonObject = std::unordered_map<std::string, JsonElement*>;
        using JsonArray = std::vector<JsonElement*>;

        class JsonElement {
        public:
            enum Type {
                // 对象
                Json_Object,
                // 数组
                Json_Array,
                // 字符串
                Json_String,
                // 数字
                Json_Number,
                // 布尔
                Json_Bool,
                // 空
                Json_Null
            };

            union Value
            {
                // 对象
                JsonObject* value_object;
                // 数组
                JsonArray* value_array;
                // 字符串
                std::string* value_string;
                // 数字
                float value_number;
                // 布尔
                bool value_bool;
            };

            JsonElement() : type_(Type::Json_Null) {}
            ~JsonElement() {
                if (type_ == Type::Json_Object) {
                    delete value_.value_object;
                    value_.value_object = nullptr;
                }
                if (type_ == Type::Json_Array) {
                    delete value_.value_array;
                    value_.value_array = nullptr;
                }
                if (type_ == Type::Json_String) {
                    delete value_.value_string;
                    value_.value_string = nullptr;
                }
            }

            void value(JsonObject* object);
            void value(JsonArray* array);
            void value(std::string* str);
            void value(float number);
            void value(bool b);


            JsonObject* AsObject();
            JsonArray* AsArray();
            std::string* AsString();
            float AsNumber();
            bool AsBool();

            std::string Dumps();

            friend std::ostream& operator<<(std::ostream& os, const JsonObject& object);
            friend std::ostream& operator<<(std::ostream& os, const JsonArray& array);

        private:
            Type type_;
            Value value_;
        };
    };
};



#endif