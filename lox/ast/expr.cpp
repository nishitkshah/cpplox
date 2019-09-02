// Reference: http://www.craftinginterpreters.com/

#include <string>

#include "expr.hpp"
#include "token.hpp"
#include "token_type.hpp"

namespace lox {
    
    Expr::Binary::Binary(Expr* left, Token oper, Expr* right) :
        left(left),
        oper(oper),
        right(right)
    {}

    void Expr::Binary::accept(Visitor &visitor, VisitorReturn vr) {
        visitor.visit(this, vr);
    }
    
    Expr::Grouping::Grouping(Expr* expression) :
        expression(expression)
    {}
    
    void Expr::Grouping::accept(Visitor &visitor, VisitorReturn vr) {
        visitor.visit(this, vr);
    }
    
    Expr::Literal::Literal(std::string value, TokenType type) :
        value(value),
        type(type)
    {}
    
    void Expr::Literal::accept(Visitor &visitor, VisitorReturn vr) {
        visitor.visit(this, vr);
    }
    
    Expr::Unary::Unary(Token oper, Expr* right) :
        oper(oper),
        right(right)
    {}
    
    void Expr::Unary::accept(Visitor &visitor, VisitorReturn vr) {
        visitor.visit(this, vr);
    }
    
} // namespace lox
