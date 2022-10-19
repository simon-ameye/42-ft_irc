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
USER username hostname ft_irc : real name
PING
JOIN h
PRIVMSG h blabla
```

## Trying OPER commands without being OPER
```
nc -C localhost 6667

PASS bla
NICK yoo
USER username hostname ft_irc :real name
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
USER username hostname ft_irc :real name
JOIN #BLABLA,#blabla,#,B
```
```
nc -C localhost 6667

PASS bla
NICK yii
USER username hostname ft_irc :real name
JOIN #BLABLA,#blabla,#,Y
NICK yuu
```
```
nc -C localhost 6667

PASS bla
NICK yoo
USER username hostname ft_irc :real name
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
USER username hostname ft_irc :real name
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

##test user
```
nc -C localhost 6667

PASS bla
NICK yuu
USER
USER
USER a a a a
USER a a a
USER            ;
USER           j
USER r r r r
USER f f f f f:::::dsdsc
USER username hostname ft_irc :real name
/
```

##test topic
```
irssi

/connect localhost 6667 bla yGG
/JOIN h,j,y,r,s,fd,dfvw,dfv,df,dg
/TOPIC h
/TOPIC
/TOPIC  h
/TOPIC    h
/TOPIC hhhhh
/TOPIC h_
/TOPIC	h_
/TOPIC h_ :
/TOPIC h  :
/TOPIC h ::
/TOPIC h:fvdv
/TOPIC h:dfvjndkjndfv dfvn dv dnv dn df:sd c sdc sdc sd
/TOPIC h: dfvjndkjndfv dfvn dv dnv dn df:sd c sdc sdc sd
/TOPIC h :dfvjndkjndfv dfvn dv dnv dn df:sd c sdc sdc sd
/TOPIC h   :dfvjndkjndfv dfvn dv dnv dn df:sd c sdc sdc sd
/TOPIC   h :dfvjndkjndfv dfvn dv dnv dn df:sd c sdc sdc sd
```
```
nc -C localhost 6667

PASS bla
NICK yoo
USER username hostname ft_irc :real name
connect localhost 6667 bla yGG
JOIN h,j,y,r,s,fd,dfvw,dfv,df,dg
TOPIC h
TOPIC
TOPIC  h
TOPIC    h
TOPIC hhhhh
TOPIC h_
TOPIC	h_
TOPIC h_ :
TOPIC h  :
TOPIC h ::
TOPIC h:fvdv
TOPIC h:dfvjndkjndfv dfvn dv dnv dn df:sd c sdc sdc sd
TOPIC h: dfvjndkjndfv dfvn dv dnv dn df:sd c sdc sdc sd
TOPIC h :dfvjndkjndfv dfvn dv dnv dn df:sd c sdc sdc sd
TOPIC h   :dfvjndkjndfv dfvn dv dnv dn df:sd c sdc sdc sd
TOPIC   h :dfvjndkjndfv dfvn dv dnv dn df:sd c sdc sdc sd
```

##test restart
```
irssi

/connect localhost 6667 bla n1
/oper opername operpass
/restart
/connect localhost 6667 bla n1
/connect localhost 6667 bla n1
/connect localhost 6667 bla n1
/join f,h,y,d
/join f,h,y,d
/connect localhost 6667 bla n1
/join f,h,y,d
/connect localhost 6667 bla n1
/join f,h,y,d
/oper opername operpass
/restart
/connect localhost 6667 bla n1
/oper opername operpass
/restart
/connect localhost 6667 bla n1
/oper opername operpass
/restart
/connect localhost 6667 bla n1
/oper opername operpass
/restart
/connect localhost 6667 bla n1
/oper opername operpass
/restart
/connect localhost 6667 bla n1
/oper opername operpass
/restart
/connect localhost 6667 bla n1
/oper opername operpass
/restart
/connect localhost 6667 bla n1
/oper opername operpass
/restart
/connect localhost 6667 bla n1
/connect localhost 6667 bla n1
/connect localhost 6667 bla n1
/connect localhost 6667 bla n1
/connect localhost 6667 bla n1
/connect localhost 6667 bla n1
/oper opername operpass
/restart
```

