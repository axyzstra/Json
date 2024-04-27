#include "Scanner.h"
#include "Error.h"
#include <sstream>


namespace axyz {
    namespace json {
        Scanner::JsonToken Scanner::Scan() {
            pre_pos = cur_pos;
            // 获取一个字符
            char c = Advance();
            switch (c)
            {
            case '{': return Scanner::JsonToken::BEGIN_OBJECT;
            case '}': return Scanner::JsonToken::END_OBJECT;
            case ',': return Scanner::JsonToken::VALUE_SEPARATOR;
            case ':': return Scanner::JsonToken::NAME_SEPARATOR;
            case '\"': {
                value_string_ = ScanString();
                return VALUE_STRING;
            }
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': {
                value_number_ = ScanNumber();
                return VALUE_NUMBER;
            }
            case ' ':
            case '\r':
            case '\n':
            case '\t': return Scan();
            case 't': {
                ScanTrue();
                return LINERAL_TRUE;
            }
            case 'f': {
                ScanFalse();
                return LINERAL_FALSE;
            }
            case 'n': {
                ScanNull();
                return LINERAL_NULL;
            }
            case '[': return Scanner::JsonToken::BEGIN_ARRAY;
            case ']': return Scanner::JsonToken::END_ARRAY;
            
            default:
                return Scanner::JsonToken::ERROR;
            }

        }


        bool Scanner::isEnd() {
            if (cur_pos >= source_string_.size()) {
                return true;
            }
            return false;
        }

        bool Scanner::isDight(char c) {
            if (c >= '0' && c <= '9') {
                return true;
            } else {
                return false;
            }
        }

        char Scanner::Advance() {
            if (isEnd()) {
                Error("here is end");
            }
            return source_string_[cur_pos++];
        }

        void Scanner::Rollback() {
            cur_pos = pre_pos;
        }

        char Scanner::Peek() {
            return source_string_[cur_pos];
        }


        std::string Scanner::ScanString() {
            size_t pos = cur_pos;
            while (!isEnd() && Peek() != '\"') {
                Advance();
            }
            if (isEnd()) {
                Error("Invaid string!");
            }
            Advance();
            return source_string_.substr(pos, (cur_pos - pos - 1));
        }

        float Scanner::ScanNumber() {
            Rollback();
            size_t pos = cur_pos;
            while (!isEnd() && isDight(Peek())) {
                Advance();
            }

            // 若遇小数
            if (Peek() == '.') {
                Advance();
                while (!isEnd() && isDight(Peek())) {
                    Advance();
                }
            }

            if (isEnd()) {
                Error("Invaid string!");
            }
            std::string str = source_string_.substr(pos, cur_pos - pos);
            return atof(str.c_str());
        }

        void Scanner::ScanTrue() {
            if (!source_string_.compare(cur_pos, 3, "rue")) {
                cur_pos += 3;
            } else {
                Error("Scan true error");
            }
        }

        void Scanner::ScanFalse() {
            if (!source_string_.compare(cur_pos, 4, "alse")) {
                cur_pos += 4;
            } else {
                Error("Scan false error");
            }
        }

        void Scanner::ScanNull() {
            if (!source_string_.compare(cur_pos, 3, "ull")) {
                cur_pos += 3;
            } else {
                Error("Scan Null error");
            }
        }

        float Scanner::GetNumber() {
            return value_number_;
        }

        std::string Scanner::GetString() {
            return value_string_;
        }

    };
};
