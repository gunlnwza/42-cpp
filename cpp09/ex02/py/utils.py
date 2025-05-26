import random
from collections import Counter

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

