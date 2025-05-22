import random
import time
import sys
from collections import Counter
import math

sys.setrecursionlimit(42)


class Utils:
    def random_arr(n=None, seed=None, number_range=None, duplicate=True):
        if seed:
            random.seed(seed)
        if not n:
            n = random.randint(1, 100)
        if number_range:
            a, b = number_range
        else:
            a, b = 1, n
        if duplicate:
            arr = [random.randint(a, b) for _ in range(n)]
        else:
            arr = [i for i in range(n)]
            random.shuffle(arr)
        return arr
        
    def is_items_same(arr_1: list, arr_2: list):
        return Counter(arr_1) == Counter(arr_2)

    def is_sorted(arr: list[int]):
        for i in range(len(arr) - 1):
            if arr[i] > arr[i + 1]:
                return False
        return True

    def print_arr(arr: list, end="\n"):
        if len(arr) > 10:
            print(str(arr[:5]).rstrip("]"), "...", str(arr[-5:]).lstrip("["), end="")
        else:
            print(arr, end="")
        print(f" ({len(arr)} items)", end=end)


class ISortStrategy:
    def __init__(self, name=""):
        self.name: str = name

        self.compare_count = 0

    # must return arr
    def sort(arr: list[int]):
        raise NotImplementedError()
    
    def compare(self, a, b):
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
            if not right_pairs[j][1]:
                break
            if self.compare(left_pairs[i][1], right_pairs[j][1]) < 0:
                pairs.append(left_pairs[i])
                i += 1
            else:
                pairs.append(right_pairs[j])
                j += 1
        pairs.extend(left_pairs[i:])
        pairs.extend(right_pairs[j:])
        return pairs

    def _sort(self, pairs: list[int]):
        if len(pairs) == 1:
            return pairs
        left_pairs = self._sort(pairs[:len(pairs) // 2])
        right_pairs = self._sort(pairs[len(pairs) // 2:])
        return self._merge(left_pairs, right_pairs)

    def _make_pairs(self, arr: list[int]):
        pairs = []
        for i in range(0, len(arr), 2):
            if i + 1 < len(arr):
                a, b = arr[i], arr[i + 1]
                if self.compare(a, b) > 0:
                    a, b = b, a
            else:
                a, b = arr[i], None
            pairs.append([a, b])
        return pairs
    
    def _init_main_chain(self, pairs):
        main_chain = []
        for a, b in pairs:
            if b != None:
                main_chain.append(b)
        main_chain.insert(0, pairs[0][0])
        return main_chain

    def sort(self, arr: list[int]):
        self.compare_count = 0

        pairs = self._make_pairs(arr)
        pairs = self._sort(pairs)

        main_chain = self._init_main_chain(pairs)

        # print(pairs)
        # print(main_chain)

        for i in range(1, len(pairs)):
            insert_num = pairs[i][0]
            insert_idx = 2 * i
            for j in range(2 * i):
                if self.compare(insert_num, main_chain[j]) < 0:
                    insert_idx = j
                    break
            # print("num", insert_num, "to index", insert_idx)
            main_chain.insert(insert_idx, insert_num)
            # print(main_chain)

            assert Utils.is_sorted(main_chain), "array is broken"

        return main_chain
        

def sort_and_report(arr: list[int], sort_strategy: ISortStrategy):
    sorted_arr = arr.copy()
    time_start = time.perf_counter()
    sorted_arr = sort_strategy.sort(sorted_arr)
    time_end = time.perf_counter()
    time_taken = time_end - time_start

    n = len(arr)
    theoretical_bound = sum(math.ceil(math.log2(3/4 * k)) for k in range(1, n + 1))

    unchanged = Utils.is_items_same(arr, sorted_arr)
    sorted_ = Utils.is_sorted(sorted_arr)
    rows = (
        ("Name", sort_strategy.name),
        ("Unchanged", unchanged),
        ("Sorted", sorted_),
        ("Compare", str(sort_strategy.compare_count) + " times"),
        ("Time", str(round(time_taken * 1000000)) + "us")
    )
    first_col_width = max(len(row[0]) for row in rows)

    Utils.print_arr(sorted_arr)
    for a, b in rows:
        print(f"{a.rjust(first_col_width)} : {b}")

    assert unchanged, "array got changed"
    assert sorted_, "array is not sorted"
    # assert sort_strategy.compare_count <= theoretical_bound, f"took too many steps (> {theoretical_bound} times)"


if __name__ == "__main__":
    arrays = [
        # [5, 0, 8, 6, 4, 1, 7, 2, 9, 3],
        # [0, 8, 6, 2, 11, 7, 9, 13, 14, 3, 4, 12, 1, 5, 10],
        # [9, 4, 1, 2, 10, 11, 13, 8, 6, 5, 7, 14, 12, 0, 3],
        # [14, 6, 3, 8, 2, 1, 13, 5, 11, 12, 7, 10, 0, 9, 4],

        # Utils.random_arr(n=42, seed=42, duplicate=True),

        Utils.random_arr(n=21),
        # Utils.random_arr(n=2100),
    ]
    strategies = (
        # SelectionSortStrategy(),
        # LinearInsertionSortStrategy(),
        # BinaryInsertionSortStrategy(),
        # MergeSortStrategy(),
        MergeInsertionSortStrategy(),
    )
    for strategy in strategies:
        for arr in arrays:
            Utils.print_arr(arr, end="\n\n")
            sort_and_report(arr, strategy)
            print()
