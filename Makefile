all:scannerCSVsorter

scannerCSVsorter: mergesort.h movieListData.h movieValueList.h columnsorter.h tokenizer.h multiThreadSorter_thread.h generalFunctions.h hashTable.h hashTable.c mergesort.c movieListData.c movieValueList.c columnsorter.c tokenizer.c multiThreadSorter_thread.c generalFunctions.c
	gcc -Wall -Werror -pthread generalFunctions.c mergesort.c movieListData.c movieValueList.c hashTable.c columnsorter.c tokenizer.c multiThreadSorter_thread.c -o multiThreadSorter_thread

clean:
	rm -rf scannerCSVsorter
