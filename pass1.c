#include<stdio.h>
#include<string.h>
#include<stdlib.h> 
int main() {
    char mnemonics[10], operand[10], label[10], code[10], mnemo[10];
    int locctr, start, length;

    FILE *fp1, *fp2, *fp3, *fp4;

    fp1 = fopen("input.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("symtbl.txt", "w");
    fp4 = fopen("out.txt", "w");
 
    fscanf(fp1, "%s\t%s\t%s", label, mnemonics, operand);

    if(strcmp(mnemonics, "START")==0) {
        start = atoi(operand);
        locctr = start;
        fprintf(fp4, "\t%s\t%s\t%s\n", label, mnemonics, operand);
        fscanf(fp1, "%s\t%s\t%s", label, mnemonics, operand);
    }
    else {
        locctr = 0;
    }

    while(strcmp(mnemonics, "END")!=0) {
        fprintf(fp4, "%d\t", locctr);

        if(strcmp(label, "**")!=0) {
            fprintf(fp3, "%s\t%d\n", label, locctr);
        }

        fscanf(fp2, "%s\t%s", mnemo, code);

        while(strcmp(mnemo, "END")!=0) {
            if(strcmp(mnemonics, mnemo)==0) {
                locctr+=3;
                break;
            }
            fscanf(fp2, "%s\t%s", mnemo, code);
        }

        if(strcmp(mnemonics, "WORD")==0) {
            locctr+=3;
        }
        else if(strcmp(mnemonics, "RESW")==0) {
            locctr+=(3*(atoi(operand)));
        }
        else if(strcmp(mnemonics, "RESB")==0) {
            locctr+=(atoi(operand));
        }
        else if(strcmp(mnemonics, "BYTE")==0) {
            ++locctr;
        }

        fprintf(fp4, "%s\t%s\t%s\t\n", label, mnemonics, operand);
        fscanf(fp1, "%s\t%s\t%s", label, mnemonics, operand);
    }

    fprintf(fp4, "%d\t%s\t%s\t%s\n", locctr, label, mnemonics, operand);

    length = locctr-start;

    printf("The length of the code : %d\n", length);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
}
