import pandas as pd

df = pd.read_csv("file_name.csv")   #read the file.

df.head()    #prints the first 5 rows
df.tail(6)    #prints the last rows (6)
df.sample(n=5)      #prints any random rows (here 5)

nrows, ncols = df.shape     #tells the number of rows and cols

df.describe()       #returns the statistics of just the numerical cols

#accessing specific cols
some_cols = df['col_name1', 'col_name_2', 'col_name_3']     #would get you the datas of the cols
some_cols.head()        #would print out the some_cols values 

df[0:3]     #would get you those many rows 
df[0:3]['col_name1', 'col_name_2', 'col_name_3']        #would give you those many rows of those cols

df.shape        #prints the dimentions of the data

