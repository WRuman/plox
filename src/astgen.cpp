#include <iostream>
#include <fstream>
#include <sysexits.h>
#include <vector>

/**
 * Take a deep breath and accept that we live in an imperfect world. 
 * Life is not a puzzle with a solution and refactoring this code will 
 * not make you happy.
 */
void defineType(std::fstream& fs, const std::string baseClass, const std::string data) {
    size_t leftBound = 0;
    size_t rightBound = data.find('|');
    const auto typeName = data.substr(leftBound, rightBound);
    auto fields = std::vector<std::string>();
    fs << "class " << typeName << " : public " << baseClass << "{\nprivate:" << std::endl;
    for (;;) {
        leftBound = rightBound + 1;
        rightBound = data.find(',', leftBound);
        if (rightBound != std::string::npos) {
            fields.push_back(data.substr(leftBound, rightBound - leftBound));
        } else {
            // Last one
            fields.push_back(data.substr(leftBound, std::string::npos));
            break;
        }
    }
    for (auto f : fields) {
        fs << "\t" << f << ";" << std::endl;
    }

    fs << "public:" << std::endl << typeName << "(";
    std::string initList = "";
    auto commas = fields.size() - 1;
    for (auto f : fields) {
        auto paramName = f.substr(f.find_last_of(' ') + 1, std::string::npos);
        initList += paramName + '(' + paramName + ')';
        fs << f; 
        if (commas > 0) {
            initList += ", ";
            fs << ", ";
            commas--;
        }
    }
    fs << "): " << initList << " {};" << std::endl << "};" << std::endl;
    std::cerr << "Generated type '" << typeName << "' with " << fields.size() << " fields" << std::endl;
}

void defineAst(const std::string destDir, const std::string baseName, const std::vector<std::string> types) {
    auto target = destDir + "/" + baseName + ".h";
    std::fstream fs(target, std::fstream::out | std::fstream::trunc);
    if (!fs) {
        std::cerr << "Could not open '" << target << "' for writing" << std::endl;
        throw EXIT_FAILURE;
    }
    fs  << "// THIS CODE IS AUTOMATICALLY GENERATED. MANUAL EDITS WILL BE OVERWRITTEN!" 
        << std::endl << "#ifndef " << baseName <<  "_H\n#define " << baseName  << "_H\n"
        << "#include <string>\n#include <Token.h>"
        << "\n\n" << "namespace pl {\n"
        << "class " << baseName << "{\n" 
        << "public:\n\t" << baseName << "() {}\n\tvirtual ~" << baseName << "()=0;\n"
        << "};\n";
    
    for (auto data : types) {
        defineType(fs, baseName, data);
    }
    fs << "}\n#endif";
}

int main() {
    defineAst(".", "Expr", std::vector<std::string>{
        "Binary | pl::Expr& left, pl::Token& op, pl::Expr& right",
        "Grouping | pl::Expr& expression",
        "Literal | std::string value",
        "Unary | pl::Token& op, pl::Expr& right"
    });
    return 0;
}
