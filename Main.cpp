#include<iostream>
#include<fstream>
#include "Lexer.cpp"

int main(int argc, char *argv[]){
    if(argc !=2){
        std::cerr << "Missing argument\n";
        return 1;
    }
    std::ifstream in(argv[1]);
    if(!in.is_open()){
        std::cerr << "Cannot Open File\n";
        return 1;
    }
    
    Lexer lexer(in);

    Token token = lexer.nextToken();
    while(token != Token::END_OF_FILE){
        std::cout << "Token:" << lexer.TokenToString(token) << "Lexema:" << lexer.getText() << std::endl;
        
    }
    in.close();


    return 0;
}