// Reference: http://www.craftinginterpreters.com/

#include "expr.hpp"
#include <string>
#include "token.hpp"

namespace lox {
    
    Expr::Binary::Binary(Expr left, Token oper, Expr right) :
        left(left),
        oper(oper),
        right(right)
    {}
    
    template <class T>
    T Expr::Binary::accept(Visitor<T> visitor) {
        return visitor.visitBinaryExpr(*this);
    }
    
    Expr::Grouping::Grouping(Expr expression) :
        expression(expression)
    {}
    
    template <class T>
    T Expr::Grouping::accept(Visitor<T> visitor) {
        return visitor.visitGroupingExpr(*this);
    }
    
    Expr::Literal::Literal(std::string value) :
        value(value)
    {}
    
    template <class T>
    T Expr::Literal::accept(Visitor<T> visitor) {
        return visitor.visitLiteralExpr(*this);
    }
    
    Expr::Unary::Unary(Token oper, Expr right) :
        oper(oper),
        right(right)
    {}
    
    template <class T>
    T Expr::Unary::accept(Visitor<T> visitor) {
        return visitor.visitUnaryExpr(*this);
    }
    
} // namespace lox
