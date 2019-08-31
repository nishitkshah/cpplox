#include "expr.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace lox
{

    class AstPrinter : Expr::Visitor<std::string> {
        public:
            std::string print(Expr* expr) {                                            
                return expr->accept<std::string>(*this);                                          
            }

            virtual std::string visitBinaryExpr(Expr::Binary* expr) override {
                std::vector<Expr*> ep = {expr->left, expr->right};
                return parenthesize((expr->oper).lexeme, ep);
            }

            virtual std::string visitGroupingExpr(Expr::Grouping* expr) override {
                std::vector<Expr*> ep = {expr->expression};
                return parenthesize("group", ep);
            }

            virtual std::string visitLiteralExpr(Expr::Literal* expr) override {
                return expr->value;
            }

            virtual std::string visitUnaryExpr(Expr::Unary* expr) override {
                std::vector<Expr*> ep = {expr->right};
                return parenthesize((expr->oper).lexeme, ep);
            }

        private:
            std::string parenthesize(std::string name, std::vector<Expr*> ep) {
                std::stringstream ss;
                ss << "(" << name;
                for(auto p: ep)
                    ss << " " << (p->accept)(*this);
                ss << ")";
                return ss.str();
            }
    };

} // namespace lox

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
    lox::AstPrinter ap;
    std::cout << ap.print(expression);
}
