./a.out 5 5
for ((n = 10; n < 151; n+=10)); do
    ./a.out $n $n
    echo $n
done
