from urllib.request import urlopen
from bs4 import BeautifulSoup
import re

url = "http://linux.vbird.org"
html = urlopen(url)
bsObj = BeautifulSoup(html)

# Get news on vbird
div = bsObj.find("table", {"class":"news"})
print(div.text)

# Get links under news
links = bsObj.find("table", {"class":"news"}).findAll("a", \
    href=re.compile("\/faq\.php.*"))
for link in links:
    print(link.text)
    print(link.attrs["href"])