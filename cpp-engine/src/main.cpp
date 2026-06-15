#include "TransactionProcessor.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <csv_filepath>\n";
        return 1;
    }

    TransactionProcessor processor;
    processor.ProcessFile(argv[1]);
    
    // Output JSON to stdout
    std::cout << processor.GenerateJSON();
    
    return 0;
}