import requests
import re
from bs4 import BeautifulSoup
from multiprocessing import Process, Manager, Lock
import operator


class WebCrawler(object):

    def __init__(self):
        self.manager = Manager()
        self.counter = self.manager.Value('i', 0)
        self.graph = self.manager.dict()
        self.pageQueue = self.manager.Queue()
        self.urlId = self.manager.dict()
        self.inDegree = self.manager.dict()

        self.session = requests.Session()
        self.session.mount("http://", requests.adapters.HTTPAdapter(max_retries=3))
        self.session.mount("https://", requests.adapters.HTTPAdapter(max_retries=3))

    def startTraverse(self):
        """Start Wikipedia traverse from multiple seeds"""
        seeds = [
            "http://simple.wikipedia.org/wiki/Biology",
            "http://simple.wikipedia.org/wiki/Politics",
            "http://simple.wikipedia.org/wiki/Sport",
            "http://simple.wikipedia.org/wiki/Science",
            "http://simple.wikipedia.org/wiki/Language",
            "http://simple.wikipedia.org/wiki/Culture",
            "http://simple.wikipedia.org/wiki/Geography"
        ]
        processes = []
        locker = Lock()
        for seed in seeds:
            processes.append(Process(target=self.startWorker, args=(locker, seed,)))
        for process in processes:
            process.start()
        for process in processes:
            process.join()
        self.saveFilenames()
        self.saveGraph()
        self.saveInOutDegrees()

    def startWorker(self, locker, seedUrl):
        """Traverse of website starting from a seed"""
        with locker:
            self.counter.value += 1
            self.urlId[seedUrl] = self.counter.value
        self.pageQueue.put(seedUrl)

        while not self.pageQueue.empty():
            try:
                pageUrl = self.pageQueue.get(timeout=5)
            except:
                return
            pageId = self.urlId[pageUrl]
            pageHtml = self.getHtml(pageUrl)
            self.saveHtml(pageId, pageHtml)
            self.graph[pageId] = []
            urls = WebCrawler.getWikiUrlsFromHtml(pageHtml)
            for url in urls:
                with locker:
                    if url not in self.urlId:
                        self.counter.value += 1
                        self.urlId[url] = self.counter.value
                        if self.pageQueue.qsize() % 100 == 0:
                            print self.counter.value - self.pageQueue.qsize(), self.pageQueue.qsize()
                        self.pageQueue.put(url)
                self.graph[pageId] += [self.urlId[url]]
                try:
                    self.inDegree[self.urlId[url]] += 1
                except: 
                    self.inDegree[self.urlId[url]] = 1

    @staticmethod
    def getWikiUrlsFromHtml(html):
        """Parse html and get Wikipedia article's URLs"""
        urls = set()
        soup = BeautifulSoup(html);
        data = soup.findAll('div',attrs={'class':'mw-body-content'});
        for div in data:
            links = div.findAll('a')
            for a in links:
                if WebCrawler.isWikipediaArticle(a['href']):
                    urls.add(WebCrawler.repairUrl(a['href']))
        return urls

    @staticmethod
    def repairUrl(url):
        pos = url.find('#')
        if pos == -1:
            return 'http://simple.wikipedia.org' + url
        else:
            return 'http://simple.wikipedia.org' + url[:pos]

    @staticmethod
    def isWikipediaArticle(url):
        """Check whether URL is Wikipedia article"""
        pattern = re.compile("^\/wiki\/[^:]+$")
        if pattern.match(url) is None:
            return False
        else:
            return True

    def getHtml(self, url):
        """Get HTML code given page URL"""
        try:
            r = self.session.get(url)
            return r.text
        except:
            return " "

    def saveHtml(self, id, html):
        with open("docs/" + str(id) + ".html", 'w+') as f:
            f.write(html.encode('utf-8'))

    def saveFilenames(self):
        """Save filename to id map in urls.txt file"""
        with open("urls.txt", 'w+') as f:
            for (url, id) in self.urlId.items():
                f.write(str(id) + ".html\t" + url.encode('utf-8'))
                f.write('\n')

    def saveGraph(self):
        """Save Wikipedia graph in graph.txt file"""
        with open("graph.txt", 'w+') as f:
            for node in self.graph.keys():
                f.write(str(node) + '\t')
                adjacentNodes = self.graph[node]
                f.write(' '.join(map(str, adjacentNodes)) + '\n')

    def saveInOutDegrees(self):
        """Save in-out degrees of nodes"""
        with open("degrees.txt", 'w+') as f:
            for (id, in_degree) in self.inDegree.items():
                if id in self.graph:
                    out_degree = len(self.graph[id])
                else:
                    out_degree = 0
                f.write(' '.join([str(id),str(in_degree), str(out_degree)]))
                f.write('\n')


if __name__ == '__main__':
    wc= WebCrawler()
    wc.startTraverse()