/********************************************************
 *                       main.c                         *
 * Author:  John Westhoff                               *
 * Date:    07/21/2016                                  *
 *                                                      *
 * The main application function, which initializes the *
 * memory and emulates the processor                    *
 *                                                      *
 */
#include <stdio.h>

#include "mem.h"
#include "opcodes.h"

int main()
{
    /* Define the processor memory space */
    UINT8 MEMORY_SPACE[MAX_MEMORY_ADDRESS] = {0};
    /* Define a pointer for the memory space on a word-level */
    UINT16* WORD_POINTER = (UINT16*)MEMORY_SPACE;
    /* Define the processor register array */
    INT16 REGISTERS[REGISTER_COUNT] = {0};
    /* Define the opcode translation array */
    UINT16 ( *OPS[MAX_OPCODE] ) ( UINT8* MEM_SPACE, INT16* REGS, tInstruction* E );
    
    /* Initialize op code translation array */
    int i;
    for (i = 0; i < MAX_OPCODE; i++)
    {
        OPS[i] = nop;
    }
    OPS[20] = mov;
    OPS[21] = add;
    
    /* For testing, just give us some memory */
    REGISTERS[PC_ADDRESS] = 18;
    WORD_POINTER[5] = 0x13A4;
    WORD_POINTER[6] = 0x2748;
    WORD_POINTER[7] = 0x9979;
    WORD_POINTER[8] = 1;
    WORD_POINTER[9] = 0x5292;
    WORD_POINTER[10] = 100;
    WORD_POINTER[11] = 102;
    WORD_POINTER[12] = 0x5335; //F2
    WORD_POINTER[13] = 0x5335;
    WORD_POINTER[14] = 0x5335;
    WORD_POINTER[15] = 0x53E2;
    WORD_POINTER[16] = 104;
    WORD_POINTER[50] = 1200;
    WORD_POINTER[51] = 1600;

    /* Advance the PC until we are out of bounds */ 
    while ( REGISTERS[PC_ADDRESS] <= MAX_CODE_ADDRESS && REGISTERS[PC_ADDRESS] >= MIN_CODE_ADDRESS )
    {
        UINT16 instruction = WORD_POINTER[REGISTERS[PC_ADDRESS]/2];
        tInstruction translated;
        /* Determine the length of this instruction */
        if ( ( ( instruction >> SHORT_INSTRUCTION_SHIFT ) ^ SHORT_INSTRUCTION_MASK ) == 0x7 )
        {  /* SHORT */
            translated.opcode  = ( instruction >> SHORT_OPCODE_SHIFT ) & SHORT_OPCODE_MASK;
            translated.bw      = ( instruction >> SHORT_BW_SHIFT )     & SHORT_BW_MASK;
            translated.ad      = ( instruction >> SHORT_AD_SHIFT )     & SHORT_AD_MASK;
            translated.dst_reg = ( instruction >> SHORT_DSTREG_SHIFT ) & SHORT_DSTREG_MASK;
        }
        else if ( ( ( instruction >> MEDIUM_INSTRUCTION_SHIFT ) ^ MEDIUM_INSTRUCTION_MASK ) == 0x7 )
        {  /* MEDIUM */
            translated.opcode    = ( instruction >> MEDIUM_OPCODE_SHIFT )    & MEDIUM_OPCODE_MASK;
            translated.pc_offset = ( instruction >> MEDIUM_PC_OFFSET_SHIFT ) & MEDIUM_PC_OFFSET_MASK;
        }
        else
        {  /* LONG */
            /* For the opcode, we set the first bit to 1 so that it is unique from the medium and short instructions */
            translated.opcode  = ( ( instruction >> LONG_OPCODE_SHIFT ) & LONG_OPCODE_MASK ) | 0x10;
            translated.bw      =   ( instruction >> LONG_BW_SHIFT )     & LONG_BW_MASK;
            translated.ad      =   ( instruction >> LONG_AD_SHIFT )     & LONG_AD_MASK;
            translated.dst_reg =   ( instruction >> LONG_DSTREG_SHIFT ) & LONG_DSTREG_MASK;
            translated.as      =   ( instruction >> LONG_AS_SHIFT )     & LONG_AS_MASK;
            translated.src_reg =   ( instruction >> LONG_SRCREG_SHIFT ) & LONG_SRCREG_MASK;
        }
        printf("%d  %d\n", REGISTERS[PC_ADDRESS], translated.opcode);
        REGISTERS[PC_ADDRESS] += 2;
        OPS[translated.opcode] ( MEMORY_SPACE, REGISTERS, &translated );
    }
    printf("%d\t%d\t%d\n", WORD_POINTER[51], REGISTERS[5], WORD_POINTER[52]);

    return EXIT_SUCCESS;
}
