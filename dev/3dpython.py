import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
#from mpl_toolkits.mplot3d import axes3d

data = np.loadtxt("exampledata4.txt")

fig = plt.figure(figsize=(8,8))
ax = Axes3D(fig)

#DQ = 1/data[:,3]
#DQ[DQ<1]=0
#ax.scatter(data[:,0], data[:,1], data[:,2],s=DQ)
#ax.set_xlim(0,1000)
#ax.set_ylim(130,135)
#ax.set_xlim(130,135)


DQ = 1/data[:,3]
DQ[DQ<1]=0
size = np.ones(len(DQ))*50
size[DQ<6]=0
#ax.scatter3D(data[:,0]*4, data[:,1]*4, data[:,2],s=DQ,marker='s',c=DQ, cmap='Reds')
ax.scatter3D(data[:,0]*4, data[:,1]*4, data[:,2],s=size,c=DQ, cmap='viridis',marker='s',alpha=0.7)

ax.set_zlim(299,311)

#ax.view_init(0, 90)
# rotate the axes and update
for i in range(0, 360, 45):
    ax.view_init(None, i)
    plt.show()
#plt.show()
