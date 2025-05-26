import sys
import math

from utils import Utils

sys.setrecursionlimit(42)

def debug(depth, *msg):
    print("    " * depth, end="")
    print(*msg)


class Chunk:
    def __init__(self, data: list[int]):
        self.key = data[-1]
        self.data = data
        self.size = len(data)

    def __repr__(self):
        return f"{self.data}"

    def __lt__(self, other: "Chunk"):
        return self.key < other.key

    def __mt__(self, other: "Chunk"):
        return self.key > other.key
    
    def divide(self):
        n = self.size // 2
        return Chunk(self.data[:n]), Chunk(self.data[n:])

# implement with static var in c++ later, "Generator class"
def jacobsthal_decreasing():
    a, b = 0, 1
    while True:
        for i in range(b, a, -1):
            yield i
        a, b = b, b + 2 * a

compare_count = 0
def _merge_insertion(chunks, depth=0):
    global compare_count
    
    if len(chunks) == 1:
        return chunks
    # debug(depth, "(0)", f"chunks={chunks}")

    pairs: list[Chunk] = []
    remainder_chunk = None
    for i in range(0, len(chunks) - 1, 2):
        compare_count += 1
        if chunks[i] < chunks[i + 1]:
            pair = Chunk(chunks[i].data + chunks[i + 1].data)
        else:
            pair = Chunk(chunks[i + 1].data + chunks[i].data)
        pairs.append(pair)
    if len(chunks) % 2 == 1:
        remainder_chunk = chunks[-1]

    # debug(depth, "(1)", f"pairs={pairs}", f"remainder_chunk={remainder_chunk}")

    pairs = _merge_insertion(pairs, depth=depth+1)
    # debug(depth, "(2)", f"pairs={pairs}", f"remainder_chunk={remainder_chunk}")

    # chunks = []
    to_insert: list[Chunk] = []
    main_chain: list[Chunk] = []
    for pair in pairs:
        lesser, greater = pair.divide()
        to_insert.append(lesser)
        main_chain.append(greater)
    if remainder_chunk:
        to_insert.append(remainder_chunk)

    # debug(depth, "(3.1)", f"to_insert={to_insert}", f"main_chain={main_chain}")

    number_inserted = 0

    for i in jacobsthal_decreasing():
        i -= 1
        if i >= len(to_insert):
            continue

        l = 0
        r = number_inserted + i
        while l < r:
            m = (l + r) // 2
            compare_count += 1
            if to_insert[i] < main_chain[m]:
                r = m
            else:
                l = m + 1
        
        main_chain.insert(r, to_insert[i])
        number_inserted += 1
        if number_inserted >= len(to_insert):
            break

    # debug(depth, "(3.2)", f"main_chain={main_chain}")

    return main_chain

def sort(arr):
    global compare_count

    compare_count = 0

    chunks: list[Chunk] = []
    for i in range(len(arr)):
        chunk = Chunk([arr[i]])
        chunks.append(chunk)

    chunks = _merge_insertion(chunks, depth=0)

    arr = []
    for chunk in chunks:
        arr.append(chunk.key)
    return arr

def max_compare_count_formula(n):
    return sum(math.ceil(math.log2(3/4 * k)) for k in range(1, n + 1))

n = 1000
for i in range(100):
    arr = Utils.random_arr(n=n)
    print(" ".join(map(str, arr)))
    sorted_arr = sort(arr)
    print(" ".join(map(str, sorted_arr)))
    print("Compare count:", compare_count)

    max_compare_count = max_compare_count_formula(n)
    GREEN = "\033[32m"
    RESET = "\033[0m"
    print("Max compare:  ", f"{GREEN}{max_compare_count}{RESET}" if compare_count <= max_compare_count else max_compare_count)

    assert Utils.is_items_same(arr, sorted_arr)
    assert Utils.is_sorted(sorted_arr)
    assert compare_count <= max_compare_count
