import random
import time
import sys
from collections import Counter
import math

from utils import Utils

sys.setrecursionlimit(42)

RED = "\033[31m"
GREEN = "\033[32m"
RESET = "\033[0m"

class ISortStrategy:
    def __init__(self, name=""):
        self.name: str = name

        self.compare_count = 0

    # must return arr
    def sort(arr: list[int]):
        raise NotImplementedError()
    
    def compare(self, a, b):
        # print(f"compare {a} vs {b}")
        self.compare_count += 1
        return a - b

class SelectionSortStrategy(ISortStrategy):
    def __init__(self):
        super().__init__("selection")
    
    def sort(self, arr: list[int]):
        for i in range(len(arr) - 1):
            min_idx = i
            for j in range(i + 1, len(arr)):
                if self.compare(arr[j], arr[min_idx]) < 0:
                    min_idx = j
            if min_idx != i:
                arr[i], arr[min_idx] = arr[min_idx], arr[i]
        return arr

class LinearInsertionSortStrategy(ISortStrategy):
    def __init__(self):
        super().__init__("linear_insertion")

    def sort(self, arr: list[int]):
        for i in range(1, len(arr)):
            for j in range(i):
                if self.compare(arr[i], arr[j]) < 0:
                    item = arr.pop(i)
                    arr.insert(j, item)
                    break
        return arr

class BinaryInsertionSortStrategy(ISortStrategy):
    def __init__(self):
        super().__init__("binary_insertion")

    def sort(self, arr: list[int]):
        for i in range(1, len(arr)):
            l = 0
            r = i
            insert_idx = -1
            while l < r:
                m = (l + r) // 2
                if self.compare(arr[m], arr[i]) > 0:
                    r = m
                    insert_idx = m
                else:
                    l = m + 1

            if insert_idx > -1:
                item = arr.pop(i)
                arr.insert(insert_idx, item)
        return arr

