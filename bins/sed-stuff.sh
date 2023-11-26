#!/bin/bash
#sed-stuff.sh
#BOF

FILE_TO_CAT="$2";
debug_mode="$DEBUG_MODE_1";
debug_mode_2="$DEBUG_MODE_2";

if [[ "$debug_mode" == "" ]]; then
  debug_mode="N";
fi

if [[ "$debug_mode_2" == "" ]]; then
  debug_mode_2="N";
fi

echo_debug () {
if [[ "$debug_mode" == "Y" ]]; then
  echo "$1";
fi;
}

echo_debug_2 () {
if [[ "$debug_mode_2" == "Y" ]]; then
  echo "$1";
fi;
}

#file_in="sed-stuff.txt"
#file_in="${0%.*}".txt
#echo $file_in

if [[ "$1" != "_" && -f "$1" ]]; then
  file_in="$1";
else
  file_in="${0%.*}".txt;
fi

if [[ -f "$file_in" ]]; then
  _count_=0;
  _countf_=0;
  echo "file_in:[$file_in]";
  cat $file_in | while read -r the_line
  do
    ((count++));
    if [[ ${the_line:0:2} == "S:" ]]; then _str_=$(echo "${the_line:2}" | tr -d "\r"); echo_debug "str:[$_str_]"; fi;
    if [[ ${the_line:0:2} == "R:" ]]; then _rpl_=$(echo "${the_line:2}" | tr -d "\r"); echo_debug "rpl:[$_rpl_]"; fi;
    if [[ ${the_line:0:2} == "F:" ]]; then _fil_=$(echo "${the_line:2}" | tr -d "\r"); echo_debug "fil:[$_fil_]"; fi;
    if [[ "$_fil_" != "" ]]; then
      if [[ -f "$_fil_" ]]; then
        ((countf++));
        echo_debug "sed -i \"s|$_str_|$_rpl_|\" $_fil_";
        _str_s_=$(grep "$_str_" "$_fil_");
        echo_debug_2 "CNTF:$countf: $_str_n_";
        sed -i "s!$_str_!$_rpl_!" "$_fil_";
        _str_r_=$(grep "$_rpl_" "$_fil_");
        if [[ "$_str_s_" != "" ]] && [[ "$_str_r_" != "" ]]; then
          echo "OK_OK: [CNT:$count, CNTF:$countf]";
        else
          echo "NOTOK: [CNT:$count, CNTF:$countf]";
        fi;
        if [[ "$debug_mode" == "Y" ]]; then
          echo "grep 1";
          grep "$_str_" "$_fil_";
          echo "grep 2";
          grep "$_rpl_" "$_fil_";
        fi;
      else
        echo "not_found: [$_fil_]";
      fi;
      _str_="";
      _rpl_="";
      _fil_="";
    fi;
    # status=$(echo "[CNT:$count, CNTF:$countf]");
  done;
  if [[ "$debug_mode" == "Y" ]]; then
    if [[ "$FILE_TO_CAT" != "" ]]; then
      echo " [[ $FILE_TO_CAT : begin ]]";
      cat $FILE_TO_CAT;
      echo " [[ $FILE_TO_CAT : end ]]";
    fi
  fi
  # echo "$status"
  # not working outside the while loop (runs in subshell process, do not have access to main shell)
fi;

#EOF
