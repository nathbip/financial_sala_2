#pragma once
#include <string>
#include <vector>

struct Report {
    int count = 0;
    int invalid_lines = 0; // TODO_WORKSHOP: Track lines that are malformed or have amount <= 0
    double total = 0.0;
    double average = 0.0;
    double max = 0.0;
    double min = 0.0;      // TODO_WORKSHOP: Track the minimum valid amount
};

class TransactionProcessor {
    Report current_report;
public:
    void ProcessLine(const std::string& line);
    void ProcessFile(const std::string& filepath);
    Report GetReport() const;
    std::string GenerateJSON() const;
};