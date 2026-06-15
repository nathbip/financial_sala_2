# Financial Data Platform

Welcome to the Financial Data Platform. This repository contains a multi-language software delivery project designed to process, aggregate, and validate financial transactions.

## Project Purpose
A financial institution receives daily transaction data (CSV). Before routing this data to downstream reporting systems, it must be aggregated by a high-performance C++ engine and validated by a robust Python service.

## Repository Structure
* `cpp-engine/`: C++17 engine that aggregates CSV data into JSON metrics.
* `python-validator/`: Python service that enforces business rules on the JSON output.
* `data/`: Sample input files.
* `docs/`: Architecture diagrams and team planning templates.
* `.github/workflows/`: CI/CD automation.

## How to Build and Run Locally

### 1. C++ Engine
```bash
cd cpp-engine
cmake -B build
cmake --build build
./build/engine ../data/transactions.csv > report.json

cd python-validator
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
python validate.py ../cpp-engine/report.json
