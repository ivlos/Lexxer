#include "fsm.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>




using namespace std;

void read(char& cache, istream& stream) {
    if (stream) {
        stream.get(cache);
    }
    if (!stream) {
        cache = 0;
    }
}

string value;
map<string, string> keywords = { {"int", "kwint"},{"char", "kwchar"},{"if", "kwif"},{"else", "kwelse"},{"switch", "kwswitch"},{"case", "kwcase"},{"while", "kwwhile"},{"for", "kwfor"},{"return", "kwreturn"},{"in", "kwin"}, {"out", "kwout"} };

pair<int, Lexem> tick(int state, istream& stream, char& cache) {
    switch (state) {
    case 0:
        value = "";
        switch (cache) {
        case '<':
            read(cache, stream);
            return { 2, {"", ""} };
        case '!':
            read(cache, stream);
            return { 4,{"",""} };
        case '=':
            read(cache, stream);
            return{ 6,{"",""} };
        case '+':
            read(cache, stream);
            return { 8,{"",""} };
        case'(':
            read(cache, stream);
            return { 1,{"lpar",""} };
        case')':
            read(cache, stream);
            return { 1,{"rpar",""} };
        case'{':
            read(cache, stream);
            return { 1,{"lbrace",""} };
        case'}':
            read(cache, stream);
            return { 1,{"rbrace",""} };
        case';':
            read(cache, stream);
            return { 1,{"semicolon",""} };
        case',':
            read(cache, stream);
            return { 1,{"comma",""} };
        case':':
            read(cache, stream);
            return { 1,{"colon",""} };
        case'>':
            read(cache, stream);
            return { 1,{"opgt",""} };
        case'*':
            read(cache, stream);
            return { 1,{"opmul",""} };
        case'|':
            read(cache, stream);
            return { 10,{"",""} };
        case'&':
            read(cache, stream);
            return { 12,{"",""} };
        case'\'':
            read(cache, stream);
            value = cache;
            return { 14,{"",""} };
        case'"':
            read(cache, stream);
            return { 18,{"",""} };
        case '-':
            value = "-";
            read(cache, stream);
            return { 22, {"",""} };
        case ' ':
        case '\t':
        case '\n':
            read(cache, stream);
            return { 0, LEX_EMPTY };

        case '$':
            return { -1, LEX_EOF };
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return { 23, {"", ""} };

        default:
            return { 21, {"", ""} };
        }


    case 1:
        return { 0,{"",""} };


    case 2:
        switch (cache) {
        case'=':
            read(cache, stream);
            return { 3,{"",""} };
        default:
            read(cache, stream);
            return { 0,{"oplt",""} };
        }


    case 3:
        read(cache, stream);
        return { 0, {"ople",""} };


    case 4:
        switch (cache) {
        case'=':
            read(cache, stream);
            return { 5, {"",""} };
        default:
            read(cache, stream);
            return { 0, {"opnot",""} };
        }


    case 5:
        read(cache, stream);
        return { 0, {"opne",""} };


    case 6:
        switch (cache) {
        case'=':
            read(cache, stream);
            return { 7, {"",""} };
        default:
            read(cache, stream);
            return { 0, {"opassign",""} };
        }



    case 7:
        read(cache, stream);
        return { 0, {"opeq",""} };


    case 8:
        switch (cache) {
        case'+':
            read(cache, stream);
            return { 9, {"",""} };
        default:
            read(cache, stream);
            return { 0, {"opplus",""} };
        }


    case 9:
        read(cache, stream);
        return { 0, {"opinc",""} };


    case 10:
        switch (cache) {
        case'|':
            read(cache, stream);
            return { 11, {"",""} };
        default:
            read(cache, stream);
            return { -1, LEX_ERROR };
        }



    case 11:
        read(cache, stream);
        return { 0, {"opor",""} };


    case 12:
        switch (cache) {
        case'&':
            read(cache, stream);
            return { 13, {"",""} };
        default:
            read(cache, stream);
            return { -1, LEX_ERROR };
        }


    case 13:
        read(cache, stream);
        return { 0, {"opand",""} };


    case 14:
        switch (cache) {
        case'\'':
            read(cache, stream);
            return { 15, {"",""} };
        default:
            read(cache, stream);
            return { 16, {"",""} };
        }


    case 15:
        read(cache, stream);
        return { -1, LEX_ERROR };


    case 16:
        switch (cache) {
        case'\'':
            read(cache, stream);
            return { 17, {"",""} };
        default:
            read(cache, stream);
            return { -1, LEX_ERROR };
        }


    case 17:
        read(cache, stream);
        return { 0, {"char",value} };


    case 18:
        switch (cache) {
        case '"':
            read(cache, stream);
            return{ 20,{"",""} };
        case'$':
            read(cache, stream);
            return { 19, {"",""} };

        default:
            while (cache != '"') {
                value += cache;
                stream.get(cache);
            }
            stream.unget();
            return { 18, {"",""} };

        }


    case 19:
        read(cache, stream);
        return { -1, LEX_ERROR };


    case 20:
        read(cache, stream);
        return { 0, {"str",value} };

    case 21:

        while (isalpha(cache)) {
            value += cache;
            stream.get(cache);
        }

        if (keywords.contains(value)) {
            return { 0, {keywords[value], ""} };
        }

        return { 0, {"id", value} };


    case 22:
        switch (cache) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            value += cache;
            read(cache, stream);
            return{ 23, {"", ""} };
        default:
            read(cache, stream);
            return { 0, {"opminus", ""} };
        }

    case 23:
        while (isdigit(cache)) {
            value += cache;
            stream.get(cache);
        }
        stream.unget();
        read(cache, stream);

        return { 0, {"num", value} };

    default:
        return { -1, LEX_EMPTY };
    }
}



