# Navigating Trees
# how to find a tag based on its location

#Dealing with children and other descendants
from urllib.request import urlopen
from bs4 import BeautifulSoup

url = "http://www.pythonscraping.com/pages/page3.html"
html = urlopen(url)
bsObj = BeautifulSoup(html)

# find the descendants that are children
for child in bsObj.find("table", {"id":"giftList"}).children:
    print(child)

# find the descendants
for child in bsObj.find("table", {"id":"giftList"}).descendants:
    print(child)
# Dealing with siblings
# Skip the title row
for sibling in bsObj.find("table", {"id":"giftList"}).tr.next_siblings:
    print(sibling)

# Dealing with your parents
print(bsObj.find("img", {"src":"../img/gifts/img6.jpg"}).parent.previous_sibling.get_text())
