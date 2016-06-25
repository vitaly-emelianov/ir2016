from bs4 import BeautifulSoup
from multiprocessing import Process
import os


class WikipediaParser(object):

    def __init__(self, processNumber=6):
        self.processNumber = processNumber

    def startRetrievingText(self):
        """Start retrieving article's text from HTML"""
        if not os.path.exists('./text'):
            os.makedirs('./text')

        filenames = os.listdir('./docs')
        fileNumber = len(filenames)

        processes = []
        partSize = len(filenames) / self.processNumber

        for i in xrange(0, self.processNumber - 1):
            if i == 0:
                files = filenames[1: partSize]
            else:
                files = filenames[i * partSize: (i + 1) * partSize]
            processes.append(Process(target=self.startWorker, args=(files,)))
        files = filenames[(self.processNumber - 1) * partSize:]
        processes.append(Process(target=self.startWorker, args=(files,)))
        for process in processes:
            process.start()
        for process in processes:
            process.join()

    def startWorker(self, files):
        for file in files:
            with open('./docs/' + file, 'r') as f :
                html = f.read()
                text = self.getPlainText(html)
            with open("./text/" + file.split('.')[0] + '.txt', 'w+') as f:
                f.write(text.encode('utf-8'))

    def getPlainText(self, html):
        """Get plain text from HTML"""
        soupDiv = BeautifulSoup(html);
        data = soupDiv.findAll('div', attrs={'id':'mw-content-text'})
        text = []
        for div in data:
            soupText = BeautifulSoup(div.text);
            text.append(soupText.text)
        return ' '.join(text)


if __name__ == '__main__':
    wp = WikipediaParser()
    wp.startRetrievingText()
