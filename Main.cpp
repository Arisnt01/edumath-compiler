#include <iostream>
#include <fstream>

#include "antlr4-runtime.h"
#include "EduMathLexer.h"
#include "EduMathParser.h"
#include "EduMathDriver.h"

using namespace antlr4;
using namespace std;

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " archivo.EduMath" << endl;
        return 1;
    }

    ifstream stream;
    stream.open(argv[1]);
    if (!stream.is_open()) {
        cerr << "No se pudo abrir el archivo: " << argv[1] << endl;
        return 1;
    }

    ANTLRInputStream input(stream);
    EduMathLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    EduMathParser parser(&tokens);

    tree::ParseTree* tree = parser.programa();
    EduMathDriver driver;
    driver.visit(tree);

    return 0;
}
