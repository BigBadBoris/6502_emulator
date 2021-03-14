#ifndef CPU_H_
#define CPU_H_


#include <stdint.h>
#include <stdbool.h>

#include "util.h"

/*
 * Status Flags
 */
#define STAT_NEG		BIT(7)	/* negative status flag */
#define STAT_OVERFLOW		BIT(6)	/* overflow flag */
/* BIT(5) unused */
#define STAT_BREAK		BIT(4)	/* set if irq triggered by BRK */
#define STAT_DECIMAL		BIT(3)	/* decimal mode set */
#define STAT_IRQ_DISABLE	BIT(2)	/* disables irq when set */
#define STAT_ZERO		BIT(1)	/* set if result is zero */
#define STAT_CARRY		BIT(0)	/* set if overflow occurred */

struct Cpu;

typedef struct Cpu Cpu;
typedef void (*const op_ptr) (Cpu *, uint16_t);
typedef uint16_t (*const addr_op) (Cpu *);


struct Cpu {
	/* registers */
	uint8_t acc; 		/* accumulator */
	uint8_t x_reg;		/* x register */
	uint8_t y_reg;		/* y register */
	uint8_t stack_ptr;	/* stack pointer */
	uint8_t status;		/* status register */
	uint16_t pc;		/* program counter */
	/* memory functions */
	uint8_t (*const mem_read) (uint16_t addr);
	void (*const mem_write) (uint16_t addr, uint8_t value);
	
	/* Instruction Jump Table */
	op_ptr op_table[MAX_UINT8_T];
	addr_op addr_table[MAX_UINT8_T];
};


/*
 * Cpu Status Functions
 */

inline void cpu_set_status_bit(Cpu * cpu, uint8_t bit, uint8_t value ){
	cpu->status ^= (-(!!value) ^ cpu->status) & (1 << bit);
}

inline bool cpu_is_status_bit_set(Cpu * cpu, uint8_t status_bit){
	return (cpu->status & status_bit);
}

/*
 * Address Modes
 */
uint16_t addr_accumulator(Cpu * cpu);

uint16_t addr_immediate(Cpu * cpu);

uint16_t addr_absolute(Cpu * cpu);

uint16_t addr_zero(Cpu * cpu);

uint16_t 


/* 
 * CPU OP Instructions 
 */

/* Add with carry */
void op_adc(Cpu * cpu, uint16_t arg);

/* Logical AND */
void op_and(Cpu * cpu, uint16_t arg);

/* Arithmetic shift left */
void op_asl(Cpu * cpu, uint16_t arg);

/* Branch if carry clear */
void op_bcc(Cpu * cpu, uint16_t arg);

/* Branch if carry set */
void op_bcs(Cpu * cpu, uint16_t arg);

/* Branch if result = 0 */
void op_beq(Cpu * cpu, uint16_t arg);

/* Test bit */
void op_bit(Cpu * cpu, uint16_t arg);

/* Branch if minus */
void op_bmi(Cpu * cpu, uint16_t arg);

/* Branch if not equal to 0 */
void op_bne(Cpu * cpu, uint16_t arg);

/* Branch if plus */
void op_bpl(Cpu * cpu, uint16_t arg);

/* Break */
void op_brk(Cpu * cpu, uint16_t arg);

/* Branch if overflow clear */
void op_bvc(Cpu * cpu, uint16_t arg);

/* Branch if overflow set */
void op_bvs(Cpu * cpu, uint16_t arg);

/* Clear carry status flag */
void op_clc(Cpu * cpu, uint16_t arg);

/* Clear decimal status flag */
void op_cld(Cpu * cpu, uint16_t arg);

/* Clear interrupt disable */
void op_cli(Cpu * cpu, uint16_t arg);

/* Clear overflow */
void op_clv(Cpu * cpu, uint16_t arg);

/* Compare to Accumulator */
void op_cmp(Cpu * cpu, uint16_t arg);

/* Compare to register X */
void op_cpx(Cpu * cpu, uint16_t arg);

/* Compare to register Y */
void op_cpy(Cpu * cpu, uint16_t arg);

/* decrement memory */
void op_dec(Cpu * cpu, uint16_t arg);

/* decrement X */
void op_dex(Cpu * cpu, uint16_t arg);

/* decrement Y */
void op_dey(Cpu * cpu, uint16_t arg);

/* Exclusive OR */
void op_eor(Cpu * cpu, uint16_t arg);

/* Increment memory */
void op_inc(Cpu * cpu, uint16_t arg);

/* Increment x */
void op_inx(Cpu * cpu, uint16_t arg);

/* Increment y */
void op_iny(Cpu * cpu, uint16_t arg);

/* Jump */
void op_jmp(Cpu * cpu, uint16_t arg);

/* Jump to subroutine */
void op_jsr(Cpu * cpu, uint16_t arg);

/* Load accumulator */
void op_lda(Cpu * cpu, uint16_t arg);

/* Load X */
void op_ldx(Cpu * cpu, uint16_t arg);

/* Load Y */
void op_ldy(Cpu * cpu, uint16_t arg);

/* Logical Shift Right */
void op_lsr(Cpu * cpu, uint16_t arg);

/* No Operation */
void op_nop(Cpu * cpu, uint16_t arg);

/* Logical OR */
void op_ora(Cpu * cpu, uint16_t arg);

/* push A */
void op_pha(Cpu * cpu, uint16_t arg);

/* push P status */
void op_php(Cpu * cpu, uint16_t arg);

/* pull A */
void op_pla(Cpu * cpu, uint16_t arg);

/* pull P status */
void op_plp(Cpu * cpu, uint16_t arg);

/* rotate left */
void op_rol(Cpu * cpu, uint16_t arg);

/* rotate right */
void op_ror(Cpu * cpu, uint16_t arg);

/* Return from interrupt */
void op_rti(Cpu * cpu, uint16_t arg);

/* Return from subroutine */
void op_rts(Cpu * cpu, uint16_t arg);

/* Subtract with carry */
void op_sbc(Cpu * cpu, uint16_t arg);

/* set carry */
void op_sec(Cpu * cpu, uint16_t arg);

/* set decimal */
void op_sed(Cpu * cpu, uint16_t arg);

/* set interrupt disable */
void op_sei(Cpu * cpu, uint16_t arg);

/* store accumulator */
void op_sta(Cpu * cpu, uint16_t arg);

/* store X */
void op_stx(Cpu * cpu, uint16_t arg);

/* store Y */
void op_sty(Cpu * cpu, uint16_t arg);

/* Transfer A to X */
void op_tax(Cpu * cpu, uint16_t arg);

/* Transfer A to Y */
void op_tay(Cpu * cpu, uint16_t arg);

/* Transfer SP to X */
void op_tsx(Cpu * cpu, uint16_t arg);

/* Transfer X to A */
void op_txa(Cpu * cpu, uint16_t arg);

/* Transfer X to SP */
void op_txs(Cpu * cpu, uint16_t arg);

/* Transfer Y to A */
void op_tya(Cpu * cpu, uint16_t arg);


#endif	/* CPU_H_ */
