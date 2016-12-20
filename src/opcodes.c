/********************************************************
 *                       opcodes.c                      *
 * Author:  John Westhoff                               *
 * Date:    07/21/2016                                  *
 *                                                      *
 * Contains code for opcode functions, which will be    *
 * called based off of the opcodes read from memory     *
 *                                                      *
 * TODO: Add all opcodes and branch instructions        *
 */
#include "opcodes.h"
#include "mem.h"
#include <stdio.h>
/* The sub opcode
 * 
 *  Essentially D -= S
 *  TODO: Add memory checks
 *  TODO: Set flags
 *
 */
UINT16 sub(UINT8* MEM_SPACE, INT16* REGS, tInstruction* E)
{
    INT8* S = (INT8*)(read_mem(MEM_SPACE, REGS, E->src_reg, E->as, E->bw));
    INT8* D = (INT8*)(read_mem(MEM_SPACE, REGS, E->dst_reg, E->ad, E->bw));
    /* Test whether we are using byte operations or word operations */
    if (E->bw)
    {
        *D -= *S;
    }
    else
    {
        *((INT16*)D) -= *((INT16*)S);
    }
    return OP_SUCCESS;
}
/* The add opcode
 * 
 *  Essentially D += S
 *  TODO: Add memory checks
 *  TODO: Set flags
 *
 */
UINT16 add(UINT8* MEM_SPACE, INT16* REGS, tInstruction* E)
{
    INT8* S = (INT8*)(read_mem(MEM_SPACE, REGS, E->src_reg, E->as, E->bw));
    INT8* D = (INT8*)(read_mem(MEM_SPACE, REGS, E->dst_reg, E->ad, E->bw));
    UINT16 OLD_D = *(UINT16*)D;
    UINT16 carry_bit = 8;
    UINT16 overflow_bit = 7;
    UINT32 result = *((UINT16*)D) + *((UINT16*)S);
    printf("%d\n", result);
    UINT8  Z = 0;
    /* Test whether we are using byte operations or word operations */
    if (E->bw)
    {
        *D += *S;
        Z = (*D == 0);
    }
    else
    {
        *((INT16*)D) += *((INT16*)S);
        Z = (*((INT16*)D) == 0);
        carry_bit = 16;
        overflow_bit = 15;
    }
    /* Test for overflow */
    UINT16 OF_MASK = (1<<overflow_bit);
    UINT16 OF = ((result & OF_MASK) != (*((INT16*)S) & OF_MASK)) &
                ((OLD_D & OF_MASK) == (*((INT16*)S) & OF_MASK));
    /* Set the status register bits */
    set_status_bits((REGS),
                    (result & (1<<carry_bit))>>carry_bit,
                    (Z),
                    (result & (1<<overflow_bit))>>overflow_bit,
                    (OF));
    
    return OP_SUCCESS;
}

/* The mov opcode
 * 
 *  Essentially D = S
 *  TODO: Add memory checks
 *
 */
UINT16 mov(UINT8* MEM_SPACE, INT16* REGS, tInstruction* E)
{
    /* Test whether we are using byte operations or word operations */
    if (E->bw)
    {
        INT8* S = (INT8*)(read_mem(MEM_SPACE, REGS, E->src_reg, E->as, E->bw));
        INT8* D = (INT8*)(read_mem(MEM_SPACE, REGS, E->dst_reg, E->ad, E->bw));
        *D = *S;
    }
    else
    {
        INT16* S = (INT16*)(read_mem(MEM_SPACE, REGS, E->src_reg, E->as, E->bw));
        INT16* D = (INT16*)(read_mem(MEM_SPACE, REGS, E->dst_reg, E->ad, E->bw));
        *D = *S;
    }
    return OP_SUCCESS;
}

/* The nop opcode
 *
 *  ... does nothing...
 *
 *
 */
UINT16 nop(UINT8* MEM_SPACE, INT16* REGS, tInstruction* E)
{

    return OP_SUCCESS;
}
