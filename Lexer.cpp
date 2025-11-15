#include "Lexer.hpp"

enum class State{
    Q0,
    END_OF_FILE_Q1,
    NUMBER_Q1,
    IDENTIFIER_Q1,
    IDENTIFIER_Q2,
    IDENTIFIER_Q3,
    SPACES_Q1,
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
            }else if(currentChar >= '0' && currentChar <= '9'){
                text+= static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::NUMBER_Q1;
            }else if((currentChar >= 'a' && currentChar <='z') || (currentChar >= 'A' && currentChar <= 'Z') || currentChar == '_'){
                text+= static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::IDENTIFIER_Q1;
            }else if(currentChar == ' ' || currentChar =='\t'){
                in.get();
                state = State::SPACES_Q1;
            }else{
                throw std::runtime_error(std::string("Invalid Character ")+ static_cast<char>(currentChar));
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
            }else{
                return Token::IDENTIFIER;
            }
            break;
            case State::SPACES_Q1:
                if(currentChar == ' ' || currentChar =='\t'){
                in.get();
                state = State::SPACES_Q1;
                }else{
                    state = State::Q0;
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
    default:
        return " ";
    }
}