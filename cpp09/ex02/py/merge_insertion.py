import sys
import math

from utils import Utils

sys.setrecursionlimit(10)

def debug(depth, *msg):
    print("    " * depth, end="")
    print(*msg)

def _merge_insertion_old(arr, depth=0):
    if len(arr) == 1:
        return arr
    debug(depth, "merge_insertion", arr)

    large = []
    small = []
    for i in range(0, len(arr), 2):
        if arr[i] > arr[i + 1]:
            arr[i], arr[i + 1] = arr[i + 1], arr[i]
        small.append(arr[i])
        large.append(arr[i + 1])
    debug(depth, "(1) >", f"arr={arr}", f"small={small}", f"large={large}")

    arr = merge_insertion(large, depth + 1)
    debug(depth, "(2) >", f"arr={arr}", f"small={small}")

    arr.insert(0, small[0])
    for i in range(1, len(small)):
        insert_idx = len(small)
        for j in range(len(small)):
            if small[i] < arr[j]:
                insert_idx = j
                # debug(depth, "found insert_idx at", insert_idx)
                break
        arr.insert(insert_idx, small[i])
        # debug(depth, insert_idx, arr)

    debug(depth, "(3) >", f"arr={arr}")
    return arr

def swap(arr, pair_size, a, b, depth=0):
    for i in range(pair_size):
        # debug(depth, "swap", a + i, b + i)
        arr[a + i], arr[b + i] = arr[b + i], arr[a + i]

def __merge_insertion_old(arr, depth=0):
    debug(depth, "(0) -", arr, f"depth={depth}")
    chunk_size = 2 ** depth
    pair_size = 2 * chunk_size
    if chunk_size >= len(arr):
        return arr

    for i in range(0, len(arr), pair_size):
        cur = i + chunk_size - 1
        next_ = i + pair_size - 1
        if next_ >= len(arr):
            break
        debug(depth, "compare", cur, next_)
        if arr[cur] > arr[next_]:
            swap(arr, chunk_size, i, i + chunk_size, depth=depth)
    debug(depth, "(1) -", arr)

    arr = merge_insertion(arr, depth + 1)
    debug(depth, "(2) -", arr)

    main_chain = []
    to_insert = []
    for i in range(0, len(arr), 2 * chunk_size):
        to_insert.extend(arr[i:i + chunk_size]) # each chunk is chunk_size long
        main_chain.extend(arr[i + chunk_size:i + 2*chunk_size])

    debug(depth, f"chunk_size={chunk_size}")
    debug(depth, f"to_insert={to_insert}", f"main_chain={main_chain}")
    for i in range(0, len(to_insert), chunk_size):
        
        insert_idx = len(main_chain) - chunk_size
        # debug(depth, i)
        cur = i + chunk_size - 1
        for j in range(0, len(main_chain), chunk_size):
            next_ = j + chunk_size - 1
            if to_insert[cur] < main_chain[next_]: 
                insert_idx = j
                break
            # debug(depth)
        
        debug(depth, "inserting at", insert_idx)
        for k in range(chunk_size):
            main_chain.insert(j, to_insert[insert_idx + k])
        debug(depth, i, f"to_insert={to_insert}", f"main_chain={main_chain}")
                

    arr = main_chain

    debug(depth, "(3) -", arr)

    return arr


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
    debug(depth, "(0)", f"chunks={chunks}")

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

    debug(depth, "(3.1)", f"to_insert={to_insert}", f"main_chain={main_chain}")

    number_inserted = 0

    for i in range(len(to_insert)):
        l = 0
        r = len(main_chain)
        while l < r:
            m = (l + r) // 2
            compare_count += 1
            if to_insert[i] < main_chain[m]:
                r = m
            else:
                l = m + 1
        main_chain.insert(r, to_insert[i])
        
    debug(depth, "(3.2)", f"main_chain={main_chain}")

    return main_chain

def sort(arr):
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

n = 21
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
