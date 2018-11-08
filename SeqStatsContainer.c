#include <stdlib.h>
#include "SeqStatsContainer.h"
#include "SeqStats.h"

long getNumberOfBps(SeqStatsContainer *container);

void goToNextSeq(FILE* fp){
    while (fgetc(fp) != '>');
}
void goToNextLine(FILE *fp) {
    while (fgetc(fp) != '\n');
}
long getSeqLen(FILE *fp) {
    long len = 0;
    char c;
    int flag = 0;

    while ((c = (char) fgetc(fp)) != EOF){
        len++;
        if (flag == 1){
            if (c == '\n'){
                break;
            } else {
                flag = 0;
            }
        }
        if(c == '\n'){
            flag = 1;
        }
    }
    fseek(fp, -len, SEEK_CUR);
    return len;
}
void readSeq(char *buffer, long len, FILE *fp) {
    long i;
    for (i=0; i<len; i++){
        buffer[i] = (char) fgetc(fp);
    }
}



SeqStatsContainer *CreateSeqStatsContainer() {
    SeqStatsContainer *container = (SeqStatsContainer*) malloc(sizeof(SeqStatsContainer));
    return container;
}

int AddSeqsToSeqStatsContainer(SeqStatsContainer *container, char *filename) {
    char name[MAX_NAME_LEN];
    long seqLen;
    char* buffer;
    int i;
    FILE* fp = fopen(filename, "r");

    if (!fp) {
        printf("ERROR: couldn't open file \"%s\"\n", filename);
        return -1;
    }

    container->numberOfSeq = NumSeqsInFile(fp);
    container->seqStatArray = (SeqStat **) malloc (container->numberOfSeq * sizeof(SeqStat*));

    /* go to beginning of file */
    rewind(fp);

    for(i=0; i<container->numberOfSeq; i++){
        /* go to next seq   */
        goToNextSeq(fp);

        /* read name */
        fscanf(fp, "%s", name);
        goToNextLine(fp);

        /* fill buffer with gene sequence */
        seqLen = getSeqLen(fp);
        buffer = (char*) malloc(seqLen* sizeof(char));
        readSeq(buffer, seqLen, fp);
        /* add SeqStats struct to object array */
        container->seqStatArray[i] = CreateSeqStats(name, buffer);
    }

    return container->numberOfSeq;
}

int NumSeqsInFile(FILE *fp) {
    rewind(fp);
    int n = 0;
    char c;
    c = (char) fgetc(fp);
    while (c != EOF){
        if (c == '>'){
            n++;
        }
        c = (char) fgetc(fp);
    }
    rewind(fp);
    return n;
}

int NumSeqsInSeqStatsContainer(SeqStatsContainer *container) {
    return container->numberOfSeq;
}

SeqStat *GetSeqStats(SeqStatsContainer *container, int index) {
    if (index < 0 || index >container->numberOfSeq){
        printf("ERROR: Invalid index");
        return NULL;
    }

    return container->seqStatArray[index];
}
#define GET_GC_PERCENTAGE(gc,len) \
        (100*(float)(gc)/(len))

void PrintSeqStatContainer(SeqStatsContainer *container) {
    int i;
    getNumberOfBps(container);
    printf("Number of sequences: %d\n", container->numberOfSeq);
    printf("Number of bps:       %ld\n\n",getNumberOfBps(container));
    printf("#\tSeq\tLength\t/G+C\tNs\n");
    for (i=0; i<container->numberOfSeq; i++){
        /* get current seqStats in array */
        SeqStat* curSeqStat = GetSeqStats(container,i);

        printf("%d\t%s\t%ld\t%.1f\t%d\n", i+1, curSeqStat->name, curSeqStat->length,
               GET_GC_PERCENTAGE(curSeqStat->gc,curSeqStat->length), curSeqStat->ns);
    }
}

long getNumberOfBps(SeqStatsContainer *container) {
    long n = 0;
    int i;
    for(i=0; i<container->numberOfSeq; i++){
        n += GetSeqStats(container,i)->length;
    }
    return n;
}



