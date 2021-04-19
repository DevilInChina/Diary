file=$(find $1 -name *md|sort | xargs )
echo \[toc\] >> $2
for i in $file; 
	do cat $i >> $2 ;
	echo "" >> $2; 
done
