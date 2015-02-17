import pygal
from pygal.style import SolarizedStyle
import webbrowser

a=[]
X=[]
Y=[]
buff=-1
count=-1

# retrieve data from text file created by data_generation program

with open("cache_test.txt") as f:
    for line in f:
        a.append(int(line))

a.sort()

# counts number of occurences

for i in range(len(a)):
    if a[i]==buff:
        X[count]+=1
    else:
        X.append(1)
        Y.append(a[i])
        count+=1
        buff=a[i]

# generate chart (open with browse)

g = pygal.Bar(style=SolarizedStyle,x_label_rotation=45)
g.title = 'Time of access to cache (ms)'
g.x_labels = map(str, Y)
g.add("Times",X)
g.render_to_file("psc.html")
webbrowser.open("psc.html")

