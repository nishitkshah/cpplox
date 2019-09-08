// Reference: http://www.craftinginterpreters.com/

#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include "expr.hpp"
#include "visitor_return.hpp"

namespace lox
{

    class AstPrinter : Expr::Visitor {
        public:
            void print(Expr* expr, VisitorReturn vr);
            virtual void visit(Expr::Binary* expr, VisitorReturn vr) override;
            virtual void visit(Expr::Grouping* expr, VisitorReturn vr) override;
            virtual void visit(Expr::Literal* expr, VisitorReturn vr) override;
            virtual void visit(Expr::Unary* expr, VisitorReturn vr) override;

        private:
            std::string parenthesize(std::string name, std::vector<Expr*> ep);
    };

} // namespace lox

#endif

/*
int main() {
    lox::Expr* expression = new lox::Expr::Binary(
        new lox::Expr::Unary(
            lox::Token(lox::TokenType::MINUS, std::string("-"), std::string(""), 1),
            new lox::Expr::Literal(std::string("123"))
        ),
        lox::Token(lox::TokenType::STAR, std::string("*"), std::string(""), 1),
        new lox::Expr::Grouping(
            new lox::Expr::Literal(std::string("45.67"))
        )
    );
    std::string s;
    lox::VisitorReturn vr(lox::VisitorReturnType::STRING, &s);
    lox::AstPrinter ap;
    ap.print(expression, vr);
    std::cout << s;
}
*/
