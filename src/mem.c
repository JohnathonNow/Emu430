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

UINT8* read_mem(UINT8* MEM_SPACE, INT16* REGS, UINT16 ADDR, UINT16 READMODE, UINT16 BW)
{
    static UINT16 GENERATED_CONSTANTS[6] = {0, 1, 2, -1, 4, 8};
    
    UINT16 OPERAND_SIZE = ADDR==STACK_POINTER?1:2-BW;

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
