./scheme 5 5
for ((n = 10; n < 151; n+=10)); do
    ./scheme $n $n
    echo $n
done
