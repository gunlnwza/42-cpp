import random
import time


class Utils:
    def random_arr(N=None, seed=None, number_range=(1, 100)):
        if seed:
            random.seed(seed)
        if not N:
            N = random.randint(1, 100)
        a, b = number_range
        arr = [random.randint(a, b) for _ in range(N)]
        return arr
    
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

    def sort(self, arr: list[int]):
        return arr
    
class MergeInsertionSortStrategy(ISortStrategy):
    def __init__(self):
        super().__init__("merge_insertion")
    
    def sort(self, arr: list[int]):
        return arr


def sort_and_report(arr: list[int], sort_strategy: ISortStrategy):
    arr = arr.copy()
    
    time_start = time.perf_counter()
    arr = sort_strategy.sort(arr)
    time_end = time.perf_counter()
    time_taken = time_end - time_start
    
    rows = [
        ("Name", sort_strategy.name),
        ("Sorted", Utils.is_sorted(arr)),
        ("Compare", str(sort_strategy.compare_count) + " times"),
        ("Time", str(round(time_taken * 1000000)) + "us")
    ]
    first_col_width = max(len(row[0]) for row in rows)
    Utils.print_arr(arr)
    for a, b in rows:
        print(f"{a.rjust(first_col_width)} : {b}")


if __name__ == "__main__":
    arr = Utils.random_arr(N=100, seed=None)
    Utils.print_arr(arr, end="\n\n")

    strategies = (
        SelectionSortStrategy(),
        LinearInsertionSortStrategy(),
        BinaryInsertionSortStrategy(),
        MergeSortStrategy(),
        MergeInsertionSortStrategy()
    )
    for strategy in strategies:
        sort_and_report(arr, strategy)
        print()
