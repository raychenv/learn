from urllib.request import urlopen
from bs4 import BeautifulSoup
import re

url = "http://www.pythonscraping.com/pages/page3.html"
html = urlopen(url)
bsObj = BeautifulSoup(html)

len2tags = bsObj.findAll(lambda tag: len(tag.attrs) == 2)
print(len2tags)