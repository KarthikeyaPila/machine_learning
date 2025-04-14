record_1 = ("karthikeya", 123456, "vizag")
record_2 = ("sahasra", 654321, "mumbai")
record_3 = ("phanni", 6969696, "usa")
print(record_1[0])
print(record_1[1])
print(record_1[2])

record_of_records = (record_1, record_2, record_3)
print(record_of_records[2])
print(record_of_records[2][0])
#they are immutable: do not change the size.