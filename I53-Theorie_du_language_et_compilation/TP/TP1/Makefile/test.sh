for i in {10..28}
do
	echo $i
	./crible.exe $$i > timing.dat
	echo $i
done