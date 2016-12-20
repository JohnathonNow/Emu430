/********************************************************
 *                        mem.h                         *
 * Author:  John Westhoff                               *
 * Date:    07/21/2016                                  *
 *                                                      *
 * Contains macro defintions for the different areas of *
 * memory                                               *
 *                                                      *
 */
#ifndef MEM_HEADER
#define MEM_HEADER
    #define MAX_MEMORY_ADDRESS (240)

    #define REGISTER_COUNT  (16)
    #define PC_ADDRESS      (0)
    #define STACK_POINTER   (1)
    #define STATUS_REG      (2)
    #define CONST_GENERATOR (3)

    #define STATUS_C_BIT (0)
    #define STATUS_Z_BIT (1)
    #define STATUS_N_BIT (2)
    #define STATUS_V_BIT (8)

    #define C_MASK (0xFFFE)
    #define Z_MASK (0xFFFD)
    #define N_MASK (0xFFFB)
    #define V_MASK (0xFEFF)

    #define MIN_CODE_ADDRESS (2)
    #define MAX_CODE_ADDRESS (32)

    #define MIN_RAM_ADDRESS (29)
    #define MAX_RAM_ADDRESS (MAX_MEMORY_ADDRESS)

    #define ALL_ONES (0xFFFF)


    #define EXIT_SUCCESS 0    
    
    typedef unsigned int   UINT32;
    typedef unsigned short UINT16;
    typedef unsigned char  UINT8;

    typedef signed int   INT32;
    typedef signed short INT16;
    typedef signed char  INT8;


    UINT8* read_mem(UINT8* MEM_SPACE, INT16* REGS, UINT16 ADDR, UINT16 READMODE, UINT16 BW);

    void set_status_bits(INT16* REGS, UINT8 C, UINT8 Z, UINT8 N, UINT8 V);


    
    #if MIN_CODE_ADDRESS > MAX_CODE_ADDRESS
        #error Minimum code address must be <= maximum code address
    #endif


#endif
