#for loop on a string
s = ["a", "b", "c"]
for i in s: 
    print(i, " ", end="")
print("outside the loop")

for i in s:
    x = i + "-"
    print(x)
print("\noutside the loop")

# for loop with start and end value of increment

for i in range(0,5,1): #goes uptill < 5
    print(i, " ", end="")
print("\noutside the loop")

for i in range(0,10,2):  #goes uptil < 10
    print(i, " ", end="")
print("\noutside the loop")


# while loop: 
print("while loop")
i=0
while i < 10:
    print(i," ", end='')
    i=i+1
print("\noutside the while loop")