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

    #define MIN_CODE_ADDRESS (2)
    #define MAX_CODE_ADDRESS (32)

    #define MIN_RAM_ADDRESS (29)
    #define MAX_RAM_ADDRESS (MAX_MEMORY_ADDRESS)


    #define EXIT_SUCCESS 0    
    typedef unsigned short UINT16;
    typedef unsigned char  UINT8;

    typedef signed short INT16;
    typedef signed char  INT8;

    UINT8* read_mem(UINT8* MEM_SPACE, INT16* REGS, UINT16 ADDR, UINT16 READMODE, UINT16 BW);


    
    #if MIN_CODE_ADDRESS > MAX_CODE_ADDRESS
        #error Minimum code address must be <= maximum code address
    #endif


#endif
