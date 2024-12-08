sticky_notes = ["12345", "54321", "00000", "11111", "22222", "101", "1010", "01010", "0010100", "0001000", "245235", "5862362", "822245234",
                "5126354862362", "094759265038467294", "11211"]


def report_combination(codes):
    global total_combinations
    print(f"* {",".join(codes)}")
    total_combinations += 1

## Main code starts here

def is_valid(codes):
    numbers = [int(num) for num in codes]
    for i in range(len(numbers) - 1):
        if numbers[i] % 2 == 0 and numbers[i] > numbers[i + 1]:
            return False
    return True

def helper(head, tail):
    if not tail:
        if is_valid(head):
            report_combination(head)
        return
    for i in range(1, len(tail) + 1):
        if is_valid(head + [tail[:i]]):
            helper(head + [tail[:i]], tail[i:])

## Main code ends here

def extract_combinations(sequence):
    helper(head=[], tail=sequence)

for sticky_note in sticky_notes:
    print(f"? {sticky_note}")
    print("Sequence:")
    total_combinations = 0
    extract_combinations(sticky_note)
    print(f"Total: {total_combinations}")
