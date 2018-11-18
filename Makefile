all:scannerCSVsorter

scannerCSVsorter: mergesort.h movieListData.h movieValueList.h columnsorter.h tokenizer.h scannerCSVsorter.h generalFunctions.h hashTable.h hashTable.c mergesort.c movieListData.c movieValueList.c columnsorter.c tokenizer.c scannerCSVsorter.c generalFunctions.c
	gcc -Wall -Werror generalFunctions.c mergesort.c movieListData.c movieValueList.c hashTable.c columnsorter.c tokenizer.c scannerCSVsorter.c -o scannerCSVsorter

clean:
	rm -rf scannerCSVsorter
