import csv
import matplotlib.pyplot as plt

datString = ""
with open("data.csv") as f:
    reader = csv.reader(f)
    for row in reader:
        datString +=" ".join(row)

datString2 = ""
with open("data2.csv") as f:
    reader = csv.reader(f)
    for row in reader:
        datString2 +=" ".join(row)

arr = datString.split(" ")
arr = [val for val in arr if val != ""]

arr2 = datString2.split(" ")
arr2 = [val for val in arr2 if val != ""]


y = arr[:10]
x1 = arr[10:20]
x2 = arr[20:30]
x3 = arr2[:10]
x4 = arr[10:20]

# y =np.array(y)
# x1 = np.array(x1)
# x2 = np.array(x2)


#### IMPORTANT
## THIS GRAPH IS NOT PLOTTING THE X AXIS CORRECTLY
maxi = 10
mini = 0

# plt.plot(x1, y, color="b")
# plt.plot(x2, y, color="r")


# plt.xticks(np.arange(mini, maxi+1, 1.0))
# t = np.linspace(0, 10, 400)
plt.plot(x1, y)
plt.plot(x2, y)
plt.plot(x3, y)
plt.plot(x4, y)
#
# # plt.xticks(np.arange(min(x1,x2), max(x1,x2)+1, 1.0))
# # plt.xticks(np.arange(mini, maxi+1, 1.0))
#
plt.legend(['initial', 'optimized', 'mpi', 'omp'], loc='upper left')
plt.xlabel('time (sec)')
plt.ylabel('size of graph')
plt.title('times of different graphs')
ax = plt.gca()
plt.xticks(rotation=20)
for label in ax.get_xaxis().get_ticklabels()[::2]:
    label.set_visible(False)
plt.show()
#
#
#
# # print(x)
# # print("\n")
# # print(y1)
# # print("\n")
# # print(y2)
# # print("\n")
