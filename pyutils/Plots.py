import numpy as np
import matplotlib.pyplot as plt


def plot_speed_ups(times, labels, title=None):
    times = np.asarray(times, dtype=np.float32)
    speedups = np.round(times[0x0] / times, 0x2)

    _, ax = plt.subplots()
    if title is not None:
        ax.set_title(title)

    ax.set_ylabel('Elapsed Time (seconds)')

    bars = ax.bar(labels, times)
    for i, bar in enumerate(bars):
        height = bar.get_height()
        str = ""
        if i > 0:
            str = '{:1.3f}s  [{:1.2f}x]'.format(times[i], speedups[i])
        else:
            str = '{:1.3f}s'.format(times[i])
        ax.annotate(str,
                    xy=(bar.get_x() + bar.get_width() / 0x2, height),
                    xytext=(0x0, 0x3),
                    textcoords="offset points",
                    ha='center',
                    va='bottom')
    plt.yticks(np.arange(0, np.max(times) + 5, 5))
    plt.show()


def plot_speed_up(std, new, labels, title=None):
    speedup = np.round(std / new, 0x2)
    t =[std, new]
    _, ax = plt.subplots()
    if title is not None:
        ax.set_title(title)
    
    ax.set_ylabel('Elapsed Time (seconds)')

    bars = ax.bar(labels, t)
    for i, bar in enumerate(bars):
        height = bar.get_height()
        str = ""
        if i > 0:
            str = '{:1.2f}s  [{:1.2f}x]'.format(t[i], speedup)
        else:
            str = '{:1.2f}s'.format(t[i])
        ax.annotate(str,
            xy=(bar.get_x() + bar.get_width() / 0x2, height),
            xytext=(0x0, 0x3),
            textcoords="offset points",
            ha='center',
            va='bottom')
    plt.yticks(np.arange(0, std + 0x1, 0x1))
    plt.show()

if __name__ == '__main__':
    #plot_speed_up(5.439, 1.100, ["Std32", "Simd32"], title="Simd32 SpeedUp")
    #plot_speed_up(5.439, 0.664, ["Std32", "BlockWise32"], title="BlockWise32 SpeedUp")

    #plot_speed_up(5.548, 1.390, ["Std64", "Simd64"], title="Simd64 SpeedUp")
    #plot_speed_up(5.548, 0.846, ["Std64", "BlockWise64"], title="BlockWise64 SpeedUp")


    #plot_speed_ups([0.109, 0.062, 0.041], ["Std32", "Simd32", "BlockWise32"], title="Dataset (951,10) Performances")
    #plot_speed_ups([0.460, 0.102, 0.060], ["Std32", "Simd32", "BlockWise32"], title="Dataset (951,100) Performances")
    #plot_speed_ups([4.100, 0.506, 0.201], ["Std32", "Simd32", "BlockWise32"], title="Dataset (951,1000) Performances")

    #plot_speed_ups([1.179, 0.683, 0.476], ["Std32", "Simd32", "BlockWise32"], title="Dataset (3186,10) Performances")
    #plot_speed_ups([5.439, 1.100, 0.664], ["Std32", "Simd32", "BlockWise32"], title="Dataset (3186,100) Performances")
    #plot_speed_ups([46.877, 8.718, 3.370], ["Std32", "Simd32", "BlockWise32"], title="Dataset (3186,1000) Performances")


    #plot_speed_ups([0.113, 0.070, 0.058], ["Std64", "Simd64", "BlockWise64"], title="Dataset (951,10) Performances")
    #plot_speed_ups([0.576, 0.187, 0.094], ["Std64", "Simd64", "BlockWise64"], title="Dataset (951,100) Performances")
    #plot_speed_ups([4.483, 0.725, 0.327], ["Std64", "Simd64", "BlockWise64"], title="Dataset (951,1000) Performances")

    #plot_speed_ups([1.199, 0.748, 0.638], ["Std64", "Simd64", "BlockWise64"], title="Dataset (3186,10) Performances")
    #plot_speed_ups([5.548, 1.390, 0.846], ["Std64", "Simd64", "BlockWise64"], title="Dataset (3186,100) Performances")
    plot_speed_ups([51.224, 12.114, 6.389], ["Std64", "Simd64", "BlockWise64"], title="Dataset (3186,1000) Performances")
