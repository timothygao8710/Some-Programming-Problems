def solution(times, times_limit):
    # Floyd Warshall
    
    n = len(times)
    for k in range(n):
        for i in range(n):
            for j in range(n):
                times[i][j] = min(times[i][j], times[i][k] + times[k][j])
                
    for i in range(n):
        if times[i][i] < 0:
            return [i for i in range(n-2)]
    
    # No negative cycles -> we never want to revisit a node    
    # Bitset DP
    dp = [[1e9 for _ in range(1 << n)] for _ in range(n)]
    dp[0][1] = 0
    for i in range(2, 1 << n):
        for j in range(n):
            # we're on j
            if not ((i >> j) & 1):
                continue
            
            rem = i ^ (1 << j)
            for k in range(n):
                # came from k
                if not ((rem >> k) & 1):
                    continue
                
                dp[j][i] = min(dp[j][i], dp[k][rem] + times[k][j])
    
    # Take the best
    best = []
    for i in range(1 << n):
        if dp[n-1][i] > times_limit:
            continue
        
        cur = []
        for k in range(n):
            if ((i >> k) & 1):
                cur.append(k-1)
        
        if len(cur) > len(best) or cur < best:
            best = cur
            
    best.remove(-1)
    best.remove(n-2)
    
    return best

print(solution([[0, 2, 2, 2, -1], [9, 0, 2, 2, -1], [9, 3, 0, 2, -1], [9, 3, 2, 0, -1], [9, 3, 2, 2, 0]], 1))
print(solution([[0, 1, 1, 1, 1], [1, 0, 1, 1, 1], [1, 1, 0, 1, 1], [1, 1, 1, 0, 1], [1, 1, 1, 1, 0]], 3))