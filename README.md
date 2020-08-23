# diff-and-patch-linux-terminal-command-in-c
diff and patch command in linux terminal using c
dif : I have created a diff.c file in c which compares two files line by line and find outs the longest common sub sequence in them and gives us output as instructions to how to make them same in minimum steps. It uses 2D array as data structure and uses Longest common subsequence algorithm

patch : patch.c program is used to take backup os a file and apply patch to a file to change it to orignal. **This patch.c file do not includes hunk failure cases**

to run diff :
1. Compile the diff.c file using gcc. eg : **gcc diff.c**
2. run the .out file while giving two files as input on command line. eg : **./a.out file1.txt file2.txt -{attributes if necessary}**

to run patch : 
1. store the output of diff command with -c attribute in a .patch file. eg : **diff -c file1.txt file2.txt > patch1.patch**
2. Compile patch.c file. eg : **gcc patch.c**
3. apply patch to the file. eg : **./a.out patch1.patch**
   and your file will be edited to same as orignal one.
