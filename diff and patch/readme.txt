Name : Abhishek Honmute
MIS No. : 111803055
Subject : DSA Project
Topic : Diff and Patch Command


Diff :
	diff command compairs two files or directories. for the text file it compairs files line by line. for this i have used longest common subsequence algorithm on lines to find longst common subsequence in file. then it according to attributes or no attribute it gives instructions how to make first file same as second.
	i have made 3 output styles having attributes (no output style attribute), -c , -y . without attribute it gives output with a(add) , d(delet) , c(change) codes. for -c attribute it gives output with statitics of the file which is used further for patch command. 
-y attribute gives output in two coloms.
	along with 3 style attributes i have made 4 more attributes -t(expand-tabs expand tabs to spaces in output) , -w( output at most NUM print columns) -b(ignore changes in the amount of white space), -i(ignore case differences in file contents) .
	multipal attributes can be give .but no more than one styling attributes are all allowed .
	diff command is used to check what is the difference between two files, whether they are same or not.
	
	
Patch :
	Patch command is applied on patch file which is output of diff -c command stored in it. on applying it , file 1 given to diff -c command becomes same as file 2 in diff -c. i have first deleated file 1 and created new one with same name as file 1. new file 1 is written with sepcific part of patch command.
	patch command can be used to backup files.
