#ifndef _SCANNER_
#define _SCANNER_

#include <string>


namespace axyz {
    namespace json {
        class Scanner {
        public:
            enum JsonToken {
                BEGIN_OBJECT,       // {
                END_OBJECT,         // }

                VALUE_SEPARATOR,    // ,
                NAME_SEPARATOR,     // :

                VALUE_STRING,       // string
                VALUE_NUMBER,       // number

                LINERAL_TRUE,       // true
                LINERAL_FALSE,      // false
                LINERAL_NULL,       // null

                BEGIN_ARRAY,        // [
                END_ARRAY,          // ]

                END_OF_SOURCE,      

                ERROR
            };

            Scanner(std::string source) : source_string_(source) {}

            JsonToken Scan();

            char Advance();
            void Rollback();
            char Peek();
            bool isEnd();
            bool isDight(char c);

            std::string ScanString();
            float ScanNumber();

            void ScanTrue();
            void ScanFalse();
            void ScanNull();

            float GetNumber();
            std::string GetString();


        private:
            std::string source_string_;

            int pre_pos = 0;
            int cur_pos = 0;


            std::string value_string_;
            float value_number_;
        };
    };
};





#endif