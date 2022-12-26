import matplotlib.pyplot as plt
import pandas as pd

df=pd.read_csv("learning_accuracy.csv")
epoch=df['epoch']
train_accuracy=df['train_accuracy']
test_accuracy=df['test_accuracy']
total_accuracy=df['total_accuracy']
fig = plt.figure()
plt.grid(linestyle='dotted')
plt.plot(epoch,train_accuracy)
plt.plot(epoch,test_accuracy)
#plt.plot(epoch,total_accuracy)
plt.legend(["train_accuracy", "test_accuracy","total_accuracy"], loc ="lower right") 
plt.title(str(df.columns[-1])+" bits")
fig.savefig(str(df.columns[-1])+"bits graph")

fig = plt.figure()
plt.legend(["total_accuracy"], loc ="lower right") 
plt.grid(linestyle='dotted')
plt.plot(epoch,total_accuracy)
plt.title(str(df.columns[-1])+" bits")
fig.savefig(str(df.columns[-1])+"bits total accuracy graph")

max_acc=test_accuracy.max()
print("max test accuracy",max_acc)
print("max index",test_accuracy.argmax())

