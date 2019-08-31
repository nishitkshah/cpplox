// Reference: http://www.craftinginterpreters.com/

#include "expr.hpp"
#include <string>
#include "token.hpp"

namespace lox {
    
    Expr::Expr(ExprType expr_type) :
        expr_type(expr_type)
    {}
    
    Expr::Binary::Binary(Expr* left, Token oper, Expr* right) :
        Expr(ExprType::BINARY),
        left(left),
        oper(oper),
        right(right)
    {}
        
    Expr::Grouping::Grouping(Expr* expression) :
        Expr(ExprType::GROUPING),
        expression(expression)
    {}
    
    Expr::Literal::Literal(std::string value) :
        Expr(ExprType::LITERAL),
        value(value)
    {}
    
    Expr::Unary::Unary(Token oper, Expr* right) :
        Expr(ExprType::UNARY),
        oper(oper),
        right(right)
    {}

    template <class T>
    T Expr::accept(Expr::Visitor<T> &visitor) {
        Binary* binary;
        Grouping* grouping;
        Literal* literal;
        Unary* unary;
        switch(this->expr_type) {
            case ExprType::BINARY :
                binary = (Binary*)this;
                return binary->accept(visitor);
            case ExprType::GROUPING :
                grouping = (Grouping*)this;
                return grouping->accept<T>(visitor);
            case ExprType::LITERAL :
                literal = (Literal*)this;
                return literal->accept<T>(visitor);
            case ExprType::UNARY :
                unary = (Unary*)this;
                return unary->accept<T>(visitor);
        }
    }
    
} // namespace lox
