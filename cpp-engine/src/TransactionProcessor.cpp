#include "TransactionProcessor.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>

void TransactionProcessor::ProcessLine(const std::string& line) {
    if (line.empty() || line.find("transaction_id") != std::string::npos) return;

    std::stringstream ss(line);
    std::string id_str, amount_str;

    if (std::getline(ss, id_str, ',') && std::getline(ss, amount_str, ',')) {
        try {
            double amount = std::stod(amount_str);
            
            // TODO_WORKSHOP: Implement Business Rule: Amounts MUST be strictly greater than 0.
            // If amount <= 0, increment invalid_lines and return early.
            if (amount <= 0) {
                current_report.invalid_lines++;
                return;
            }

            current_report.count++;
            current_report.total += amount;
            current_report.average = current_report.total / current_report.count;
            
            if (current_report.count == 1 || amount > current_report.max) {
                current_report.max = amount;
            }

            // TODO_WORKSHOP: Implement logic to track the minimum amount correctly.
            // Hint: Be careful when initializing min.
            if (current_report.count == 1 || amount < current_report.min) {
                current_report.min = amount;
            }
            

        } catch (...) {
            // TODO_WORKSHOP: If stod fails (e.g. invalid string), increment invalid_lines.
            current_report.invalid_lines++;
        }
    } else {
        // TODO_WORKSHOP: If line doesn't have a comma, increment invalid_lines.
        current_report.invalid_lines++;
    }
}

void TransactionProcessor::ProcessFile(const std::string& filepath) {
    std::ifstream file(filepath);
    std::string line;
    while (std::getline(file, line)) {
        ProcessLine(line);
    }
}

Report TransactionProcessor::GetReport() const { return current_report; }

std::string TransactionProcessor::GenerateJSON() const {
    std::stringstream ss;
    ss << "{\n";
    ss << "  \"count\": " << current_report.count << ",\n";
    // TODO_WORKSHOP: Print "invalid_lines" and "min" to the JSON output.
    ss << "  \"invalid_lines\": " << current_report.invalid_lines << ",\n";
    ss << "  \"min\": " << current_report.min << ",\n";
    ss << "  \"total\": " << current_report.total << ",\n";
    ss << "  \"average\": " << current_report.average << ",\n";
    ss << "  \"max\": " << current_report.max << "\n";
    ss << "}\n";
    return ss.str();
}