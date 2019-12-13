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
        crossEnd = Point(min(self.maxx, int2.maxx), min(self.maxy, int2.maxy))
        if crossStart.x == crossEnd.x:
            return min([Point(crossStart.x, i).manhattan for i in range(crossStart.y, crossEnd.y+1) if Point(crossStart.x, i).manhattan > 0] or [1e9])
        else:
            return min([Point(i, crossStart.y).manhattan for i in range(crossStart.x, crossEnd.x+1) if Point(i, crossStart.y).manhattan > 0] or [1e9])


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
for i in range(len(int1[1:])):
    for j in range(len(int2[1:])):
        if int1[i].is_cross(int2[j]):
            min_dist = min(min_dist, int1[i].get_cross_dist(int2[j]))

print(min_dist)