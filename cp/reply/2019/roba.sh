for x in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15; do
    echo $x
    time ./a.out $1 < in/b.txt > out/b$x.txt &
done;