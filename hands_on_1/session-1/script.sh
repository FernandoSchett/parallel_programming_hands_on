printf "THREADS\tSIZE(100)\tSIZE(200)\tSIZE(300)\tSIZE(400)\tSIZE(500)\tSIZE(600)\tSIZE(700)\tSIZE(800)\tSIZE(900)\tSIZE(1000)\tTIME\n"
for j in $1 $2 $3
do
 printf "$j\t"
 for i in 100 200 300 400 500 600 700 800 900 1000
 do
 ./mm $i $j
 printf "\t"
 done
 printf "\n"
done