import numpy as np
import os
import re
from simhash import simhash


def calculateSimhashes():
    """Calculate simhash values for number of textfiles."""
    word_counts = dict()
    hashes = dict()
    files = os.listdir('./text')
    counter = 0

    for file in files:
        counter += 1
        if counter % 1000 == 0:
            print counter
        with open('./text/' + file, 'r') as f:
            lines = f.readlines()
            words = []
            for line in lines:
                for word in re.split('\W+', line):
                    if word != '':
                        newWord = word.lower()
                        words.append(newWord)
            hashes[file] = simhash(words)
            word_counts[file] = len(words)

    with open("word_counts.txt", 'w+') as f:
        for (file, count) in word_counts.items():
            f.write(file + '\t' + str(count) + '\n')
    with open("hashes.txt", 'w+') as f:
        for (file, hash) in hashes.items():
            f.write(file + '\t' + str(hash) + '\n')


if __name__ == '__main__':
    calculateSimhashes()
