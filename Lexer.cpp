#include "Lexer.hpp"
#include <iostream>

enum class State{
    Q0,
    END_OF_FILE_Q1,
    NUMBER_Q1,
    IDENTIFIER_Q1,
    IDENTIFIER_Q2,
    IDENTIFIER_Q3,
    SPACES_Q1,
    EQUALSING_Q1,
    GREATER_Q1,
    LESS_Q1,
    NOT_Q1,
    AND_Q1,
    OR_Q1
};

Token Lexer::nextToken(){
    State state = State::Q0;
    while(true){
        switch (state)
        {
        case State::Q0:
            text= "";
            if(currentChar == EOF){
                state = State::END_OF_FILE_Q1;
            }else if(currentChar == '\n'){
                lineNumber++;
                currentChar = in.get();
            }else if(currentChar == '\r'){
                currentChar = in.get();
                if(currentChar == '\n'){
                    lineNumber++;
                    currentChar = in.get();
                }
            }else if(currentChar >= '0' && currentChar <= '9'){
                text+= static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::NUMBER_Q1;
            }else if((currentChar >= 'a' && currentChar <='z') || (currentChar >= 'A' && currentChar <= 'Z') || currentChar == '_'){
                text+= static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::IDENTIFIER_Q1;
            }else if(currentChar == ' ' || currentChar =='\t'){
                currentChar = in.get();
                state = State::SPACES_Q1;
            }else if(currentChar == '+'){
                text+= static_cast<char>(currentChar);
                currentChar = in.get();
                return Token::ADD;
            }else if(currentChar == '-'){
                text+= static_cast<char>(currentChar);
                currentChar = in.get();
                if(std::isdigit(currentChar)){
                    state = State::NUMBER_Q1;
                }else{
                    return Token::SUBS;
                }
            }else if(currentChar == '/'){
                int next = in.peek();
                if(next == '/'){
                    int c = in.get();
                    while(c != EOF && c != '\n'){
                        c = in.get();
                    }
                    if(c == '\n'){
                        lineNumber++;
                        currentChar = in.get();
                    }else{
                        currentChar = EOF;
                    }
                    state = State::Q0;
                }else{
                    text+= static_cast<char>(currentChar);
                    currentChar = in.get();
                    return Token::DIV;
                }
            }else if(currentChar == '*'){
                text+= static_cast<char>(currentChar);
                currentChar = in.get();
                return Token::MULT;
            }else if(currentChar == ';'){
                text+= static_cast<char>(currentChar);
                currentChar = in.get();
                return Token::POINTCOMMA;
            }else if(currentChar == '{'){
                text+= static_cast<char>(currentChar);
                currentChar = in.get();
                return Token::OBRACKET;
            }else if(currentChar == '}'){
                text+= static_cast<char>(currentChar);
                currentChar = in.get();
                return Token::CBRACKET;
            }else if(currentChar == '('){
                text+= static_cast<char>(currentChar);
                currentChar = in.get();
                return Token::OPAREN;
            }else if(currentChar == ')'){
                text+= static_cast<char>(currentChar);
                currentChar = in.get();
                return Token::CPAREN;
            }else if(currentChar == '='){
                text+= static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::EQUALSING_Q1;
            }else if(currentChar == '<'){
                text+= static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::LESS_Q1;
            }else if(currentChar == '>'){
                text+= static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::GREATER_Q1;
            }else if(currentChar == '!'){
                text+= static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::NOT_Q1;  
            }else if(currentChar == '&'){
                text+= static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::AND_Q1;
            }else if(currentChar == '|'){
                text+= static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::OR_Q1;
            }else{
               
                char ch = static_cast<char>(currentChar);
                std::cerr << "Lexer error: Invalid character '" << ch << "' at line " << lineNumber << std::endl;
                text = std::string(1, ch);
                currentChar = in.get();
                return Token::ERROR;
            }
            break;
        case State::END_OF_FILE_Q1:
            return Token::END_OF_FILE;
        case State::NUMBER_Q1:
            if(currentChar >= '0' && currentChar <= '9'){
                    text+= static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::NUMBER_Q1;
                }else{
                    return Token::NUMBER;
                }
            break;
        case State::IDENTIFIER_Q1:
        if(currentChar >= '0' && currentChar <= '9'){
                    text+= static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::IDENTIFIER_Q2;
            }else if((currentChar >= 'a' && currentChar <='z') || (currentChar >= 'A' && currentChar <= 'Z') || currentChar == '_'){
                    text+= static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::IDENTIFIER_Q3;
            }else{
                return Token::IDENTIFIER;
            }
            break;
        case State::IDENTIFIER_Q2:
            if(currentChar >= '0' && currentChar <= '9'){
                    text+= static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::IDENTIFIER_Q2;
            }else if((currentChar >= 'a' && currentChar <='z') || (currentChar >= 'A' && currentChar <= 'Z') || currentChar == '_'){
                    text+= static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::IDENTIFIER_Q3;
            }else{
                return Token::IDENTIFIER;
            }
            break;
            case State::IDENTIFIER_Q3:
            if(currentChar >= '0' && currentChar <= '9'){
                    text+= static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::IDENTIFIER_Q2;
            }else if((currentChar >= 'a' && currentChar <='z') || (currentChar >= 'A' && currentChar <= 'Z') || currentChar == '_'){
                    text+= static_cast<char>(currentChar);
                    currentChar = in.get();
                    state = State::IDENTIFIER_Q3;
            }else if(text == "int"){
                return Token::INT;
            }else if(text == "while"){
                return Token::WHILE;
            }else if(text == "if"){
                return Token::IF;
            }else if(text == "else"){
                return Token::ELSE;
            }else if(text == "print"){
                return Token::PRINT;
            }else{
                return Token::IDENTIFIER;
            }
            break;
            case State::SPACES_Q1:
                if(currentChar == ' ' || currentChar =='\t'){
                currentChar = in.get();
                state = State::SPACES_Q1;
                }else{
                    state = State::Q0;
                }
            break;
            case State::EQUALSING_Q1:
                if(currentChar == '='){
                    text+= static_cast<char>(currentChar);
                    currentChar =  in.get();
                    return Token::EQUAL;
                }else{
                    return Token::ASSIGN;
                }
            break;
            case State::LESS_Q1:
                if(currentChar == '='){
                    text+= static_cast<char>(currentChar);
                    currentChar = in.get();
                    return Token::LESSEQUAL;
                }else{
                    return Token::LESS;
                }
            break;
            case State::GREATER_Q1:
                if(currentChar == '='){
                    text+= static_cast<char>(currentChar);
                    currentChar = in.get();
                    return Token::GREATEREQUAL;
                }else{
                    return Token::GREATER;
                }
            break;
            case State::NOT_Q1:
                if(currentChar == '='){
                    text+= static_cast<char>(currentChar);
                    currentChar =  in.get();
                    return Token::NOTEQUAL;
                }else{
                    return Token::NOT;
                }
            break;
            case State::AND_Q1:
                if(currentChar == '&'){
                    text+= static_cast<char>(currentChar);
                    currentChar = in.get();
                    return Token::AND;
                }else{
                    std::cerr << "Lexer error: Expected '&' after '&' at line " << lineNumber << std::endl;
                    text = "&";
                    return Token::ERROR;
                }
            break;
            case State::OR_Q1:
                if(currentChar == '|'){
                    text+= static_cast<char>(currentChar);
                    currentChar = in.get();
                    return Token::OR;
                }else{
                    std::cerr << "Lexer error: Expected '|' after '|' at line " << lineNumber << std::endl;
                    text = "|";
                    return Token::ERROR;
                }
            break;
        default:
            break;
        }
    }
}

