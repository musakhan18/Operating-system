#include<stdio.h>

int main()
{
printf("Hello!, This program is going to clear carry flag.\n"); asm("clc;"); /* clear the carry flag using inline assembly */

printf("Carry flag cleared!\n");

printf("This program is attempting to disable interrupts using CLI (Clear Interrupt Flag) instruction.\n");

printf("If	you	see	segmentation	fault,	process	is trapped.\n\n\n");

asm("cli;"); /* inline assembly instruction to clear interrupt flag */

printf("\nInterrupts disbled!!!"); return 0;
}

