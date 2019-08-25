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
            class Unary;
            template <class T>
            class Visitor {
                virtual T visitBinaryExpr(Binary expr)=0;
                virtual T visitUnaryExpr(Unary expr)=0;
            };    // class Visitor

        template <class T>
        T accept(Visitor<T> visitor){}
    };    // class Expr
    
    class Expr::Binary : public Expr {
        public:
            Binary(Expr left, Token oper, Expr right) :
                left(left),
                oper(oper),
                right(right)
            {}
            
            template <class T>
            T accept(Visitor<T> visitor) {
                return visitor.visitBinaryExpr(*this);
            }
            
            Expr left;
            Token oper;
            Expr right;
    };    // class Binary
    
    class Expr::Unary : public Expr {
        public:
            Unary(Token oper, Expr right) :
                oper(oper),
                right(right)
            {
            }
            
            template <class T>
            T accept(Visitor<T> visitor) {
                return visitor.visitUnaryExpr(*this);
            }
            
            Token oper;
            Expr right;
    };    // class Unary
    
    
} // namespace lox

#endif
