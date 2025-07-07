#pragma once

#include "antlr4-runtime.h"
#include "EduMathBaseVisitor.h"
#include <any>
#include <iostream>
#include <cmath>

class EduMathDriver : public EduMathBaseVisitor {
public:
    std::any visitPrograma(EduMathParser::ProgramaContext* ctx) override {
        for (auto instr : ctx->instruccion()) {
            visit(instr);
        }
        return nullptr;
    }

    std::any visitInstruccion(EduMathParser::InstruccionContext* ctx) override {
        double val = std::any_cast<double>(visit(ctx->expresion()));
        std::cout << "Resultado: " << val << std::endl;
        return val;
    }

    std::any visitExpresion(EduMathParser::ExpresionContext* ctx) override {
        return visit(ctx->potencia());
    }

    std::any visitPotencia(EduMathParser::PotenciaContext* ctx) override {
        double base = std::any_cast<double>(visit(ctx->suma()));
        if (ctx->potencia()) {
            double exponente = std::any_cast<double>(visit(ctx->potencia()));
            return pow(base, exponente);
        }
        return base;
    }

    std::any visitSuma(EduMathParser::SumaContext* ctx) override {
        double result = std::any_cast<double>(visit(ctx->producto(0)));
        for (size_t i = 1; i < ctx->producto().size(); ++i) {
            double right = std::any_cast<double>(visit(ctx->producto(i)));
            std::string op = ctx->children[2 * i - 1]->getText();
            if (op == "+") result += right;
            else if (op == "-") result -= right;
        }
        return result;
    }

    std::any visitProducto(EduMathParser::ProductoContext* ctx) override {
        double result = std::any_cast<double>(visit(ctx->atomo(0)));
        for (size_t i = 1; i < ctx->atomo().size(); ++i) {
            double right = std::any_cast<double>(visit(ctx->atomo(i)));
            std::string op = ctx->children[2 * i - 1]->getText();
            if (op == "*") result *= right;
            else if (op == "/") result = (right != 0) ? result / right : 0;
        }
        return result;
    }

    std::any visitAtomo(EduMathParser::AtomoContext* ctx) override {
        if (ctx->NUMERO()) {
            return std::stod(ctx->NUMERO()->getText());
        }

        std::string firstToken = ctx->getStart()->getText();

        if (firstToken == "raiz") {
            return sqrt(std::any_cast<double>(visit(ctx->expresion())));
        }

        if (ctx->expresion()) {
            return std::any_cast<double>(visit(ctx->expresion()));
        }

        return 0.0;
    }
};
