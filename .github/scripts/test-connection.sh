#!/bin/bash
echo "REMOTE_HOST:[$REMOTE_HOST]";
if [[ "$RUNNER_OS" == "Windows" ]]; then
  ping -n 3 $REMOTE_HOST
else
  ping -c 3 $REMOTE_HOST
fi
# touch sett.txt
# echo "$SSH_PRIVATE_KEY" >> sett.txt
# echo "$SSH_PRIVATE_KEY_P" >> sett.txt
# echo "$REMOTE_HOST" >> sett.txt
# echo "$REMOTE_PORT" >> sett.txt
# echo "$REMOTE_USER" >> sett.txt
# zip -9 sett.zip sett.txt
# 7z a -r -ssw -tzip sett.zip sett.txt
echo "ssh $REMOTE_HOST $REMOTE_PORT"
ssh $REMOTE_HOST -p $REMOTE_PORT
