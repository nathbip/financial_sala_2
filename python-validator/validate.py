import json
import sys
import os

def validate_report(filepath):
    if not os.path.exists(filepath):
        print(f"FAIL: File {filepath} not found.")
        return False

    try:
        with open(filepath, 'r') as f:
            data = json.load(f)
    except json.JSONDecodeError:
        print("FAIL: Invalid JSON format.")
        return False

    if not isinstance(data, dict):
        print("FAIL: JSON content must be an object, not a primitive.")
        return False

    errors = []

    # TODO_WORKSHOP: Rule 0: Strict Schema Validation
    # The JSON MUST contain exactly these keys: "count", "invalid_lines", "total", "average", "min", "max".
    # If any key is missing, or if extra keys exist, append an error and STOP validation.

    expected_keys = {"count", "invalid_lines", "total", "average", "min", "max"}
    if set(data.keys()) != expected_keys:
        errors.append(f"JSON must contain exactly these keys: {expected_keys}. Found: {set(data.keys())}")
        print("FAIL: Validation errors found:")
        for e in errors:
            print(f" - {e}")
        return False
    
    # Rule 1: Count
    if data.get("count", 0) <= 0:
        errors.append("count must be greater than 0")

    # Rule 2: Averages and Boundaries
    avg = data.get("average", 0)
    if avg > data.get("max", 0):
        errors.append("average cannot be greater than max")
        
    # TODO_WORKSHOP: Rule 3: Add check: 'min' cannot be greater than 'average'
    min_val = data.get("min", 0)
    if min_val > avg:
        errors.append("min cannot be greater than average")

    # TODO_WORKSHOP: Rule 4: Mathematical Consistency
    # Check that (count * average) is almost equal to total.
    # Hint: Use a small epsilon (e.g., 0.01) for floating-point comparison, don't use '=='!
    count = data.get("count", 0)
    total = data.get("total", 0)
    if abs(count * avg - total) > 0.01:
        errors.append("Mathematical inconsistency: (count * average) != total")

    if errors:
        print("FAIL: Validation errors found:")
        for e in errors:
            print(f" - {e}")
        return False

    print("PASS: Report is valid.")
    return True

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python validate.py <path_to_json>")
        sys.exit(1)
    
    success = validate_report(sys.argv[1])
    sys.exit(0 if success else 1)