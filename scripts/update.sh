#!/bin/bash
Year=$(date +%Y)
Month=$(date +%m)
Day=$(date +%d)
diary_root=$1

Month=$(printf "%02d" $Month)
Day=$(printf "%02d" $Day)
Year=$(printf "%04d" $Year)

Update_info="$Year $Month $Day"

curD=$(pwd)
cd $diary_root
all_file=$(ls . | grep [0-9] | xargs)
git add $all_file
git commit -m "$Update_info"
git push origin main
cd $curD
