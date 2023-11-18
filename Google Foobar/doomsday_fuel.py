# import numpy as np

def solution(m):
    def gcd(a, b):
        while b:
            a, b = b, a % b
        return a
    
    def simplify(X):
        if X[0] == 0:
            return [0, 1]
        return [X[0] / gcd(X[0], X[1]), X[1] / gcd(X[0], X[1])]
    
    n = len(m)    
    is_leaf = []
    for i in range(n):
        S = sum(m[i])
        is_leaf.append(S == 0)
        if is_leaf[i]:
            m[i][i] = 1
            S += 1
            
        for j in range(len(m)):
            m[i][j] = [m[i][j], S]
            
        if not is_leaf[i]:
            m[i][i][0] -= S
    
    def gaussian_elimination(A, u):
        M = [i[:] for i in A]

        for i in range(n):
            if i == u:
                M[i] = [[1, 1]] + M[i]
            else:
                M[i] = [[0, 1]] + M[i]

        M = [i[::-1] for i in M[::-1]]
        # for i in M:
        #     print(i)
        # print(" ")

        for i in range(n):
            # swap until non-zero
            if M[i][i] == 0:
                for j in range(i+1, n):
                    if M[j][i] != 0:
                        M[i], M[j] = M[j], M[i]
                        break
            
            if(M[i][i][0] == 0):
                # edge case: self loop
                continue

            # Make the elements in the current column and below the current row 0
            for j in range(i+1, n):
                ratio = simplify([M[j][i][0] * M[i][i][1], M[j][i][1] * M[i][i][0]])
                # print(M[j][i][0], M[i][i][1], ratio)
                for k in range(n+1):
                    cur = simplify([ratio[0] * M[i][k][0], ratio[1] * M[i][k][1]])
                    M[j][k] = [M[j][k][0] * cur[1] - M[j][k][1] * cur[0], M[j][k][1] * cur[1]]
                    M[j][k] = simplify(M[j][k])
            # print(i, "Result: ")
            # for i in M:
            #     print(i)
            # print(" ")
        
        # print(M[n-1])
        return simplify([M[n-1][n][0] * M[n-1][n-1][1], M[n-1][n][1] * M[n-1][n-1][0]])
    
    res = []
    tot_lcm = 0
    for i in range(n):
        if (is_leaf[i]):
            cur = gaussian_elimination(m, i)
            res.append(cur)
            if cur[0] == 0:
                continue
            
            if tot_lcm == 0:
                tot_lcm = cur[1]
            else:
                tot_lcm = tot_lcm * cur[1] / gcd(tot_lcm, cur[1])
            
    
    for i in range(len(res)):
        res[i] = res[i][0] * tot_lcm / res[i][1]
    res.append(tot_lcm)
    
    return res

        
A = [[0, 1, 0, 0, 0, 1], [4, 0, 0, 3, 2, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0]]
print(solution(A))