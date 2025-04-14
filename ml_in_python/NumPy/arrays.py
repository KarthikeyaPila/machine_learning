import numpy as np

x = np.array([1,2,3, 4], dtype='float32')

print(x)
print("shape: ", x.shape)
print(x[0])

y = np.array([[1,2,3,4],[5,6,7,8]], dtype='float32')  #both the elements of the array should be of the same size (len(y[0])==leny[1])
print(y)
print("shape: ", y.shape)
print(y[0][1])


# the following creates equal spaced array. give the start and end and no.of elements.
z = np.linspace(-10, 0, 10)
print(z.shape)
print(z)

# the following would create a random number generated array.
a = np.random.normal(10.0, 50.0, 100)
print(a.shape)
print(a[:20])

# initializes the array with zeros
shape = (3,3)
b = np.zeros(shape, dtype='int32')
print(b.shape)
print(b)

# reshaping (changing the dimentions) of numpy arrays: 
c = np.array([[1,2], [3,4]], dtype='float32')
c_1D = c.ravel()
print(c_1D.shape)
print(c_1D)

# or you could also do it like this; 
d = np.array([[1,2], [3,4], [5,6], [7,8]], dtype='float32')
d_1D = d.reshape(8,)       #enter the shape inside of the reshape to reshape it.
print(d_1D.shape)
print(d_1D)


e_1 = np.array([2,3], dtype='int32')
e_2 = np.array([4,5], dtype='int32')
e = e_1 + e_2
print(e)

f = np.array([1,2,3,4,5], dtype='int32')
f_sqrt = np.sqrt(f)
print(f_sqrt)

g = np.array([1,2,3,4,5,6,7,8,9], dtype='int32')
print(g)
print("sum: ", g.sum())
print("min: ", g.min())
print("max: ", g.max())
print("mean: ", g.mean())