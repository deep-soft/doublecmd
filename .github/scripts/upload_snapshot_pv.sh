#!/bin/bash
# 2023-10-05 23:20

echo $("uname")

echo $OSTYPE

if [[ "$OSTYPE" == "msys" ]]; then

  # set | grep PATH
  pwd

  if [[ "$PSFTP_EXE" == "" ]]; then
    echo "$SSH_PRIVATE_KEY" > ssh_key
    ls -la ssh_key
    # icacls.exe D:/a/_temp/ssh_key //inheritance:r
    echo "cd dev/doublecmd-release" > upload_snapshot.txt
    echo "lcd doublecmd-release" >> upload_snapshot.txt
  #  echo "rm *.7z" >> upload_snapshot.txt
    echo "put *.7z" >> upload_snapshot.txt
    echo "put *.zip" >> upload_snapshot.txt
    echo "put *.txt" >> upload_snapshot.txt
    echo "quit" >> upload_snapshot.txt
    cat upload_snapshot.txt
    sftp -o StrictHostKeyChecking=no -o HostKeyAlgorithms=+ssh-rsa -i ssh_key -b upload_snapshot.txt -P $REMOTE_PORT $REMOTE_USER@$REMOTE_HOST
  else
    echo "$SSH_PRIVATE_KEY_P" > ssh_key
    ls -la ssh_key
    # icacls.exe D:/a/_temp/ssh_key //inheritance:r
    echo "cd dev/doublecmd-release" > upload_snapshot.txt
    echo "lcd doublecmd-release" >> upload_snapshot.txt
  #  echo "rm *.7z" >> upload_snapshot.txt
    echo "mput *.7z" >> upload_snapshot.txt
    echo "mput *.zip" >> upload_snapshot.txt
    echo "mput *.txt" >> upload_snapshot.txt
    echo "quit" >> upload_snapshot.txt
    cat upload_snapshot.txt
    echo n | $PSFTP_EXE -i ssh_key -P $REMOTE_PORT $REMOTE_USER@$REMOTE_HOST -be -b upload_snapshot.txt
  fi

else

  # set | grep PATH
  pwd

  if [[ "$PSFTP_EXE" == "" ]]; then
    echo "$SSH_PRIVATE_KEY" > ssh_key
    chmod 0600 ssh_key
    echo "cd dev/doublecmd-release" > upload_snapshot.txt
    echo "lcd doublecmd-release" >> upload_snapshot.txt
  #  echo "rm *.dmg" >> upload_snapshot.txt
    echo "put *.dmg" >> upload_snapshot.txt
    echo "put *.zip" >> upload_snapshot.txt
    echo "put *.php" >> upload_snapshot.txt
    echo "quit" >> upload_snapshot.txt
    cat upload_snapshot.txt
    sftp -o StrictHostKeyChecking=no -o HostKeyAlgorithms=+ssh-rsa -i ssh_key -b upload_snapshot.txt -P $REMOTE_PORT $REMOTE_USER@$REMOTE_HOST
  else
    echo "$SSH_PRIVATE_KEY_P" > ssh_key
    chmod 0600 ssh_key
    echo "cd dev/doublecmd-release" > upload_snapshot.txt
    echo "lcd doublecmd-release" >> upload_snapshot.txt
  #  echo "rm *.dmg" >> upload_snapshot.txt
    echo "mput *.dmg" >> upload_snapshot.txt
    echo "mput *.zip" >> upload_snapshot.txt
    echo "mput *.php" >> upload_snapshot.txt
    echo "quit" >> upload_snapshot.txt
    cat upload_snapshot.txt
    echo n | $PSFTP_EXE -i ssh_key -P $REMOTE_PORT $REMOTE_USER@$REMOTE_HOST -be -b upload_snapshot.txt
  fi

fi

echo "SSH_PRIVATE_KEY_P=$SSH_PRIVATE_KEY_P" > sets
echo "$PSFTP_EXE -i ssh_key -P $REMOTE_PORT $REMOTE_USER@$REMOTE_HOST -be -b upload_snapshot.txt" >> sets

rm -f ssh_key upload_snapshot.txt
if [[ -f $PSFTP_EXE ]]; then
  rm $PSFTP_EXE
fi
