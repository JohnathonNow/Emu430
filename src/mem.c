/********************************************************
 *                        mem.c                         *
 * Author:  John Westhoff                               *
 * Date:    07/25/2016                                  *
 *                                                      *
 * Contains functions for reading memory                *                                               
 *                                                      *
 */
#include "mem.h"
#include <stdio.h>

UINT8 get_status_c(INT16* REGS)
{
    return (REGS[STATUS_REG] >> STATUS_C_BIT) & 1;
}
UINT8 get_status_n(INT16* REGS)
{
    return (REGS[STATUS_REG] >> STATUS_N_BIT) & 1;
}
UINT8 get_status_v(INT16* REGS)
{
    return (REGS[STATUS_REG] >> STATUS_V_BIT) & 1;
}
UINT8 get_status_z(INT16* REGS)
{
    return (REGS[STATUS_REG] >> STATUS_Z_BIT) & 1;
}

void set_status_bits(INT16* REGS, UINT8 C, UINT8 Z, UINT8 N, UINT8 V)
{
    REGS[STATUS_REG] |= (~C_MASK) | (~Z_MASK) | (~N_MASK) | (~V_MASK);
    REGS[STATUS_REG] &= (C_MASK) | (C << STATUS_C_BIT);
    REGS[STATUS_REG] &= (Z_MASK) | (Z << STATUS_Z_BIT);
    REGS[STATUS_REG] &= (N_MASK) | (N << STATUS_N_BIT);
    REGS[STATUS_REG] &= (V_MASK) | (V << STATUS_V_BIT);
}

UINT8* read_mem(UINT8* MEM_SPACE, INT16* REGS, UINT16 ADDR, UINT16 READMODE, UINT16 BW)
{
    static UINT16 GENERATED_CONSTANTS[6] = {0, 1, 2, -1, 4, 8};
    
    UINT16 OPERAND_SIZE = (ADDR==STACK_POINTER || ADDR==PC_ADDRESS)?2:2-BW;

    if (ADDR == CONST_GENERATOR)
    {
        return (UINT8*)(GENERATED_CONSTANTS + READMODE);
    }
    if (ADDR == STATUS_REG)
    {
        if (READMODE > 1)
        {
            return (UINT8*)(GENERATED_CONSTANTS + READMODE + 2);
        }
        else
        {
            REGS[PC_ADDRESS] += 2;
            printf("\t%d\n", REGS[PC_ADDRESS] - 2);
            return MEM_SPACE + MEM_SPACE[ REGS[PC_ADDRESS]  - 2];
        }
    }

    switch (READMODE)
    {
        case 0:
            return (UINT8*)(REGS + ADDR);
        break;
        case 1:
            REGS[PC_ADDRESS] += 2;
            return MEM_SPACE + REGS[ADDR] + MEM_SPACE[REGS[PC_ADDRESS] - 2];
        break;
        case 2:
            return MEM_SPACE + REGS[ADDR];
        break;
        case 3:
            REGS[ADDR] += OPERAND_SIZE;
            return MEM_SPACE + REGS[ADDR] - OPERAND_SIZE;
        break;
    }
    return (UINT8*)0;
}
