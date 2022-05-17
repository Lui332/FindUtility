printf "\nPART 1: find where-to-look\n" > find_one_output.txt
printf "\n--- COMMAND: find testdir\n\n" >> find_one_output.txt
./find_one.exe testdir >> find_one_output.txt
printf "\n--- COMMAND: find testdir/dir1\n\n" >> find_one_output.txt
./find_one.exe testdir/dir1 >> find_one_output.txt
printf "\n--- COMMAND: find testdir/dir3\n\n" >> find_one_output.txt
./find_one.exe testdir/dir3 >> find_one_output.txt
printf "\n\n" >> find_one_output.txt
echo "   find_one.c output is in find_one_output.txt"


printf "\nPART 2: find where-to-look criteria\n" > find_two_output.txt
printf "\n--- COMMAND: find -n test7 \n\n" >> find_two_output.txt
./find_two.exe -n test7 >> find_two_output.txt
printf "\n--- COMMAND: find -n dir3 \n\n" >> find_two_output.txt
./find_two.exe -n dir3 >> find_two_output.txt
printf "\n--- COMMAND: find -m -5 \n\n" >> find_two_output.txt
./find_two.exe -m -5 >> find_two_output.txt
printf "\n--- COMMAND: li -i \n\n" >> find_two_output.txt
ls -i >> find_two_output.txt
printf "\n--- COMMAND: find -i 62522480\n\n" >> find_two_output.txt
./find_two.exe -i 62522480 >> find_two_output.txt
printf "\n--- COMMAND: find -i 62523151\n\n" >> find_two_output.txt
./find_two.exe -i 62523151 >> find_two_output.txt
printf "\n--- COMMAND: find -w testdir -n test1 -i 44062919\n\n" >> find_two_output.txt
./find_two.exe -w testdir -n test1 -i 44062919 >> find_two_output.txt
printf "\n--- COMMAND: find -w testdir -i 62522493\n\n" >> find_two_output.txt
./find_two.exe -w testdir -i 62522493 >> find_two_output.txt
printf "\n--- COMMAND: find -w testdir -m +10\n\n" >> find_two_output.txt
./find_two.exe -w testdir -m +10 >> find_two_output.txt
printf "\n\n" >> find_two_output.txt
echo "   find_two.c output is in find_two_output.txt"


printf "\nPART 3: find where-to-look criteria -delete\n" > find_three_output.txt
printf "\n--- COMMAND: touch exampleFile \n\n" >> find_three_output.txt
touch exampleFile >> find_three_output.txt
printf "\n--- COMMAND: ls \n\n" >> find_three_output.txt
ls >> find_three_output.txt
printf "\n--- COMMAND: find -n exampleFile -a delete \n\n" >> find_three_output.txt
./find_three.exe -n exampleFile -a delete >> find_three_output.txt
printf "\n--- COMMAND: ls \n\n" >> find_three_output.txt
ls >> find_three_output.txt
printf "\n--- COMMAND: touch exampleFile testdir/exampleFile testdir/dir1/dir2/exampleFile \n\n" >> find_three_output.txt
touch exampleFile testdir/exampleFile testdir/dir1/dir2/exampleFile >> find_three_output.txt
printf "\n--- COMMAND: find -n exampleFile -a delete \n\n" >> find_three_output.txt
./find_three.exe -n exampleFile -a delete >> find_three_output.txt
printf "\n\n" >> find_three_output.txt
echo "   find_three.c output is in find_three_output.txt"
