#ifndef AUDIO_H_
#define AUDIO_H_

#define SWAP(X, Y)    \
    do                \
    {                 \
        int temp = X; \
        X = Y;        \
        Y = temp;     \
    } while (0)
#define MIN(a, b) ((a) > (b) ? (b) : (a))

#define audio_ptr (volatile unsigned int *)(virtual_base + ((0xFF203040) & (HW_REGS_MASK)))

// phase accumulator
// drum-specific multiply macros simulated by shifts
#define times0pt5(a) ((a) >> 1)
#define times0pt25(a) ((a) >> 2)
#define times2pt0(a) ((a) << 1)
#define times4pt0(a) ((a) << 2)
#define times0pt9998(a) ((a) - ((a) >> 12))  //>>10
#define times0pt9999(a) ((a) - ((a) >> 13))  //>>10
#define times0pt99999(a) ((a) - ((a) >> 16)) //>>10
#define times0pt999(a) ((a) - ((a) >> 10))   //>>10
#define times_rho(a) (((a) >> 4))            //>>2

// fixed pt macros suitable for 32-bit sound
typedef signed int fix28;
// multiply two fixed 4:28
#define multfix28(a, b) ((fix28)((((signed long long)(a)) * ((signed long long)(b))) >> 28))
//#define multfix28(a,b) ((fix28)((( ((short)((a)>>17)) * ((short)((b)>>17)) ))))
#define float2fix28(a) ((fix28)((a)*268435456.0f)) // 2^28
#define fix2float28(a) ((float)(a) / 268435456.0f)
#define int2fix28(a) ((a) << 28)
#define fix2int28(a) ((a) >> 28)
// shift fraction to 32-bit sound
#define fix2audio28(a) (a << 4)

#define FOURfix28 0x40000000
#define SIXTEENTHfix28 0x01000000
#define ONEfix28 0x10000000
#define two32 4294967296

#define string_size 20
#define string_out 5
#define string_pluck 15

void play();

#endif