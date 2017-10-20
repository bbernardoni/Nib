import matplotlib.collections as col
import matplotlib.pyplot as plt
import struct

inFile = 'cib3.svg'
outFile = 'player.mod'

def addVert(verts, x, y):
    vert = (round(x,1), round(y,1))
    try:
        index = verts.index(vert)
    except ValueError:
        index = len(verts)
        verts.append(vert)
    return index

def readNum(s):
    if (s[0]>='0' and s[0]<='9') or s[0]=='.' or s[0]=='-':
        skip = 0
    else:
        skip = 1
    i = 1
    while (s[i]>='0' and s[i]<='9') or s[i]=='.':
        i += 1
        if i == len(s):
           break
    if i == 1 and skip == 1:
        return (0.0, s)
    return (float(s[skip:i]), s[i:])

with open(inFile) as f:
    content = f.readlines()

first = True
rx = ry = 0.0
verts = []
segs = []
for line in content:
    if line.find('<path') >= 0:
        start = line.find('d="')+3
        end = line.find('"', start)
        pathStr = line[start:end].strip()
        x = y = 0.0
        strip = []
        mode = 'l'
        loop = False
        while len(pathStr) > 0:
            cmd = pathStr[0]
            if cmd == 'm':
                mx, pathStr = readNum(pathStr)
                my, pathStr = readNum(pathStr)
                if first:
                    rx = mx
                    ry = my
                    first = False
                x = round(mx - rx, 5)
                y = round(my - ry, 5)
                sIn = addVert(verts, x, y)
                strip.append(sIn)
                continue
            elif cmd == 'l':
                mode = 'l'
            elif cmd == 'v':
                mode = 'v'
            elif cmd == 'h':
                mode = 'h'
            elif cmd == 'z':
                strip.append(sIn)
                loop = True
                break
            
            lx = ly = 0.0
            if mode == 'l':
                lx, pathStr = readNum(pathStr)
                ly, pathStr = readNum(pathStr)
            elif mode == 'v':
                ly, pathStr = readNum(pathStr)
            elif mode == 'h':
                lx, pathStr = readNum(pathStr)
            x = round(x+lx, 5)
            y = round(y+ly, 5)
            strip.append(addVert(verts, x, y))
        if loop:
            strip.insert(0, strip[-2])
            strip.append(strip[2])
        else:
            strip.insert(0, strip[0])
            strip.append(strip[-1])
        segs.append(strip)

with open(outFile, 'wb') as f:
    f.write(struct.pack('i%sf' % (2*len(verts)), len(verts), *list(sum(verts,()))))
    f.write(struct.pack('i', len(segs)))
    for seg in segs:
        f.write(struct.pack('i%si' % len(seg), len(seg), *seg))

lines = [[verts[i] for i in seg] for seg in segs]
lc = col.LineCollection(lines)
fig, ax = plt.subplots()
ax.add_collection(lc)
mins = list(map(min, zip(*verts)))
maxs = list(map(max, zip(*verts)))
plt.xlim([mins[0],maxs[0]])
plt.ylim([mins[1],maxs[1]])
plt.gca().invert_yaxis()
plt.show()
