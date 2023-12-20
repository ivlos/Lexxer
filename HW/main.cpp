#include <iostream>
#include <vector>
#include "lexer.h"
#include "fsm.h"


using namespace std;


int main()
{
    Lexer lex(cin);
    Lexem buff = lex.getNextLexem();
    while (buff.first != LEX_EOF.first and buff.first != LEX_ERROR.first) {
        cout << buff.first << " " << buff.second << endl;
        buff = lex.getNextLexem();
    }

    return 0;
}
