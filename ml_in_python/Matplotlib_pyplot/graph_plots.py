import matplotlib.pyplot as plt
import numpy as np

#data to work with
X = np.linspace(-2, 2, 100)
Y = 2*X*X + 3
Z = 2*X + 5

# a scatter plot
plt.scatter(X,Y)
plt.ylabel('Y')
plt.xlabel('X')
plt.title('scatter plot')
plt.show()

# a line plot
plt.plot(X,Y)
plt.ylabel('Y')
plt.xlabel('X')
plt.title('line plot')
plt.show()


# plotting multiple plots on the same graph.
plt.plot(X, Y, label = "polynomial function")
plt.plot(X, Z, label = "linear function")
plt.ylabel('Y')
plt.xlabel('X')
plt.title('multiple plots')
plt.legend()
plt.show()

# you can set the axis as well

axes = plt.axes()
axes.set_xlim([-10, 10])
axes.set_ylim([-4, 15])

plt.plot(X, Y, label = "polynomial function")
plt.plot(X, Z, label = "linear function")
plt.ylabel('Y')
plt.xlabel('X')
plt.title('multiple plots')
plt.legend(loc='lower right') #tells where to put the lable
plt.show()


# subplotting in a single graph.
plt.subplot(2,2,1)  #gives the coordinates to the plot
plt.scatter(X, Y, c='red')

plt.subplot(2,2,2)  #gives the coordinates to the plot
plt.plot(X, Y, c='green')

plt.subplot(2,2,3)  #gives the coordinates to the plot
plt.scatter(X, Z, c='blue')

plt.subplot(2,2,4)  #gives the coordinates to the plot
plt.plot(X, Z, c='yellow')

plt.show()