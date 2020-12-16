#include <iostream>
#include <fstream>
#include <sysexits.h>
#include <vector>

void defineType(std::fstream& fs, const std::string baseClass, const std::string data) {
    auto nameBrk = data.find(':');
    auto typeName = data.substr(0, nameBrk);
    //std::vector<std::string> fields();

    fs << "class " << typeName << " : public " << baseClass << "{\n\t"
        << "};\n";
}

void defineAst(const std::string destDir, const std::string baseName, const std::vector<std::string> types) {
    auto target = destDir + "/" + baseName + ".h";
    std::fstream fs(target, std::fstream::out | std::fstream::trunc);
    if (!fs) {
        std::cerr << "Could not open '" << target << "' for writing" << std::endl;
        throw EXIT_FAILURE;
    }
    fs << "#ifndef " << baseName <<  "_H\n#define " << baseName  << "_H\n"
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
        "Binary:pl::Expr left,pl::Token operator,pl::Expr right",
        "Grouping:pl::Expr expression",
        "Literal:std::string value",
        "Unary:pl::Token operator,pl::Expr right"
    });
    return 0;
}
