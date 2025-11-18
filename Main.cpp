#include<iostream>
#include<fstream>
#include "Lexer.hpp"
#include <memory>

int main(int argc, char *argv[]){
    if(argc !=2){
        std::cerr << "Missing argument\n";
        return 1;
    }
    std::ifstream in(argv[1]);
    std::cout << "Opening file: " << argv[1] << std::endl;
    if(!in.is_open()){
        std::cerr << "Cannot Open File\n";
        return 1;
    }
    
    std::unique_ptr<Lexer> lexer;
    try{
        lexer = std::make_unique<Lexer>(in);

        Token token = lexer->nextToken();
        while(token != Token::END_OF_FILE){
            std::cout << "Token: " << Lexer::TokenToString(token) << "    Lexema: " << lexer->getText() << "    Line: " << lexer->getLineNumber() << std::endl;
            token = lexer->nextToken();
        }
    }catch(const std::exception &e){
        std::cerr << "Runtime error: " << e.what();
        if(lexer) std::cerr << " at line " << lexer->getLineNumber();
        std::cerr << std::endl;
        in.close();
        return 1;
    }catch(...){
        std::cerr << "Unknown runtime error";
        if(lexer) std::cerr << " at line " << lexer->getLineNumber();
        std::cerr << std::endl;
        in.close();
        return 1;
    }
    in.close();


    return 0;
}