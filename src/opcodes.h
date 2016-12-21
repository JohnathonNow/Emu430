/********************************************************
 *                       opcodes.h                      *
 * Author:  John Westhoff                               *
 * Date:    07/21/2016                                  *
 *                                                      *
 * Contains declarations  for opcode functions, which   *
 * will be called based off of the opcodes read from    *
 * memory                                               *
 *                                                      *
 */
#ifndef OPCODES_HEADER
#define OPCODES_HEADER
    #define OP_SUCCESS 0
    #define OP_D_OUT_OF_BOUNDS 1
    #define OP_S_OUT_OF_BOUNDS 2

    #define MAX_OPCODE 32

    #include "mem.h"

   /* Macros for identifying which of the three
    * instruction formats we are seeing
    */ 
    #define SHORT_INSTRUCTION_SHIFT  (13)
    #define SHORT_INSTRUCTION_MASK   (0x7)
    #define MEDIUM_INSTRUCTION_SHIFT (13)
    #define MEDIUM_INSTRUCTION_MASK  (0x6)

   /* Macros for identifying components of a
    * short instruction
    */
    #define SHORT_OPCODE_SHIFT       (7) 
    #define SHORT_OPCODE_MASK        (0x7)
    #define SHORT_BW_SHIFT           (6)
    #define SHORT_BW_MASK            (0x1)
    #define SHORT_AD_SHIFT           (4)
    #define SHORT_AD_MASK            (0x3)
    #define SHORT_DSTREG_SHIFT       (0)
    #define SHORT_DSTREG_MASK        (0xF)
   /* Macros for identifying components of a
    * medium instruction
    */
    #define MEDIUM_OPCODE_SHIFT       (10) 
    #define MEDIUM_OPCODE_MASK        (0x7)
    #define MEDIUM_PC_OFFSET_SHIFT    (0)
    #define MEDIUM_PC_OFFSET_MASK     (0x3FF)
   /* Macros for identifying components of a
    * long instruction
    */
    #define LONG_OPCODE_SHIFT         (12)
    #define LONG_OPCODE_MASK          (0xF)
    #define LONG_SRCREG_SHIFT         (8) 
    #define LONG_SRCREG_MASK          (0xF)
    #define LONG_AD_SHIFT             (7)
    #define LONG_AD_MASK              (0x1)
    #define LONG_BW_SHIFT             (6)
    #define LONG_BW_MASK              (0x1)
    #define LONG_AS_SHIFT             (4)
    #define LONG_AS_MASK              (0x3)
    #define LONG_DSTREG_SHIFT         (0)
    #define LONG_DSTREG_MASK          (0xF)

    /* Struct for  breaking apart pieces of
     * an instruction
     */
    typedef struct Instruction
    {
        UINT16 opcode    :  5;
        UINT16 bw        :  1;
        UINT16 ad        :  2;
        UINT16 dst_reg   :  4;
         INT16 pc_offset : 10;
        UINT16 as        :  2;
        UINT16 src_reg   :  4; 
    } tInstruction;

    UINT16 add(UINT8* MEM_SPACE, INT16* REGS, tInstruction* exec);
    UINT16 sub(UINT8* MEM_SPACE, INT16* REGS, tInstruction* exec);
    UINT16 mov(UINT8* MEM_SPACE, INT16* REGS, tInstruction* exec);
    UINT16 nop(UINT8* MEM_SPACE, INT16* REGS, tInstruction* exec);

    UINT16 jne(UINT8* MEM_SPACE, INT16* REGS, tInstruction* exec);
    UINT16 jeq(UINT8* MEM_SPACE, INT16* REGS, tInstruction* exec);
    UINT16 jnc(UINT8* MEM_SPACE, INT16* REGS, tInstruction* exec);
    UINT16 jc(UINT8* MEM_SPACE, INT16* REGS, tInstruction* exec);
    UINT16 jin(UINT8* MEM_SPACE, INT16* REGS, tInstruction* exec);
    UINT16 jge(UINT8* MEM_SPACE, INT16* REGS, tInstruction* exec);
    UINT16 jl(UINT8* MEM_SPACE, INT16* REGS, tInstruction* exec);
    UINT16 jmp(UINT8* MEM_SPACE, INT16* REGS, tInstruction* exec);
    
    
#endif
