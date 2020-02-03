# bs4 advance findAll() find()
from bs4 import BeautifulSoup
from urllib.request import urlopen
from urllib.error import HTTPError

url = "http://www.pythonscraping.com/pages/warandpeace.html"
try:
    html = urlopen(url)
except HTTPError as e:
    print(e)
else:
    try:
        bsObj = BeautifulSoup(html.read())
        # nameList = bsObj.findAll("span", {"class":"green"})
        nameList = bsObj.findAll(text="the prince")            
        for name in nameList:
            print(name)

        allText = bsObj.findAll(id="text")
        print(allText[0].get_text())
    except AttributeError as e:
        print(e)



