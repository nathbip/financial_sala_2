Workflow implementation:


FERRACCI
    C++ core logic (/cpp-engine/src/TransactionProcessor.cpp + /cpp-engine/include/TransactionProcessor.h)

CARDINALI
    C++ tests (/cpp-engine/tests/test_processor.cpp + /cpp-engine/CMakeLists.txt)

ZANGARI
    python tests (/python-validator/tests/test_validate.py + /python-validator/validate.py)

CLAY
    CI/CD pipeline + docs (/.github\workflows/pipeline.yalm + /README.md)

