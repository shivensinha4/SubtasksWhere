/**
 * Author: Nachia
 * Date: 2016-09-06
 * License: CC0
 * Source: SmolBrain
 * Description: Determine A Non-Increasing Integer Sequence of Length n with a[k]<=n/k in O(sqrt(n)) Steps
 * Time: $O(sqrt(n))$
 * Status: somewhat tested
 */

def f(k) :
    # find a_k

def search(l, r) :
    if l > r
        return
    if A[l-1] == A[r+1] :
        for x in range(l, r+1) :
            A[x] = A[l-1]
        return
    m = (l + r) // 2
    A[m] = f(m)
    search(l, m-1)
    search(m+1, r)