const char *Lexer::TokenToString(Token token){
    switch (token)
    {
    case Token::END_OF_FILE:
        return "End of File";
    case Token::IDENTIFIER:
        return "Identifier";
    case Token::NUMBER:
        return "Number";
    case Token::IF:
        return "If";
    case Token::WHILE:
        return "While";
    case Token::ELSE:
        return "Else";
    case Token::PRINT:
        return "Print"; 
    case Token::ASSIGN:
        return "Assign";
    case Token::GREATER:
        return "Greater";  
    case Token::LESS:
        return "Less";  
    case Token::GREATEREQUAL:
         return "Greater Equal";
    case Token::LESSEQUAL:
        return "Less Equal";
    case Token::EQUAL:
        return "Equal";
    case Token::NOTEQUAL:
        return "Not Equal";
    case Token::NOT:
        return "Not";
    case Token::AND:
        return "And";
    case Token::OR:
        return "Or";
    case Token::OPAREN:
        return "Open Parenthesis";
    case Token::CPAREN:
        return "Close Parenthesis";
    case Token::ADD:
        return "Addition";
    case Token::SUBS:
        return "Subtraction";
    case Token::MULT:
        return "Multiplication";
    case Token::DIV:
        return "Division";
    case Token::OBRACKET:
        return "Open Bracket";
    case Token::CBRACKET:
        return "Close Bracket";
    case Token::INT:
        return "Int";
    case Token::POINTCOMMA:
        return "Point Comma";
    case Token::ERROR:
        return "Error";    
    default:
        return " ";
    }
}