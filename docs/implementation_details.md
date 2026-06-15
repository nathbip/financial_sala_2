
Workflow implementation

Team division and responsibilities

- Ferracci: C++ core logic
    - Files: cpp-engine/src/TransactionProcessor.cpp, cpp-engine/include/TransactionProcessor.h
    - Responsibilities: implement parsing, business rules, compute metrics (`count`, `invalid_lines`, `total`, `average`, `min`, `max`), and produce JSON output.

- Cardinali: C++ tests and build integration
    - Files: cpp-engine/tests/test_processor.cpp, cpp-engine/CMakeLists.txt
    - Responsibilities: complete unit tests covering edge cases (malformed lines, zero/negative amounts, floating-point precision, min/max), and ensure CMake correctly builds tests.

- Zangari: Python validator and Python tests
    - Files: python-validator/validate.py, python-validator/tests/
    - Responsibilities: implement strict schema and consistency rules, and make validator exit with non-zero status on failure.

- Clay: CI/CD pipeline, docs, integration
    - Files: .github/workflows/pipeline.yaml, README.md, docs/
    - Responsibilities: author GitHub Actions workflow to build and test both components, add linting and artifacts, and keep docs updated.

Design choices

1) C++ engine
- Robust parsing: skip header lines, handle malformed rows by incrementing `invalid_lines` and continuing.
- Business rules: amounts must be strictly > 0; non-positive or unparsable amounts count as invalid
- Output format: JSON must include exactly the keys required by the validator: `count`, `invalid_lines`, `total`, `average`, `min`, `max`.

2) Tests
- C++ tests (GoogleTest): focus on correctness and edge cases. For floating-point sums, use `EXPECT_NEAR` with a small epsilon (e.g., 0.01) to avoid false negatives.
- Python tests: validate validator behavior (PASS/FAIL) given crafted JSON files, and test schema enforcement and mathematical consistency.

3) Python validator
- Schema enforcement: require exactly these keys: `count`, `invalid_lines`, `total`, `average`, `min`, `max` and reject extra/missing keys.
- Consistency checks: ensure `min <= average <= max` and that `abs(count * average - total) <= epsilon` (epsilon = 0.01 by default).
- UX: print clear PASS/FAIL messages and exit 0/1 for CI integration.

4) CI / GitHub Actions (high level)
- Trigger: `push` and `pull_request` on main branches.
- Jobs:
    - `build_cpp`: setup CMake, build `engine` and `engine_tests`, run `engine_tests`.
    - `python_tests`: create a venv, install `requirements.txt`, run `python validate.py` against produced or sample JSON.
    - `lint`: run `flake8` for Python.


Collaboration & workflow
- PRs: Require at least one approving review and passing CI before merge.
- Ownership: each teammate is primary owner of their area but should review integration PRs.


See README for an overview and the `data/` folder for sample inputs.


