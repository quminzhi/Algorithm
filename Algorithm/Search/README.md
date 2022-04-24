# Search

## Depth First Search

### N Queens

> The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
>
> Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.
>
> Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.

One trick in N-Queens is the representation of diagonal line and anti-diagonal line. One fact is that diagonal line is indexed by y-distance of a x-y plane.

```text
    0  1  2  3  4
 0  a
 1   b c 
 2      d e
 3         f g
 4            h i
```

For an anti-diagonal line `y = -x + b`, we got `b = x + y`. So, `Grid[i][j]` is in `AntiDiag[i + j]`. For a diagonal line `y = x + b`, we got `b = -x + y`, but `b` should be non-negative. `b = -x + y + max(N, M)` for any rectangular (`b = -x + y + N or M` for a square), where `N` represents column, and `M` row.

We use `col[]`, `row[]`, `diag[]`, `anti_diag[]` to record if there is a queen on that line.

```c++

```

