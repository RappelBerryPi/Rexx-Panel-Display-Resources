#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <spc.h>

/*
 *https://www.ibm.com/docs/en/zos/2.4.0?topic=environments-host-command-environment-table#addrenv
 */

struct envblock { /* Environment Block */
	char envblock_id[8];
	char envblocK_version[4];
	int length;
	struct parmblock *envblock_parmblock;
	void *envblocK_userfield;
	void *envblocK_worKbloK_ext;
	struct irxexte *envblock_irxexte;
	void *error_call;
	char reserved[4];
	char error_msgid[8];
	char primary_error_message[80];
	char alternate_error_message[160];
	void *compgmtb;
	void *attnrout_parmptr;
	void *ectptr;
	int info_flags;
}*penvblock;

struct parmblock {
	char id[8];
	char version[4];
	char language[3];
	char reserved;
	void *modenamet;
	struct subcomtb *subcomtable;
	void *packtb;
	char parsetok[8];
	int flags;
	int masks;
	int subpool;
	char addrspn[8];
	char eob[8]; /* end of block */
} *pparmblock;

struct subcomtb {
	struct subcomEntry *firstEntry;
	int entries;
	int validEntries;
	int lengthofEntries;
	char initial[4];
	char reserved[8];
	char EOH[8];
} *psubcomtb;

struct subcomEntry {
	char name[8];
	char routine[8];
	char token[16];
} *psubcomEntry;

struct irxexte { /* External Entry Points */
	int irxexte_entry_count;
	void *irxinit;
	void *irxload;
	void * irxexcom;
	void *irxexec;
	void *irxinout;
	void *irxjcl;
	void *irxrlt;
	void *irxstk;
}*pirxexte;

int main(void) {
	/* execution code */
	/* get registers on entry */
	penvblock = (void*) edcxregs(0); /* GPR 0 */

	/* get VEEP */
	pirxexte = penvblock->envblock_irxexte;

	pparmblock = penvblock->envblock_parmblock;

	psubcomtb = pparmblock->subcomtable;

	psubcomEntry = psubcomtb->firstEntry;


	printf("%.8s\n",penvblock->envblock_id);

	printf("%.8s %.8s %.16s\n", psubcomEntry->name, psubcomEntry->routine,
			psubcomEntry->token);


	int i;
	for (i = 1; i < psubcomtb->entries; i++) {
		psubcomEntry = psubcomEntry + psubcomtb->lengthofEntries;
    	printf("'%8.8s' '%8.8s' '%16.16s'\n", psubcomEntry->name,
    			psubcomEntry->routine, psubcomEntry->token);
	}
	return 0;
}
