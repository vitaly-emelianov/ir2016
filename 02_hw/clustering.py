import numpy as np
from simhash import distance
import random
import operator


def buildClusters(n=5):
    """Build clusters given document's hashes and lengths, threshold n"""
    word_counts = dict()
    with open('word_counts.txt', 'r') as f:
        lines = f.readlines()
        for line in lines:
            item = line.split('\t')
            word_counts[item[0]] = int(item[1])
    hashes = dict()
    with open('hashes.txt', 'r') as f:
        lines = f.readlines()
        for line in lines:
            item = line.split('\t')
            hashes[item[0]] = int(item[1])
    # distances= []
    clusters = dict()
    cluster_sizes = []
    sorted_counts = sorted(word_counts.items(), key=operator.itemgetter(1))
    files = set(word_counts.keys())
    indices = set(range(0, len(word_counts)))
    while len(indices) > 0:
        index = random.sample(indices, 1)[0]
        indices.remove(index)
        file = sorted_counts[index][0]
        clusters[file] = set()
        hash = hashes[file]
        length = float(word_counts[file])
        if length == 0:
            length = 1
        if index > 0:
            i = index - 1
            filel = sorted_counts[i][0]
            while i >= 0 and abs(word_counts[filel] - length) / length <= 0.2:
                filel = sorted_counts[i][0]
                dist = distance(hash, hashes[filel])
                # distances.append(dist)
                if i in indices and dist <= n:
                    clusters[file].add(filel)
                    indices.remove(i)
                i -= 1
        if index < len(word_counts) - 1:
            i = index + 1
            filer = sorted_counts[i][0]
            while i < len(word_counts) and abs(word_counts[filer] - length) / length <= 0.2:
                filer = sorted_counts[i][0]
                dist = distance(hash, hashes[filer])
                # distances.append(dist)
                if i in indices and dist <= n:
                    clusters[file].add(filer)
                    indices.remove(i)
                i += 1
        cluster_sizes.append(len(clusters[file]))
        print len(indices)

    np.save('clusters5.npy', clusters)
    # np.save('distances15.npy', distances)
    np.save('sizes5.npy', cluster_sizes)


if __name__ == '__main__':
    buildClusters()
