import math

def ft_insert(arr: list, left, right, num):
    LIMIT = 10

    print(arr)
    print("-" * 40)

    insert_idx = None

    l = left
    r = right
    while l < r:
        assert LIMIT > 0, "probably infinite loop"; LIMIT -= 1

        print(arr[l:r])
        print(f"l={l}, r={r}")
        m = (l + r) // 2
        print(f"m={m}")
        if num < arr[m]:
            print("num < arr[m]")
            r = m
            print(f"r={r}, insert_idx={insert_idx}")
        else:
            print("num >= arr[m]")
            l = m + 1
            print(f"l={l}")
        print("-" * 40)

    insert_idx = r
    assert insert_idx != None, "insert_idx not found"
    arr.insert(insert_idx, num)

    print(arr)


def _merge(left, right):
    global compare_cnt

    arr = []
    i = 0
    j = 0
    while i < len(left) and j < len(right):
        compare_cnt += 1
        if left[i] < right[j]:
            arr.append(left[i])
            i += 1
        else:
            arr.append(right[j])
            j += 1

    arr.extend(left[i:])
    arr.extend(right[j:])
    return arr

compare_cnt = 0
def merge_sort(arr, depth=0):
    global compare_cnt

    print("-->" * depth, "merge_sort", arr)
    if len(arr) == 1:
        print("..." * depth, "return", arr, f"compare_cnt={compare_cnt}")
        return arr
    left = merge_sort(arr[:len(arr) // 2], depth + 1)
    right = merge_sort(arr[len(arr) // 2:], depth + 1)
    print("-->" * depth, "_merge", left, right)
    arr = _merge(left, right)
    print("..." * depth, "return", arr, f"compare_cnt={compare_cnt}")
    return arr

def B(n):
    return n * math.ceil(math.log2(n)) - 2**math.ceil(math.log2(n)) + 1

def G(m):
    a, b = 1, 1
    k = 1
    while not (a <= m <= b):
        a, b = b, b + 2*a
        k += 1
    w = math.floor(2**(k+1) / 3)
    return k * m - w

# arr = [1, 3, 5, 7, 15, 20]
# arr = [1, 3, 5]
# arr = [21, 9, 8, 5, 18, 19, 2, 7, 17, 20]
# print(arr)
# arr = merge_sort(arr)
# print(arr)
# for n in range(1, 101):
    # print(f"B({n}) = {B(n)}")

n = 3001
a = n // 2
b = n - a
print("for merge", B(a))
print("for insert", G(b))
