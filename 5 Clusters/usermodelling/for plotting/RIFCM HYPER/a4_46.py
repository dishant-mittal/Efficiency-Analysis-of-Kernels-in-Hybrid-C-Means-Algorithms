import matplotlib.pyplot as plt
import numpy as np
import csv as csv

csv_file = csv.reader(open('coordinates.csv'))
csv_fi = csv.reader(open('synthetic.csv'))
csv_f = csv.reader(open('cluster_datapoints.csv'))

#file read for cluster_coordinates
header= csv_file.next()

data = []

for row in csv_file:
	data.append(row)

data = np.array(data)


#file read for dataset
head= csv_fi.next()

dt = []

for row in csv_fi:
	dt.append(row)

dt = np.array(dt)

#file read for belongingness

h= csv_f.next()

d = []

for row in csv_f:
	d.append(row)

d = np.array(d)

fig = plt.figure()
ax1 = fig.add_subplot(111)

C1=d[0:3,0].astype(np.int)

x=[]
y=[]


for i in C1:
    x.append(dt[i,4].astype(np.float))
    y.append(dt[i,46].astype(np.float))
    
## left panel
ax1.scatter(x,y,color='blue',s=30,edgecolor='none',alpha=0.6,label='Cluster 1')
ax1.set_aspect(1./ax1.get_data_ratio()) # make axes square


C2=d[0:393,1].astype(np.int)

X1=[]
Y1=[]


for i in C2:
    X1.append(dt[i,4].astype(np.float))
    Y1.append(dt[i,46].astype(np.float))

ax1.scatter(X1,Y1,color='green',s=20,edgecolor='none',alpha=0.6,label='Cluster 2')
ax1.set_aspect(1./ax1.get_data_ratio()) # make axes square

C3=d[0:243,2].astype(np.int)

X2=[]
Y2=[]


for i in C3:
    X2.append(dt[i,4].astype(np.float))
    Y2.append(dt[i,46].astype(np.float))
    
ax1.scatter(X2,Y2,color='black',s=7,edgecolor='none',alpha=0.6,label='Cluster 3')
ax1.set_aspect(1./ax1.get_data_ratio()) # make axes square

C4=d[0:14,3].astype(np.int)

X3=[]
Y3=[]


for i in C4:
    X3.append(dt[i,4].astype(np.float))
    Y3.append(dt[i,46].astype(np.float))
    
ax1.scatter(X3,Y3,color='red',s=15,edgecolor='none',alpha=0.6,label='Cluster 4')
ax1.set_aspect(1./ax1.get_data_ratio())

Centroid1_x=[29.098253]
Centroid1_y=[317.514718]

ax1.scatter(Centroid1_x,Centroid1_y,color='blue',marker='^',s=70,edgecolor='none',alpha=1)
ax1.set_aspect(1./ax1.get_data_ratio())

Centroid2_x=[33.322952]
Centroid2_y=[37.635558]

ax1.scatter(Centroid2_x,Centroid2_y,color='green',marker='^',s=70,edgecolor='none',alpha=1)
ax1.set_aspect(1./ax1.get_data_ratio())

Centroid3_x=[31.165577]
Centroid3_y=[21.478701]

ax1.scatter(Centroid3_x,Centroid3_y,color='black',marker='^',s=70,edgecolor='none',alpha=1)
ax1.set_aspect(1./ax1.get_data_ratio())

Centroid4_x=[29.011933]
Centroid4_y=[128.734198]

ax1.scatter(Centroid4_x,Centroid4_y,color='red',marker='^',s=70,edgecolor='none',alpha=1)
ax1.set_aspect(1./ax1.get_data_ratio())
'''
## the data
N=1000
x = np.random.randn(N)
y = np.random.randn(N)
'''


'''
## right panel
ax2 = fig.add_subplot(122)
props = dict(alpha=0.5, edgecolors='none' )


handles = []
colors = ['blue', 'green', 'magenta', 'cyan']
for color in colors:
    x = np.random.randn(N)
    y = np.random.randn(N)
    s = np.random.randint(50,200)
    handles.append(ax2.scatter(x, y, c=color, s=s, **props))
'''
#ax2.set_ylim([-5,11])
#ax2.set_xlim([-5,11])

#ax2.legend(handles, colors)
#ax2.grid(True)
#ax2.set_aspect(1./ax2.get_data_ratio())
plt.grid(True)
plt.xlabel('Attribute 5',size='17')
plt.ylabel('Attribute 47',size='17')
plt.legend(loc='upper right')
plt.title('RIFCM with Hypertangent Kernel',size='18')
plt.savefig('synthetic RFCM_euclid.png', format='png', dpi=600)
plt.show()
