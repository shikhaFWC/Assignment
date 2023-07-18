import numpy as np

# Define the vector
e1  = np.array([1,0,0])
e2  = np.array([0,1,0])
e3  = np.array([0,0,1])

# calculate cross product of the vectors
a = np.cross(e2,e3)
b = np.cross(e1,e3)
c = np.cross(e1,e2)

# calculate dot product of the vectors
d = np.dot(e1,a)
e = np.dot(e2,b)
f = np.dot(e3,c)

# print result
print(d+e+f)
