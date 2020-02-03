# Our first web scraper

from urllib.request import urlopen
import requests

html = urlopen("https://www.baidu.com")

print(html.read())

res = requests.get("https://api.github.com/events")
print(res)