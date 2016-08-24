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
    /* Test whether we are using byte operations or word operations */
    if (E->bw)
    {
        INT8* S = (INT8*)(read_mem(MEM_SPACE, REGS, E->src_reg, E->as, E->bw));
        INT8* D = (INT8*)(read_mem(MEM_SPACE, REGS, E->dst_reg, E->ad, E->bw));
        *D -= *S;
    }
    else
    {
        INT16* S = (INT16*)(read_mem(MEM_SPACE, REGS, E->src_reg, E->as, E->bw));
        INT16* D = (INT16*)(read_mem(MEM_SPACE, REGS, E->dst_reg, E->ad, E->bw));
        *D -= *S;
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
    /* Test whether we are using byte operations or word operations */
    if (E->bw)
    {
        INT8* S = (INT8*)(read_mem(MEM_SPACE, REGS, E->src_reg, E->as, E->bw));
        INT8* D = (INT8*)(read_mem(MEM_SPACE, REGS, E->dst_reg, E->ad, E->bw));
        *D += *S;
    }
    else
    {
        INT16* S = (INT16*)(read_mem(MEM_SPACE, REGS, E->src_reg, E->as, E->bw));
        INT16* D = (INT16*)(read_mem(MEM_SPACE, REGS, E->dst_reg, E->ad, E->bw));
        *D += *S;
    }
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
