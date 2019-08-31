// Reference: http://www.craftinginterpreters.com/

#ifndef EXPR_H
#define EXPR_H

#include <string>

#include "token.hpp"
#include "visitor_return.hpp"

namespace lox {
    
    class Expr {
        // Abstract class for Abstract Syntax Tree
        public:
            class Binary;
            class Grouping;
            class Literal;
            class Unary;
            
            class Visitor;
            
            virtual void accept(Expr::Visitor &visitor, VisitorReturn vr)=0;
    };    // class Expr
    
    class Expr::Visitor {
        public:
            virtual void visit(Binary* expr, VisitorReturn vr)=0;
            virtual void visit(Grouping* expr, VisitorReturn vr)=0;
            virtual void visit(Literal* expr, VisitorReturn vr)=0;
            virtual void visit(Unary* expr, VisitorReturn vr)=0;
    };    // class Visitor
    
    class Expr::Binary : public Expr {
        public:
            Binary(Expr* left, Token oper, Expr* right);
            
            virtual void accept(Visitor &visitor, VisitorReturn vr) override;
            
            Expr* left;
            Token oper;
            Expr* right;
    };    // class Binary
    
    class Expr::Grouping : public Expr {
        public:
            Grouping(Expr* expression);
            
            virtual void accept(Visitor &visitor, VisitorReturn vr) override;
                        
            Expr* expression;
    };    // class Grouping
    
    class Expr::Literal : public Expr {
        public:
            Literal(std::string value);
            
            virtual void accept(Visitor &visitor, VisitorReturn vr) override;
            
            std::string value;
    };    // class Literal
    
    class Expr::Unary : public Expr {
        public:
            Unary(Token oper, Expr* right);
            
            virtual void accept(Visitor &visitor, VisitorReturn vr) override;
            
            Token oper;
            Expr* right;
    };    // class Unary

} // namespace lox

#endif
