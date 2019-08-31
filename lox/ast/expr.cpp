// Reference: http://www.craftinginterpreters.com/

#include "expr.hpp"
#include <string>
#include "token.hpp"

namespace lox {
    
    Expr::Binary::Binary(Expr* left, Token oper, Expr* right) :
        left(left),
        oper(oper),
        right(right)
    {}
        
    Expr::Grouping::Grouping(Expr* expression) :
        expression(expression)
    {}
    
    Expr::Literal::Literal(std::string value) :
        value(value)
    {}
    
    Expr::Unary::Unary(Token oper, Expr* right) :
        oper(oper),
        right(right)
    {}
    
} // namespace lox
