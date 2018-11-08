#ifndef DORON_SEQSTATSCONTAINER_H
#define DORON_SEQSTATSCONTAINER_H

#include <stdio.h>
#include "SeqStats.h"

typedef struct {
    SeqStat **seqStatArray;
    int numberOfSeq;
} SeqStatsContainer;


SeqStatsContainer* CreateSeqStatsContainer();
int AddSeqsToSeqStatsContainer(SeqStatsContainer* container, char *filename);
int NumSeqsInFile(FILE* fp);
int NumSeqsInSeqStatsContainer(SeqStatsContainer* container);
SeqStat* GetSeqStats(SeqStatsContainer* container, int index);
void PrintSeqStatContainer(SeqStatsContainer* container);

#endif
