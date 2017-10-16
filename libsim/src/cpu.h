/******************************************************************************
 *
 * Cpu
 *
 ******************************************************************************/

#ifndef __CPU_H__
#define __CPU_H__

#include <cstdio>
#include <cstdint>
#include <vector>
#include <string>

#include "register.h"
#include "memory.h"
#include "alu.h"
#include "tracer.h"

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6
#define R7 7
#define R8 8
#define R9 9
#define R10 10
#define R11 11
#define R12 12
#define SP 13
#define LR 14
#define PC 15


class Cpu
{
	private:
		Alu alu;
		Memory ram;
		Tracer tracer;
		unsigned long int instruction_count;

		std::string trace_index_filename;
		bool generate_trace_index;
		bool trace_index_done;
		FILE *trace_index_file;

		uint32_t generate_modified_immediate(uint16_t ins16, uint16_t ins16_b);
		uint32_t decode_imm_shift(unsigned int op, unsigned int imm, unsigned int s, uint32_t a);
		unsigned int conditional_branch(unsigned int cond, int32_t offset, bool is_ins32, unsigned int p_addr);

	public:
		Register regs[16];

		Cpu(std::string trace_index_filename = "");
		~Cpu();
		void reset(void);
		int load(const char *filename);
		void write_register(unsigned int reg_idx, uint32_t value);
		int step(void);
		unsigned long int run(unsigned int from, unsigned int until, unsigned long int limit = 0);

		void dump_memory(unsigned int start, unsigned int len);
		void dump_regs(void);

		void copy_array_to_target(uint32_t *buffer, unsigned int len, unsigned int target_addr);
		void copy_array_from_target(uint32_t *buffer, unsigned int len, unsigned int target_addr);

		void reset_pwr_trace(void);
		std::vector<unsigned int> get_pwr_trace(void);
};

#endif
