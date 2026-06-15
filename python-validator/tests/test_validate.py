import pytest
import json
import os
from validate import validate_report

def create_temp_json(tmp_path, data):
    file_path = tmp_path / "test.json"
    with open(file_path, 'w') as f:
        json.dump(data, f)
    return str(file_path)

def test_valid_report(tmp_path):
    data = {
        "count": 2, "invalid_lines": 0, "total": 200.0, 
        "average": 100.0, "min": 50.0, "max": 150.0
    }
    filepath = create_temp_json(tmp_path, data)
    assert validate_report(filepath) == True

# ==========================================
# TODO_WORKSHOP: IMPLEMENT THE FOLLOWING TESTS
# ==========================================

def test_missing_keys_fails(tmp_path):
    """
    Create a JSON missing the 'invalid_lines' key.
    Assert that validate_report returns False.
    """
    pytest.fail("TODO_WORKSHOP: Implement this test")

def test_min_greater_than_average_fails(tmp_path):
    """
    Create a valid JSON but set 'min' to 200 and 'average' to 100.
    Assert that validate_report returns False.
    """
    pytest.fail("TODO_WORKSHOP: Implement this test")

def test_math_inconsistency_fails(tmp_path):
    """
    Create a JSON where count=2, average=100.0, but total=500.0.
    This violates (count * average == total).
    Assert that validate_report returns False.
    """
    pytest.fail("TODO_WORKSHOP: Implement this test")

def test_malformed_json_file(tmp_path):
    """
    Create a text file that contains invalid JSON (e.g. "{ bad string ]").
    Assert that validate_report returns False and handles the exception gracefully.
    """
    pytest.fail("TODO_WORKSHOP: Implement this test")