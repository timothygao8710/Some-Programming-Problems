def solution(dimensions, your_position, trainer_position, distance):
    w, l, a, b, c, d = dimensions[0], dimensions[1], your_position[0], your_position[1], trainer_position[0], trainer_position[1]
    
    def gcd(a, b):
        while b:
            a, b = b, a%b
        return a
        
    ys = []
    xs = []
    
    cur = d
    A, B = 2 * l - 2 * d, 2 * d
    while cur <= distance + l:
        ys.append(cur)
        ys.append(-cur)
        cur += A
        A, B = B, A
    
    cur = c
    A, B = 2 * w - 2 * c, 2 * c
    while cur <= distance + w:
        xs.append(cur)
        xs.append(-cur)
        cur += A
        A, B = B, A
        
    bad_ys = []
    bad_xs = []
    
    cur = b
    A, B = 2 * l - 2 * b, 2 * b
    while cur <= distance + l:
        bad_ys.append(cur)
        bad_ys.append(-cur)
        cur += A
        A, B = B, A
    
    cur = a
    A, B = 2 * w - 2 * a, 2 * a
    while cur <= distance + w:
        bad_xs.append(cur)
        bad_xs.append(-cur)
        cur += A
        A, B = B, A
    
    distance *= distance

    ys.sort(key=lambda x: abs(b - x))
    bad_ys.sort(key=lambda x: abs(b - x))
    
    all = {}
    for i in xs:
        for j in ys:
            dx, dy = i - a, j - b
            cur_dist = dx * dx + dy * dy
            if cur_dist > distance:
                break
            
            cur = (dx // gcd(abs(dx), abs(dy)), dy // gcd(abs(dx), abs(dy)))
            if cur not in all:
                all[cur] = cur_dist
            else:
                all[cur] = min(all[cur], cur_dist)
            
    sub = 0
    for i in bad_xs:
        for j in bad_ys:
            dx, dy = i - a, j - b
            if dx == 0 and dy == 0:
                continue 
            
            cur_dist = dx * dx + dy * dy
            if cur_dist > distance:
                break

            cur = (dx // gcd(abs(dx), abs(dy)), dy // gcd(abs(dx), abs(dy)))
            
            if cur in all and all[cur] > cur_dist:
                sub += 1
                all[cur] = 0
            
    return len(all) - sub

print(solution([3,4], [1,1], [2,2], 500))
# 54243