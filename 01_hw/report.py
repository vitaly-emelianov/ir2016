import os
import numpy as np
import networkx as nx
from matplotlib import pyplot as plt
import re
from Queue import Queue


def sizeHistogram():
    """Plot article's size histogram"""
    files = os.listdir('./text')
    fileNumber = len(files)
    fileSize = []

    for file in files:
        size = os.path.getsize('./text/' + file)
        fileSize.append(size)
    plt.figure(figsize=(20,10))
    plt.hist(fileSize, bins=200, normed=False, range=[0, 20000], alpha= 0.5, color = 'b')
    plt.xlabel("size, bytes")
    plt.ylabel("counts")
    plt.axvline(np.median(fileSize), color='r', linestyle ='--')
    plt.text(np.median(fileSize) + 300, 6000,'median = 1523', rotation=90)
    plt.show()


def inOutDegreeHistogram():
    """Plot in/out degree histogram"""
    inDegrees = []
    outDegrees = []

    with open('./data/degrees.txt', 'r') as f:
        lines = f.read().split('\n')

    for line in lines:
        items = line.split(' ')
        inDegrees.append(int(items[1]))
        outDegrees.append(int(items[2]))
    plt.figure(figsize=(20,10))
    plt.hist(inDegrees, bins=100, range=[0, 100], alpha=0.5, label='in-degree', normed=False, color = 'k')
    plt.hist(outDegrees, bins=100, range=[0, 100], alpha=0.5, label='out-degree', normed=False, color = 'r')
    plt.legend(loc='upper right')
    plt.xlabel('degree')
    plt.ylabel('counts')
    plt.axvline(np.median(inDegrees), color='k', linestyle ='--')
    plt.axvline(np.median(outDegrees), color='r', linestyle ='--')
    plt.show()


def wordCounts():
    """Calculate word's occurence frequency in document collection"""
    wordCounter = dict()
    files = os.listdir('./text')
    counter = 0
    for file in files:
        counter += 1
        if counter % 1000 == 0:
            print counter
        with open('./text/' + file, 'r') as f:
            lines = f.readlines()
            for line in lines:
                for word in re.split('\W+', line):
                    newWord = word.lower()
                    if newWord not in wordCounter:
                        wordCounter[newWord] = 1
                    else:
                        wordCounter[newWord] += 1
    with open("word_counts.txt", 'w+') as f:
        for (word, count) in wordCounter.items():
            f.write(word.encode('utf-8') + '\t' + str(count) + '\n')


def wordCountsHistogram():
    """Plot word counts histogram"""
    wordCounter = dict()
    with open("word_counts.txt", 'r') as f:
        lines = f.readlines()
        for line in lines:
            (word, count) = line.split('\t')
            wordCounter[word] = int(count)
    freq = np.array(wordCounter.values())
    log_freq = np.log(freq)
    plt.figure(figsize=(20, 10))
    plt.hist(log_freq, 200, range=[0, 8], alpha=0.5)
    plt.xlabel("$\log$(wordFreq)")
    plt.ylabel("counts")
    plt.axvline(np.median(log_freq), color='r', linestyle ='--')
    plt.show()


def distancesHistogram():
    """Plot distances from Main Page histogram"""
    with open("./data/graph.txt", 'r') as f:
        lines = f.readlines()
    graph = dict()
    for line in lines:
        items = line.split('\t')
        node = int(items[0])
        if items[1] != '\n':
            adjacentNodes = set(map(int, items[1].split(' ')))
        else:
            adjacentNodes = set()
        graph[node] = adjacentNodes
    mainPageId = 31872
    distances = dict()
    distances[mainPageId] = 0
    q = Queue()
    q.put(mainPageId)
    visited = set()
    visited.add(mainPageId)
    while not q.empty():
        page = q.get()
        for link in graph[page]:
            if link not in visited:
                distances[link] = distances[page] + 1
                visited.add(link)
                q.put(link)
    plt.figure(figsize=(20, 10))
    plt.hist(distances.values(), 50, range=[0, 10], alpha=0.5)
    plt.xlabel('distances')
    plt.ylabel('counts')
    plt.axvline(np.median(distances.values()), color='r', linestyle ='--')
    plt.show()


def pageRank():
    """Calculate PageRank"""
    with open("./data/graph.txt", 'r') as f:
        lines = f.readlines()
    graph = dict()
    for line in lines:
        items = line.split('\t')
        node = int(items[0])
        if items[1] != '\n':
            adjacentNodes = set(map(int, items[1].split(' ')))
        else:
            adjacentNodes = set()
        graph[node] = adjacentNodes

    inNodes = dict()
    nodeCounter = 0
    for node1 in graph:
        nodeCounter +=1
        if nodeCounter % 100 == 0:
            print nodeCounter
        for node2 in graph:
            if node2 in graph[node1]:
                if node2 in inNodes:
                    inNodes[node2].add(node1)
                else:
                    inNodes[node2] = set()

    d = 0.85 # damping factor
    numloops = 100
    ranks = {}
    npages = len(graph)
    for page in graph:
        ranks[page] = 1.0 / npages
    for i in range(0, numloops):
        print i
        newranks = {}
        for page in graph:
            newrank = (1 - d) / npages
            for node in inNodes[page]:
                newrank = newrank + d * (ranks[node] / len(graph[node]))
            newranks[page] = newrank
        ranks = newranks
    with open("ranks.txt", 'w+') as f:
        for (node, rank) in ranks.items():
                f.write(str(node) + ' ' + str(rank) + '\n')


def getTop20Pages():
    """Get 20 page with highest PageRank"""
    with open("ranks.txt", 'r') as f:
        lines = f.readlines()
    ranks = dict()
    for line in lines:
        (id, rank) = line.split()
        ranks[int(id)] = float(rank)

    with open("./data/urls.txt", 'r') as f:
        lines = f.readlines()
    urls = dict()
    for line in lines:
        (id, url) = line.split()
        urls[int(id.split('.')[0])] = str(url)

    n = 0
    for (id, rank) in sorted(ranks.items(), key=lambda x: x[1], reverse=True):
        if n == 20:
            break
        n += 1
        print urls[id], rank


if __name__ == '__main__':
    sizeHistogram()
    inOutDegreeHistogram()
    wordCountsHistogram()
    distancesHistogram()
    pageRank()
    getTop20Pages()
