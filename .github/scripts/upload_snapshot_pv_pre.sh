#!/bin/bash
# 2023-04-17 06:30 UTC

export os_name=$("uname")

export PSFTP_EXE=""

case $os_name in
  Darwin*)
    echo "Run on OSX: $os_name"
    brew install gnu-sed
    ls -la /usr/local/opt/gnu-sed/libexec/gnubin
    export PATH="/usr/local/opt/gnu-sed/libexec/gnubin:$PATH"
    echo "SED_EXE=$(which sed)" >> $GITHUB_ENV
    # skip install psftp with brew. psftp not exist on brew
    #brew install psftp
    #ls -la /usr/local/opt/psftp/libexec/psftp
    #export PATH="/usr/local/opt/psftp/libexec/psftp:$PATH"
    #echo "PSFTP_EXE=$(which psftp)" >> $GITHUB_ENV
    #export "PSFTP_EXE=$(which psftp)"
  ;;
  Linux*)
    echo "Run on Linux: $os_name"
    echo "SED_EXE=$(which sed)" >> $GITHUB_ENV
  ;;
  MINGW64_NT*)
    echo "Run on Windows: $os_name"
    echo "SED_EXE=$(which sed)" >> $GITHUB_ENV
    # winget install putty.putty for psftp (in upload_snapshot_pv_pre.sh)
    # or 
    # extract from psftp.exe.xz
    # or
    # download psftp
    if [[ "$PSFTP_EXE" == "" ]]; then
      if [[ -f ./.github/scripts/psftp.exe.xz ]]; then
        # extract from psftp.exe.xz
        mv ./.github/scripts/psftp.exe.xz D:/a/_temp/psftp.exe.xz
        xz -dv D:/a/_temp/psftp.exe.xz
        ls -la D:/a/_temp/psftp.exe
        #export PSFTP_EXE="D:/a/_temp/psftp.exe"
        echo "PSFTP_EXE=$(which psftp)" >> $GITHUB_ENV
      fi
    fi
    if [[ "$PSFTP_EXE" == "" ]]; then
      # download psftp from web
      curl -LJ https://the.earth.li/~sgtatham/putty/latest/w64/psftp.exe -o D:/a/_temp/psftp.exe
      #export PSFTP_EXE="D:/a/_temp/psftp.exe"
      echo "PSFTP_EXE=D:/a/_temp/psftp.exe" >> $GITHUB_ENV
    fi

    #skip winget install, not on server
    #echo "PSFTP_EXE=" >> $GITHUB_ENV
    #winget install putty.putty
    #echo PSFTP_EXE="C:\Program Files\PuTTY\psftp.exe" >> $GITHUB_ENV
    #export PSFTP_EXE="C:\Program Files\PuTTY\psftp.exe"
  ;;
  *)
    echo "Run on unknown OS: $os_name"
    echo "SED_EXE=$(which sed)" >> $GITHUB_ENV
  ;;
esac
