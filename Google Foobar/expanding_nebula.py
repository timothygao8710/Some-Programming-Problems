def solution(g):
    n, m = len(g), len(g[0])
    # n <= 10
    
    # convert everything to bits
    temp = []
    for j in range(m):
        cur = 0
        for i in range(n):
            if(g[i][j]):
                cur = 2 * cur + 1
            else:
                cur = 2 * cur
                
        temp.append(cur)
        
    g = temp
    
    transitions = {}
    
    # precompute possibilities
    for i in range(1<<(n+1)):
        for j in range(1<<(n+1)):
            res = 0
            # (i | j)
            for k in range(n-1, -1, -1):
                a, b, c, d = (i>>k) & 1, (i>>(k+1)) & 1, (j >> k) & 1, (j >> (k+1)) & 1
                if (
                    
                    (a and not (b or c or d)) or
                    (b and not (a or c or d)) or
                    (c and not (b or a or d)) or
                    (d and not (b or c or a))
                    
                    ):
                        res = res * 2 + 1
                else:
                    res = res * 2
            
            if res not in g:
                continue
            
            # given, result
            res = (i, res)
            if res not in transitions:
                transitions[res] = []
            transitions[res].append(j)
        
    dp = [[-1 for _ in range(1 << (n+1))] for _ in range(m)]
            
    def recur(col, cur):
        if col == m:
            return 1
        
        if(dp[col][cur] != -1):
            return dp[col][cur]
        
        if((cur, g[col]) not in transitions):
            dp[col][cur] = 0
            return 0
        
        res = 0
        for i in transitions[(cur, g[col])]:
            res += recur(col + 1, i)
        dp[col][cur] = res
        return res

    ans = 0
    for i in range(1<<(n+1)):
        ans += recur(0, i)
    return ans
        
        
print(solution([[True, True, False, True, False, True, False, True, True, False], [True, True, False, False, False, False, True, True, True, False], [True, True, False, False, False, False, False, False, False, True], [False, True, False, False, False, False, True, True, False, False]]))