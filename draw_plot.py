import matplotlib.pyplot as plt
import pandas as pd
log_file = 'cycles_times.log'
data = pd.read_csv(log_file, delimiter=',')
print(data.head())
plt.plot(data, marker='o', color='b')
plt.xlim(xmin=0)
plt.ylim(ymin=0)
plt.xlabel("Iterations (by 0.25 sec interval)")
plt.ylabel("Cycles (by rdtsc())")
plt.title("Timing of the branch code block in the spy process,\nreflecting the data sent by the trojan.")
plt.savefig("cycles_times.png", bbox_inches="tight")
plt.show()
plt.close()
