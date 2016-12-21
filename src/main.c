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

    OPS[ 8] = jne;
    OPS[ 9] = jeq;
    OPS[10] = jnc;
    OPS[11] = jc;
    OPS[12] = jin;
    OPS[13] = jge;
    OPS[14] = jl;
    OPS[15] = jmp;
    OPS[20] = mov;
    OPS[21] = add;
    OPS[24] = sub;
    
    REGISTERS[PC_ADDRESS] = MIN_CODE_ADDRESS;

    /* Read in memory from stdin */
    for (i = 0; i < MAX_MEMORY_ADDRESS / 2; i++)
    {
        UINT32 in;
        scanf("%X", &in);
        WORD_POINTER[i] = (UINT16)in;
    }

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
            translated.opcode    = ( ( instruction >> MEDIUM_OPCODE_SHIFT )    & MEDIUM_OPCODE_MASK ) | 0x08;
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
        printf("PC: %d  OP: %d\n", REGISTERS[PC_ADDRESS], translated.opcode);
        printf("STATUS: %d\n", REGISTERS[STATUS_REG]);
        REGISTERS[PC_ADDRESS] += 2;
        OPS[translated.opcode] ( MEMORY_SPACE, REGISTERS, &translated );
    }

    return EXIT_SUCCESS;
}
