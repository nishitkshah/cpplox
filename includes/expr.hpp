// Reference: http://www.craftinginterpreters.com/

#ifndef EXPR_H
#define EXPR_H

#include <string>
#include "token.hpp"

namespace lox {
    
    class Expr {
        // Abstract class for Abstract Syntax Tree
        public:
            class Binary;
            class Grouping;
            class Literal;
            class Unary;
            template <class T>
            class Visitor;
            
            template <class T>
            T accept(Visitor<T> &visitor){}
    };    // class Expr
    
    template <class T>
    class Expr::Visitor {
        virtual T visitBinaryExpr(Binary* expr)=0;
        virtual T visitGroupingExpr(Grouping* expr)=0;
        virtual T visitLiteralExpr(Literal* expr)=0;
        virtual T visitUnaryExpr(Unary* expr)=0;
    };    // class Visitor
    
    class Expr::Binary : public Expr {
        public:
            Binary(Expr* left, Token oper, Expr* right);
            
            template <class T>
            T accept(Expr::Visitor<T> &visitor);
            
            Expr* left;
            Token oper;
            Expr* right;
    };    // class Binary
    
    class Expr::Grouping : public Expr {
        public:
            Grouping(Expr* expression);
            
            template <class T>
            T accept(Expr::Visitor<T> &visitor);
            
            Expr* expression;
    };    // class Grouping
    
    class Expr::Literal : public Expr {
        public:
            Literal(std::string value);
            
            template <class T>
            T accept(Expr::Visitor<T> &visitor);
            
            std::string value;
    };    // class Literal
    
    class Expr::Unary : public Expr {
        public:
            Unary(Token oper, Expr* right);
            
            template <class T>
            T accept(Expr::Visitor<T> &visitor);
            
            Token oper;
            Expr* right;
    };    // class Unary
    
} // namespace lox

#endif
