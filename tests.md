## start
do ```make && ./ircserv 6667 bla```
or ```make && valgrind --leak-check=full --track-fds=yes ./ircserv 6667 bla```

## basic
```
irssi

/connect localhost 6667 bla n1
/oper opername operpass
/die
```

## nick collision
```
irssi

/connect localhost 6667 bla n1
/connect localhost 6667 bla n1
/connect localhost 6667 bla n1
/nick n1
/nick n1
/nick n1
/connect localhost 6667 bla n1
/join channeltest
/join channeltest
/connect localhost 6667 bla n1
/connect localhost 6667 bla n1
/connect localhost 6667 bla n1
/nick n1
/nick n1
/nick n1
/oper opername operpass
/die
```

## Trying to join without pass
```
irssi

/connect localhost 6667
/PING
/JOIN h
blabla
```

## trying to join without pass
```
nc -C localhost 6667

NICK yoo
USER yoyo yoyo yoyo : yoyo
PING
JOIN h
PRIVMSG h blabla
```

## Trying OPER commands without being OPER
```
nc -C localhost 6667

PASS bla
NICK yoo
USER realname unused hostname :real name
DIE
KILL bla
REHASH
RESTART
```

## Trying OPER
```
nc -C localhost 6667

PASS bla
NICK yaa
USER realname unused hostname :real name
JOIN #BLABLA,#blabla,#,B
```
```
nc -C localhost 6667

PASS bla
NICK yii
USER realname unused hostname :real name
JOIN #BLABLA,#blabla,#,Y
NICK yuu
```
```
nc -C localhost 6667

PASS bla
NICK yoo
USER realname unused hostname :real name
OPER opername operpass
KILL yuu :
KILL yuu :tu es moche
NOTICE yaa :blabla
REHASH
RESTART
```

## Trying OPER commands
```
irssi

/connect localhost 6667 bla yoo
/JOIN #BLABLA,#blabla,#,B
```
```
irssi

/connect localhost 6667 bla yaa
/JOIN #BLABLA,#blabla,#,Y
/NICK yLL
```
```
nc -C localhost 6667

PASS bla
NICK yuu
USER realname unused hostname :real name
JOIN #BLABLA,#blabla,#,Y
NICK yPP
```
```
irssi

/connect localhost 6667 bla yGG
/OPER opername operpass
/KILL yPP
/KILL yPP :
/KILL yLL :tu es moche
/KILL yLL :tu es moche
/NOTICE yoo blabla
/msg #BLABLA blabladcdcdc
/NOTICE #BLABLA blabla
/msg yoo blabladcdcdc
/REHASH
/RESTART
/connect localhost 6667 bla yGG
/JOIN h,j,y,r,s,fd,dfvw,dfv,df,dg
/OPER opername operpass
/RESTART
/connect localhost 6667 bla yGG
/OPER opername operpass
/DIE
```