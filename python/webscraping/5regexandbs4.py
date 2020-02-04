from urllib.request import urlopen
from bs4 import BeautifulSoup
import re

url = "http://www.pythonscraping.com/pages/page3.html"
html = urlopen(url)
bsObj = BeautifulSoup(html)

images = bsObj.findAll("img", {"src":re.compile("\.\./img\/gifts/img.*\.jpg")})
print(images)
for image in images:
    print(image["src"])

    # Accessing Attributes
    print(image.attrs['src'])