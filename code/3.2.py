import sys

class Point(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
    @property
    def manhattan(self):
        return abs(self.x) + abs(self.y)
    
class Interval(object):    
    def __init__(self, p1, p2):
        self.p1 = p1
        self.p2 = p2
        self.minx = p1.x if p1.x < p2.x else p2.x 
        self.miny = p1.y if p1.y < p2.y else p2.y
        self.maxx = p1.x if p1.x > p2.x else p2.x 
        self.maxy = p1.y if p1.y > p2.y else p2.y
    
    @property
    def length(self):
        return abs(self.maxy-self.miny) + abs(self.maxx-self.minx)

    def is_cross(self, int2):
        return (
            self.minx <= int2.minx <= self.maxx and
            int2.miny <= self.miny <= int2.maxy
        ) or (
            int2.minx <= self.minx <= int2.maxx and
            self.miny <= int2.miny <= self.maxy
        )
 
    def get_cross_dist(self, int2):
        crossStart = Point(max(self.minx, int2.minx), max(self.miny, int2.miny))
        return (
            max(abs(crossStart.x - self.p1.x), abs(crossStart.y - self.p1.y)) +
            max(abs(crossStart.x - int2.p1.x), abs(crossStart.y - int2.p1.y))
        )

def getIntervalFromPointToDirection(p1, d2):
    direction, val = d2[0], int(d2[1:])
    if direction == 'D': p2 = Point(p1.x, p1.y - val)
    elif direction == 'U': p2 = Point(p1.x, p1.y + val)
    elif direction == 'L': p2 = Point(p1.x - val, p1.y)
    else: p2 = Point(p1.x + val, p1.y)
    return Interval(p1, p2)

l1 = sys.stdin.readline().split(',')
l2 = sys.stdin.readline().split(',')
int1 = [getIntervalFromPointToDirection(Point(0, 0), 'U0')]
int2 = [getIntervalFromPointToDirection(Point(0, 0), 'U0')]
 
for i in l1:
    int1.append(getIntervalFromPointToDirection(int1[-1].p2, i))
 
for i in l2:
    int2.append(getIntervalFromPointToDirection(int2[-1].p2, i))

min_dist = 2e9
len1 = 0
for i in range(1, len(int1)):
    len2 = 0
    for j in range(1, len(int2)):
        if int1[i].is_cross(int2[j]):
            s = len1 + len2 + int1[i].get_cross_dist(int2[j])
            if s > 0:
                min_dist = min(min_dist, s)
        len2 += int2[j].length
    len1 += int1[i].length
print(min_dist)