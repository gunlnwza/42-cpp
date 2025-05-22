import random
import time


def is_sorted(arr: list[int]):
    for i in range(len(arr) - 1):
        if arr[i] > arr[i + 1]:
            return False
    return True


def print_arr(arr: list):
    print("arr of length ", len(arr), ": ", sep="", end="")
    if len(arr) > 10:
        print(str(arr[:5]).rstrip("]"), "...", str(arr[-5:]).lstrip("["))
    else:
        print(arr)


def selection_sort(arr: list[int]):
    print("selection_sort")
    time_start = time.perf_counter()

    compare_cnt = 0
    swap_cnt = 0

    for i in range(len(arr) - 1):
        
        min_idx = i
        for j in range(i + 1, len(arr)):
            compare_cnt += 1
            if arr[j] < arr[min_idx]:
                min_idx = j
        if min_idx != i:
            arr[i], arr[min_idx] = arr[min_idx], arr[i]
            swap_cnt += 1
            # print(swap_cnt, arr)

    time_stop = time.perf_counter()
    time_taken = time_stop - time_start

    print_arr(arr)
    print("is_sorted:", is_sorted(arr))
    print(f"time_taken: {time_taken * 1000:.0f} ms")
    print("compare_cnt:", compare_cnt)
    print("swap_cnt:", swap_cnt)
    print()


def linear_insertion_sort(arr: list[int]):
    print("linear_insertion_sort")
    time_start = time.perf_counter()

    compare_cnt = 0
    insert_cnt = 0

    for i in range(1, len(arr)):
        for j in range(i):
            compare_cnt += 1
            if arr[i] < arr[j]:
                item = arr.pop(i)
                arr.insert(j, item)
                insert_cnt += 1
                # print(insert_cnt, arr)
                break
    
    time_stop = time.perf_counter()
    time_taken = time_stop - time_start
    
    print_arr(arr)
    print("is_sorted:", is_sorted(arr))
    print(f"time_taken: {time_taken * 1000:.0f} ms")
    print("compare_cnt:", compare_cnt)
    print("insert_cnt:", insert_cnt)
    print()


def binary_insertion_sort(arr: list[int]):
    print("binary_insertion_sort")
    time_start = time.perf_counter()

    compare_cnt = 0
    insert_cnt = 0

    for i in range(1, len(arr)):
        l = 0
        r = i
        insert_idx = -1
        while l < r:
            m = (l + r) // 2
            compare_cnt += 1
            if arr[m] > arr[i]:
                r = m
                insert_idx = m
            else:
                l = m + 1

        if insert_idx > -1:
            item = arr.pop(i)
            arr.insert(insert_idx, item)
            insert_cnt += 1
            # print(insert_cnt, arr)

    time_stop = time.perf_counter()
    time_taken = time_stop - time_start

    print_arr(arr)
    print("is_sorted:", is_sorted(arr))
    print(f"time_taken: {time_taken * 1000:.0f} ms")
    print("compare_cnt:", compare_cnt)
    print("insert_cnt:", insert_cnt)
    print()



compare_cnt = 0
insert_cnt = 0
def merge_sort(arr: list[int]):
    def rec(arr: list[int]):
        if len(arr) <= 1:
            return arr
        
        mid = len(arr) // 2
        left = rec(arr[:mid])
        right = rec(arr[mid:])

        return merge(left, right)

    def merge(left: list[int], right: list[int]):
        global compare_cnt, insert_cnt

        result = []
        i = j = 0

        while i < len(left) and j < len(right):
            compare_cnt += 1
            if left[i] <= right[j]:
                insert_cnt += 1
                result.append(left[i])
                i += 1
            else:
                insert_cnt += 1
                result.append(right[j])
                j += 1
        
        insert_cnt += len(left[i:])
        result.extend(left[i:])
        insert_cnt += len(right[j:])
        result.extend(right[j:])
        return result

    print("merge_sort")
    time_start = time.perf_counter()

    arr = rec(arr)
    print_arr(arr)

    time_end = time.perf_counter()
    time_taken = time_end - time_start

    print("is_sorted:", is_sorted(arr))
    print(f"time_taken: {time_taken * 1000:.0f} ms")
    print("compare_cnt:", compare_cnt)
    print("insert_cnt:", insert_cnt)

class Result:
    def __init__(self):
        pass

    def put(self):
        pass

class ISortStrategy:
    def __init__(self):
        pass

    def sort(arr: list[int], result: Result):
        pass



class Sorter:
    def __init__(self):
        self.time_start = None
        self.time_end = None
        self.result: Result = None

    def sort(self, arr: list[int], func: ISortStrategy):
        self.time_start = time.perf_counter()
        func.sort(arr.copy(), self.result)
        self.time_end = time.perf_counter()
        self.result.put()


if __name__ == "__main__":
    # random.seed(42)
    
    # N = random.randint(10, 100)
    # N = 10000
    # arr = [i for i in range(N)]
    # random.shuffle(arr)
    arr = [5,2,3,4,1,7,6]

    print_arr(arr)
    print()

    selection_sort(arr.copy())
    linear_insertion_sort(arr.copy())
    binary_insertion_sort(arr.copy())
    merge_sort(arr.copy())
    