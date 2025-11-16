#include<istream>
#include <string>

enum class Token {
    END_OF_FILE,
    NUMBER,
    IDENTIFIER,
    IF,
    WHILE,
    ELSE,
    PRINT,
    ASSIGN,
    GREATER,
    LESS,
    GREATEREQUAL,
    LESSEQUAL,
    EQUAL,
    NOTEQUAL,
    NOT,
    AND,
    OR,
    OPAREN,
    CPAREN,
    ADD,
    SUBS,
    MULT,
    DIV,
    OBRACKET,
    CBRACKET,
    INT,
    POINTCOMMA,
    ERROR,
};

class Lexer{
    public:
     Lexer(std::istream& in_): in(in_){
        currentChar = in.get();
     }

     Token nextToken();

     std::string getText() const{
        return text;
     }

    static const char *TokenToString(Token token);
    private:
    std::istream& in;
    std::string text;
    int currentChar;
};