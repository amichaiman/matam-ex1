#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "SeqStats.h"
#include "SeqStatsContainer.h"

int main(int argc, char **argv) {
    SeqStatsContainer* container = CreateSeqStatsContainer();

    if (argc != 2) {
        printf("expected: ./<application> <fasta filename>\n");
        exit(1);
    }

    if (AddSeqsToSeqStatsContainer(container, argv[1]) == -1){
        exit(2);
    }
    PrintSeqStatContainer(container);
}