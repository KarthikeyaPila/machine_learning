import matplotlib.pyplot as plt
import numpy as np

values_input = [12,55,4,32,14]
colors_input = ['r','g','b','c','m']

explode_input = [0, 0, 0.2, 0, 0.0]
lables_input = ['India', 'united states', 'Russia', 'China', 'Europe']

# ploting a pie chart
plt.pie(values_input, colors= colors_input, explode= explode_input, labels= lables_input)
plt.title('fat people')
plt.show()

# plotting a bar graph
plt.bar(range(1,6), values_input, color=colors_input)       #range is the values on X axis.
plt.show()

# plotting a histogram
x = np.random.normal(10, 100, 10000)
plt.hist(x, bins=50)
plt.show()
