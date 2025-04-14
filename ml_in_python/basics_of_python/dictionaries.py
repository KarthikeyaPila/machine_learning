x = {
    "name" : "karthikeya",
    "age" : 18,
    "food" : "biriyani"
}

print("printing food: ", x["food"])


#to know if a item is there or not.

x["company"] = "company_name"
del x["food"]
print("deletion of food")
print("is company there? : ", "company" in x) #checks if the struct var "company" is there in the struct or not.    It is there
print("is food there?: ","food" in x) #checks if the struct var "food" is there in the struct or not.          It is not there
