Year=$(date +%Y)
Month=$(date +%m)
Day=$(date +%d)
diary_root=$2
Editor=$1
if [[ $# = 3 ]] ;then
	Day=$3
elif [[ $# = 4 ]] ;then
	Month=$3
	Day=$4
elif [[ $# = 5 ]] ;then
	Year=$3
	Month=$4
	Day=$5
elif [[ $# != 2 ]] ;then 
	exit 1
fi

Month=$(printf "%02d" $Month)
Day=$(printf "%02d" $Day)
Year=$(printf "%04d" $Year)

weekday=$(date --date=$Year$Month$Day +%a)

if [[ $? != 0 ]] ; then
	echo invalid date
	exit 1
fi
	
mkdir -p $diary_root/$Year/$Month
File=$diary_root/$Year/$Month/$Day.md
if [ -f $File ] ; then
	$Editor $File
else
	echo "# $Year年$Month月$Day日 星期$weekday" > $File
	#echo >> $File
	echo "" >> $File
	$Editor $File
fi
exit 0
