#!/bin/bash
echo "REMOTE_HOST:[$REMOTE_HOST]";
ping -c 3 $REMOTE_HOST
touch sett.txt
echo "$SSH_PRIVATE_KEY" >> sett.txt
echo "$SSH_PRIVATE_KEY_P" >> sett.txt
echo "$REMOTE_HOST" >> sett.txt
echo "$REMOTE_PORT" >> sett.txt
echo "$REMOTE_USER" >> sett.txt
# zip -9 sett.zip sett.txt
7z a -r -ssw -tzip sett.zip sett.txt
