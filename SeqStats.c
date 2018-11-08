#include <stdlib.h>
#include <string.h>
#include "SeqStats.h"

SeqStat *CreateSeqStats(char *name, char *seq) {
    int i;
    SeqStat *s = (SeqStat*) malloc (sizeof(SeqStat));

    strcpy(s->name, name);
    s->length = strlen(seq);

    s->gc = 0;
    s->ns = 0;

    for(i=0; i<s->length; i++){
        if (seq[i] == 'G' || seq[i] == 'C'  ){
            s->gc++;
        } else if (seq[i] == 'N'){
            s->ns++;
        } else if (seq[i] == '\n'){
            s->length--;
        }
    }

    return s;
}

void DestroySeqStats(SeqStat *seqStat) {
    free(seqStat);
}

void CopySeqStats(SeqStat *seqStat1, SeqStat *seqStat2) {
    *seqStat1 = *seqStat2;
}

void SwitchSeqStats(SeqStat *seqStat1, SeqStat *seqStat2) {
    SeqStat temp = *seqStat1;
    *seqStat1 = *seqStat2;
    *seqStat2 = temp;
}
