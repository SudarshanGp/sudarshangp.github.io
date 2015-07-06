import json
import requests
from pprint import pprint
import sys
import os
import math
import urllib2
import urllib
import shutil

from firebase import firebase
firebase = firebase.FirebaseApplication('https://sud.firebaseio.com/', None)
result = firebase.post('/Headings/Visited', '1', )
print result


# request = urllib2.urlopen('https://api.sportsdatallc.org/nba-t3/games/2015/04/08/schedule.json?api_key=skt8qqacw6dv83kvkxfcrybk'	)
# data = json.load(request)

#data = f.read()
#data1 = data.json()
# game_id = {}
# i = 0
# FILE = open('today_schedule.json', "w+")
# FILE.write("Date " + data['date'] + "\n")
# for game in data['games']:
# 	game_id[i] = game['id']
# 	FILE.write(game['id']+ "\n" + game['broadcast']['network'] + "\n" + game['home']['name']+ "\n"+game['home']['alias'] + '\n' + game['home']['id'] + '\n' + game['away']['name']+'\n'+ game['away']['alias']+ '\n'  + game['away']['id'] )
# 	i = i+1


# url_game_id = 'https://api.sportsdatallc.org/nba-t3/games/'+game_id[0] + '/boxscore.json?api_key=skt8qqacw6dv83kvkxfcrybk'
# #pprint(url_game_id)
# request_game_id = urllib2.urlopen(url_game_id)
# data_game_id = json.load(request_game_id)




# FILE.close()

#name of teams playing, scores, quarter scores, live video.. , game stats, player stats, all games playing on the current day.
#schdule . games[i][status], games[i][venue][name], games[i][network] ,
# games[i][home][name] and the alias, games[i][away][name] and alias