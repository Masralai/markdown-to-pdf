#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>


std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}

void writeFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not write to file: " + filename);
    }

    file << content;
    file.close();
}

void convertMarkdownToPdf(const std::string& mdFile, const std::string& pdfFile) {
    // Read the Markdown file
    std::string mdContent = readFile(mdFile);

    // Convert Markdown to HTML using md4c (assuming system command is available)
    std::string htmlFile = "temp.html";
    std::string command = "md4c --html " + mdFile + " > " + htmlFile;
    system(command.c_str());

    // Convert HTML to PDF using wkhtmltopdf
    command = "wkhtmltopdf " + htmlFile + " " + pdfFile;
    system(command.c_str());

    // Cleanup temp files
    std::remove(htmlFile.c_str());

    std::cout << "Converted " << mdFile << " to " << pdfFile << " successfully.\n";
}

int main() {
    try {
        convertMarkdownToPdf("sample.md", "output.pdf");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}
