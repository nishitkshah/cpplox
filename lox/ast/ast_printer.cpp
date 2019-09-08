// Reference: http://www.craftinginterpreters.com/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "ast_printer.hpp"
#include "expr.hpp"
#include "visitor_return.hpp"

namespace lox
{

    void AstPrinter::print(Expr* expr, VisitorReturn vr) {
        expr->accept(*this, vr);
    }

    void AstPrinter::visit(Expr::Binary* expr, VisitorReturn vr) {
        std::vector<Expr*> ep = {expr->left, expr->right};
        if(vr.return_type != VisitorReturnType::STRING){
            std::cerr << "AstPrinter expects VisitorReturnType STRING\n";
            throw "AstPrinter expects VisitorReturnType STRING\n";
        }
        std::string* ret_pt = (std::string*)vr.return_pointer;
        *(ret_pt) = parenthesize((expr->oper).lexeme, ep);
    }

    void AstPrinter::visit(Expr::Grouping* expr, VisitorReturn vr) {
        std::vector<Expr*> ep = {expr->expression};
        if(vr.return_type != VisitorReturnType::STRING){
            std::cerr << "AstPrinter expects VisitorReturnType STRING\n";
            throw "AstPrinter expects VisitorReturnType STRING\n";
        }
        std::string* ret_pt = (std::string*)vr.return_pointer;
        *(ret_pt) = parenthesize("group", ep);
    }

    void AstPrinter::visit(Expr::Literal* expr, VisitorReturn vr) {
        if(vr.return_type != VisitorReturnType::STRING){
            std::cerr << "AstPrinter expects VisitorReturnType STRING\n";
            throw "AstPrinter expects VisitorReturnType STRING\n";
        }
        std::string* ret_pt = (std::string*)vr.return_pointer;
        *(ret_pt) = expr->value;
    }

    void AstPrinter::visit(Expr::Unary* expr, VisitorReturn vr) {
        std::vector<Expr*> ep = {expr->right};
        if(vr.return_type != VisitorReturnType::STRING){
            std::cerr << "AstPrinter expects VisitorReturnType STRING\n";
            throw "AstPrinter expects VisitorReturnType STRING\n";
        }
        std::string* ret_pt = (std::string*)vr.return_pointer;
        *(ret_pt) = parenthesize((expr->oper).lexeme, ep);
    }

    std::string AstPrinter::parenthesize(std::string name, std::vector<Expr*> ep) {
        std::stringstream ss;
        ss << "(" << name;
        for(auto p: ep){
            std::string s;
            VisitorReturn vr(VisitorReturnType::STRING, &s);
            (p->accept)(*this, vr);
            ss << " " << s;
        }
        ss << ")";
        return ss.str();
    }

} // namespace lox

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
