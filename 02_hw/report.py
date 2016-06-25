from matplotlib import pyplot as plt
import numpy as np
import scipy.stats as st


def distanceHistogram():
    """Plot distances histogram."""
    distances = np.load("distances15.npy")
    mean = distances.mean()
    std = distances.std()
    print "mean, std =", mean, std
    print "skewness =", st.skew(distances)
    plt.figure(figsize=(12, 8))
    plt.hist(distances, bins=distances.max(), alpha=0.4, normed=True)
    x = np.linspace(-10, 50, 1000)
    plt.plot(x, st.norm.pdf(x, mean, std), color='k')
    plt.axvline(mean, color='k', linestyle='dashed')
    plt.xlabel('Simhash distance')
    plt.ylabel('Counts')
    plt.show()


def sizeHistogram():
    """Plot cluster's sizes histogram."""
    sizes = np.load("sizes10.npy")
    fig, ax = plt.subplots()
    plt.hist(sizes, bins=40, alpha=0.5, range=(0, 40))
    plt.xlabel('Cluster size')
    plt.ylabel('Counts')
    ax.set_yticks(np.linspace(0, 200, 10), minor=True)
    plt.show()


def top10():
    """Get top 10 biggest clusters"""
    clusters = np.load('clusters5.npy').item()
    sizes = dict()
    for (k, v) in clusters.items():
        sizes[k] = len(v)
    top = sorted(sizes.iteritems(), key=lambda (k, v): (-v, k))[:11]
    with open("urls.txt", 'r') as f:
        lines = f.readlines()
    urls = dict()
    for line in lines:
        (id, url) = line.split()
        urls[int(id.split('.')[0])] = str(url)

    for (k, v) in top:
        print urls[int(k.split('.')[0])], v


if __name__ == '__main__':
    # distanceHistogram()
    sizeHistogram()
    # top10()
