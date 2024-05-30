#pragma once

#include "../utils/errors.hh"
#include "nodes.hh"

namespace ast {
namespace eval {

class Evaluator : public types::ConstASTIntVisitor {
public:
    int result;

    int32_t visit(const types::IntegerLiteral &node) override {
        result = node.value;
        return result;
    }

    int32_t visit(const types::BinaryOperator &node) override {
        node.get_left().accept(*this);
        int left_value = result;

        node.get_right().accept(*this);
        int right_value = result;

        switch (node.op) {
            case types::o_plus:
                result = left_value + right_value;
                break;
            case types::o_minus:
                result = left_value - right_value;
                break;
            case types::o_times:
                result = left_value * right_value;
                break;
            case types::o_divide:
                result = left_value / right_value;
                break;
            case types::o_eq:
                result = left_value == right_value ? 1 : 0;
                break;
            case types::o_neq:
                result = left_value != right_value ? 1 : 0;
                break;
            case types::o_lt:
                result = left_value < right_value ? 1 : 0;
                break;
            case types::o_le:
                result = left_value <= right_value ? 1 : 0;
                break;
            case types::o_gt:
                result = left_value > right_value ? 1 : 0;
                break;
            case types::o_ge:
                result = left_value >= right_value ? 1 : 0;
                break;
            default:
                utils::error(node.loc, "Unsupported binary operator.");
        }
        return result;
    }

    int32_t visit(const types::Sequence &node) override {
        if (node.get_exprs().empty()) {
            utils::error(node.loc, "Empty sequence.");
        }

        for (const auto &expr : node.get_exprs()) {
            expr->accept(*this);
        }
        return result;
    }

    int32_t visit(const types::IfThenElse &node) override {
        node.get_condition().accept(*this);
        if (result) {
            node.get_then_part().accept(*this);
        } else {
            node.get_else_part().accept(*this);
        }
        return result;
    }

    int32_t visit(const types::StringLiteral &) override {
        utils::error(yy::location(), "StringLiteral not supported in this evaluator.");
        return 0;
    }

    int32_t visit(const types::Let &) override {
        utils::error(yy::location(), "Let not supported in this evaluator.");
        return 0;
    }

    int32_t visit(const types::Identifier &) override {
        utils::error(yy::location(), "Identifier not supported in this evaluator.");
        return 0;
    }

    int32_t visit(const types::VarDecl &) override {
        utils::error(yy::location(), "VarDecl not supported in this evaluator.");
        return 0;
    }

    int32_t visit(const types::FunDecl &) override {
        utils::error(yy::location(), "FunDecl not supported in this evaluator.");
        return 0;
    }

    int32_t visit(const types::FunCall &) override {
        utils::error(yy::location(), "FunCall not supported in this evaluator.");
        return 0;
    }

    int32_t visit(const types::WhileLoop &) override {
        utils::error(yy::location(), "WhileLoop not supported in this evaluator.");
        return 0;
    }

    int32_t visit(const types::ForLoop &) override {
        utils::error(yy::location(), "ForLoop not supported in this evaluator.");
        return 0;
    }

    int32_t visit(const types::Break &) override {
        utils::error(yy::location(), "Break not supported in this evaluator.");
        return 0;
    }

    int32_t visit(const types::Assign &) override {
        utils::error(yy::location(), "Assign not supported in this evaluator.");
        return 0;
    }
};

} 
}
