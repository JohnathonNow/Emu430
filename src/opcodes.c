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

/* The unconditional jump
 * 
 *  Modifies the PC
 *
 */
UINT16 jmp(UINT8* MEM_SPACE, INT16* REGS, tInstruction* exec)
{
    INT16 offset = exec->pc_offset;
    if (offset >> 9)
        offset |= 0xFC00; /* Sign extend if negative*/
    offset *= 2; /* Double for PC modification */
    REGS[PC_ADDRESS] += offset;
    return OP_SUCCESS;
}
/* Jump if not equal
 * 
 *  Modifies the PC
 *
 */
UINT16 jne(UINT8* MEM_SPACE, INT16* REGS, tInstruction* exec)
{
    if (!get_status_z(REGS))
        jmp(MEM_SPACE, REGS, exec);
    return OP_SUCCESS;
}
/* Jump if equal
 * 
 *  Modifies the PC
 *
 */
UINT16 jeq(UINT8* MEM_SPACE, INT16* REGS, tInstruction* exec)
{
    if (get_status_z(REGS))
        jmp(MEM_SPACE, REGS, exec);
    return OP_SUCCESS;
}
/* Jump if carry is 0
 * 
 *  Modifies the PC
 *
 */
UINT16 jnc(UINT8* MEM_SPACE, INT16* REGS, tInstruction* exec)
{
    if (!get_status_c(REGS))
        jmp(MEM_SPACE, REGS, exec);
    return OP_SUCCESS;
}
/* Jump if carry is 1
 * 
 *  Modifies the PC
 *
 */
UINT16 jc(UINT8* MEM_SPACE, INT16* REGS, tInstruction* exec)
{
    if (get_status_c(REGS))
        jmp(MEM_SPACE, REGS, exec);
    return OP_SUCCESS;
}
/* Jump if negative
 * 
 *  Modifies the PC
 *
 */
UINT16 jin(UINT8* MEM_SPACE, INT16* REGS, tInstruction* exec)
{
    if (get_status_n(REGS))
        jmp(MEM_SPACE, REGS, exec);
    return OP_SUCCESS;
}
/* Jump if n == v
 * 
 *  Modifies the PC
 *
 */
UINT16 jge(UINT8* MEM_SPACE, INT16* REGS, tInstruction* exec)
{
    if (get_status_n(REGS)==get_status_v(REGS))
        jmp(MEM_SPACE, REGS, exec);
    return OP_SUCCESS;
}
/* Jump if n != v
 * 
 *  Modifies the PC
 *
 */
UINT16 jl(UINT8* MEM_SPACE, INT16* REGS, tInstruction* exec)
{
    if (get_status_n(REGS)!=get_status_v(REGS))
        jmp(MEM_SPACE, REGS, exec);
    return OP_SUCCESS;
}

/* The cmp opcode
 * 
 *  Does D - S and sets the flags
 *  TODO: Add memory checks
 *
 */
UINT16 cmp(UINT8* MEM_SPACE, INT16* REGS, tInstruction* E)
{
    INT16* D = (INT16*)(read_mem(MEM_SPACE, REGS, E->dst_reg, E->ad, E->bw));
    INT16 OLD_D = *D;
    sub(MEM_SPACE, REGS, E); /* Do sub, to reuse code */
    *D = OLD_D; /* Restore old destination value */
    return OP_SUCCESS;
}
/* The sub opcode
 * 
 *  Essentially D -= S
 *  TODO: Add memory checks
 *  TODO: Consider just having sub call add
 *
 */
UINT16 sub(UINT8* MEM_SPACE, INT16* REGS, tInstruction* E)
{
    INT8* S = (INT8*)(read_mem(MEM_SPACE, REGS, E->src_reg, E->as, E->bw));
    INT8* D = (INT8*)(read_mem(MEM_SPACE, REGS, E->dst_reg, E->ad, E->bw));
    UINT16 OLD_D = *(UINT16*)D;
    UINT16 carry_bit = 8;
    UINT16 overflow_bit = 7;
    INT32 result = *((INT16*)D) - *((INT16*)S);
    printf("%d\n", result);
    UINT8  Z = 0;
    /* Test whether we are using byte operations or word operations */
    if (E->bw)
    {
        *D -= *S;
        Z = (*D == 0);
    }
    else
    {
        *((INT16*)D) -= *((INT16*)S);
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
/* The add opcode
 * 
 *  Essentially D += S
 *  TODO: Add memory checks
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