class MergeSortStrategy(ISortStrategy):
    def __init__(self):
        super().__init__("merge")

    def _merge(self, left, right):
        arr = []
        i = 0
        j = 0
        while i < len(left) and j < len(right):
            if self.compare(left[i], right[j]) < 0:
                arr.append(left[i])
                i += 1
            else:
                arr.append(right[j])
                j += 1
        arr.extend(left[i:])
        arr.extend(right[j:])
        return arr
    
    def _sort(self, arr: list[int]):
        if len(arr) == 1:
            return arr
        left = self._sort(arr[:len(arr) // 2])
        right = self._sort(arr[len(arr) // 2:])
        return self._merge(left, right)

    def sort(self, arr: list[int]):
        return self._sort(arr)
    
class MergeInsertionSortStrategy(ISortStrategy):
    def __init__(self):
        super().__init__("merge_insertion")
    
    def _merge(self, left_pairs, right_pairs):
        
        pairs = []
        i = 0
        j = 0
        while i < len(left_pairs) and j < len(right_pairs):
            if self.compare(left_pairs[i][1], right_pairs[j][1]) < 0:
                pairs.append(left_pairs[i])
                i += 1
            else:
                pairs.append(right_pairs[j])
                j += 1
        pairs.extend(left_pairs[i:])
        pairs.extend(right_pairs[j:])
        return pairs

    def _merge_sort(self, pairs: list[int]):
        if len(pairs) <= 1:
            return pairs
        left_pairs = self._merge_sort(pairs[:len(pairs) // 2])
        right_pairs = self._merge_sort(pairs[len(pairs) // 2:])
        arr = self._merge(left_pairs, right_pairs)
        # print(arr, f"self.compare_count = {self.compare_count}")
        return arr

    def _make_pairs(self, arr: list[int]):
        pairs = []
        leftover = None
        for i in range(0, len(arr), 2):
            if i + 1 < len(arr):
                a, b = arr[i], arr[i + 1]
                if self.compare(a, b) > 0:
                    a, b = b, a
                pairs.append([a, b])
            else:
                leftover = arr[i]
        return pairs, leftover
    
    def _insert(self, main_chain: list[int], left: int, right: int, num: int):
        # print("main_chain", main_chain)
        # print("left", left, "right", right)
        # print("num", num)
        
        l = left
        r = right
        compare_cnt = 0
        while l < r:
            m = (l + r) // 2
            compare_cnt += 1
            if self.compare(num, main_chain[m]) < 0:
                r = m
            else:
                l = m + 1
        
        # max_compare = math.ceil(math.log2(right - left + 1))
        # print(f"{num} took {compare_cnt} compares (max is {max_compare})")
        main_chain.insert(r, num)

        # print("main_chain", main_chain)
        # print("-"*40)

    def jacobsthal_decreasing(self):
        a, b = 0, 1
        while True:
            for i in range(b, a, -1):
                yield i
            a, b = b, b + 2 * a

    def sort(self, arr: list[int]):
        self.compare_count = 0

        cnt = []

        # print("arr", arr)
        pairs, leftover = self._make_pairs(arr)
        # print("pairs", pairs)
        print(f"make_pairs self.compare_count = {self.compare_count}")
        # print(pairs, leftover)

        cnt.append(self.compare_count)

        pairs = self._merge_sort(pairs)
        # print("pairs", pairs)
        print(f"merge_sort self.compare_count = {self.compare_count}")

        cnt.append(self.compare_count)

        to_insert = []
        main_chain = []
        for a, b in pairs:
            to_insert.append(a)
            if b != None:
                main_chain.append(b)
        if leftover != None:
            to_insert.append(leftover)

        # print("arr", arr)
        # print("pairs", pairs)
        # print("to_insert", to_insert)
        # print("main_chain", main_chain)
        # print("-"*40)

        number_inserted = 0
        for i in self.jacobsthal_decreasing():
            i -= 1
            if number_inserted >= len(to_insert):
                break
            if i >= len(to_insert):
                continue 
            num = to_insert[i]
            right = number_inserted + i
            self._insert(main_chain, 0, right, num)
            number_inserted += 1
            assert Utils.is_sorted(main_chain), "binary search messed up"

        print(f"binary insert self.compare_count = {self.compare_count}")
        print("sort finish\n")
        cnt.append(self.compare_count)

        diff = [cnt[0], cnt[1] - cnt[0], cnt[2] - cnt[1]]
        print(diff)

        return main_chain
        

def B(n):
    return n * math.ceil(math.log2(n)) - 2**math.ceil(math.log2(n)) + 1

def info_theoretic_lower_bound(n):
    return n * math.log2(n) - n / math.log(2) + (1/2) * math.log2(n)

def F(n):
    return sum(math.ceil(math.log2(3/4 * k)) for k in range(1, n + 1))

def G(m):
    a, b = 1, 1
    k = 1
    while not (a <= m <= b):
        a, b = b, b + 2*a
        k += 1
    w = math.floor(2**(k+1) / 3)
    return k * m - w

def sort_and_report(arr: list[int], sort_strategy: ISortStrategy):
    Utils.print_arr(arr, end="\n\n")

    sorted_arr = arr.copy()
    time_start = time.perf_counter()
    sorted_arr = sort_strategy.sort(sorted_arr)
    time_end = time.perf_counter()
    time_taken = time_end - time_start

    n = len(arr)
    theoretical_bound = F(n)
    # print("B(n) =", B(n))
    # print("info_theoretic_lower_bound(n) =", info_theoretic_lower_bound(n))
    # print("F(n) =", F(n))

    unchanged = Utils.is_items_same(arr, sorted_arr)
    sorted_ = Utils.is_sorted(sorted_arr)
    rows = (
        ("Name", sort_strategy.name),
        ("Unchanged", unchanged),
        ("Sorted", sorted_),
        ("Compare", (GREEN if sort_strategy.compare_count <= theoretical_bound else RED) + str(sort_strategy.compare_count) + f" times (max is {theoretical_bound})"),
        ("Time", str(round(time_taken * 1000000)) + "us")
    )
    first_col_width = max(len(row[0]) for row in rows)

    Utils.print_arr(sorted_arr)
    for a, b in rows:
        print(f"{a.rjust(first_col_width)} : {b}{RESET}")

    assert unchanged, "array got changed"
    assert sorted_, "array is not sorted"
    # assert sort_strategy.compare_count <= theoretical_bound, f"took too many steps (> {theoretical_bound} times)"

    print("-" * 40)

if __name__ == "__main__":
    # random.seed(42)

    # sort_and_report([1], MergeInsertionSortStrategy())

    for n in range(1, 4001, 1000):
        arr = Utils.random_arr(n)
        sort_and_report(arr, MergeInsertionSortStrategy())
