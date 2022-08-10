#for~in 2

for fname in $(ls *.sh)
do
	echo "---$fname---"
	head -3 $fname
done

exit 0
