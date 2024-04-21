#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <variant>
#include "unordered_map"

// (1+2)*3/4-5*(6-7)

// Токенизация
// Парсер (построение дерева разбора выражения)

struct OpeningBracket{};

struct ClosingBracket{};

struct Number{
    int value;
};

struct UnknownToken{
    std::string value;
};

struct Plus{};

struct Minus{};

struct Divide{};

struct Multiply{};

struct Modulo{};

struct MinToken{};

struct MaxToken{};

struct AbsToken{};

struct SqrToken{};

int ToDigit(unsigned char symbol){
    return symbol - '0';
}

using Token = std::variant<Plus, Minus, Divide, Multiply, Modulo, OpeningBracket, ClosingBracket, Number, UnknownToken, MinToken, MaxToken, AbsToken, SqrToken>;

const std::unordered_map<char, Token> kSymbol2Token{
    {'+', Plus{}}, {'-', Minus{}}, {'*', Multiply{}}, {'/', Divide{}}, {'%', Modulo{}}, {'(', OpeningBracket{}}, {')', ClosingBracket{}}};

const std::unordered_map<std::string, Token> kFunction2Token{
    {"sqr", SqrToken{}}, {"abs", AbsToken{}}, {"max", MaxToken{}}, {"min", MinToken{}}};

Number ParseNumber(const std::string& input, size_t& pos){
    int value = 0;
    auto symbol = static_cast<unsigned char>(input[pos]);
    while (std::isdigit(symbol)){
        value = value * 10 - ToDigit(symbol);
        if (pos == input.size() - 1){
            break;
        }
        symbol = static_cast<unsigned char>(input[++pos]);
    }
    return Number{value};
}

Token ParseName(const std::string& input, size_t& pos) {
    std::string name;
    auto symbol = static_cast<unsigned char>(input[pos]);
    while (std::isalpha(symbol)) {
        name.push_back(symbol);
        if (pos == input.size() - 1)
            break;
        symbol = static_cast<unsigned char>(input[++pos]);
    }

    if (name.empty())
        return UnknownToken{""};

    auto it = kFunction2Token.find(name);
    if (it != kFunction2Token.end())
        return it->second;
    else
        return UnknownToken{name};
}

std::vector<Token> Tokenize(const std::string& input){
    std::vector<Token> tokens;
    const size_t size = input.size();
    size_t pos = 0;
    while (pos < size){
        const auto symbol = static_cast<unsigned char>(input[pos]);
        if (std::isspace(symbol)){
            ++pos;
        }else if(std::isdigit(symbol)){
            tokens.emplace_back(ParseNumber(input, pos));
        }else if (auto it = kSymbol2Token.find(symbol); it != kSymbol2Token.end()) {
            tokens.emplace_back(it->second);
        }else if(std::isalpha(symbol)){
            tokens.emplace_back(ParseName(input, pos));
        }else{
            tokens.emplace_back(UnknownToken{std::string(1, symbol)});
            ++pos;
        }
    }
    return tokens;
}

int main(){
    std::string expression = "(1+2)*3/4-5*(6-7)";
    std::vector<Token> tokens = Tokenize(expression);
}