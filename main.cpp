#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;


string readFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

void writeFile(const string& filename, const string& content) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not write to file: " + filename);
    }

    file << content;
    file.close();
}

void convertMarkdownToPdf(const string& mdFile, const string& pdfFile) {
   
    string mdContent = readFile(mdFile);

   
    string htmlFile = "temp.html";
    string command = "md4c --html " + mdFile + " > " + htmlFile;
    system(command.c_str());

   
    command = "wkhtmltopdf " + htmlFile + " " + pdfFile;
    system(command.c_str());


    remove(htmlFile.c_str());

    cout << "Converted " << mdFile << " to " << pdfFile << " successfully.\n";
}

int main() {
    try {
        convertMarkdownToPdf("sample.md", "output.pdf");
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}
