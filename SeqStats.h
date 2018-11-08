#ifndef DORON_SEQSTATS_H
#define DORON_SEQSTATS_H
#define MAX_NAME_LEN 256
typedef struct {
    char name[MAX_NAME_LEN];
    long length;
    int gc;
    int ns;
} SeqStat;

SeqStat* CreateSeqStats(char name[], char *seq);
void DestroySeqStats(SeqStat *seqStat);
void CopySeqStats(SeqStat *seqStat1, SeqStat *seqStat2);
void SwitchSeqStats(SeqStat *seqStat1, SeqStat *seqStat2);

#endif
