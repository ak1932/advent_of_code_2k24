infile = '2.txt'

D = open(infile).read().strip()
lines = D.split('\n')

def is_good(xs):
    inc_or_dec = (xs==sorted(xs) or xs==sorted(xs,reverse=True))

    if(not inc_or_dec):
        return False
    ok = True
    for i in range(len(xs)-1):
        diff = abs(xs[i]-xs[i+1])
        if not 1<=diff<=3:
            ok = False

    return ok


p1 = p2 = 0

for line in lines:
    xs1 = list(map(int, line.split()))
    if is_good(xs1):
        p1 += 1

    good = False
    for j in range(len(xs1)):
        xs = xs1[:j] + xs1[j+1:]
        if is_good(xs):
            good = True
            break
    if good:
        p2 += 1

print(p1)
print(p2)
