//Lawrence Chas Kane LA978453

#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero){
    if(!ALUresult || !Zero) return;
    switch (ALUControl) {
        case 0:
            *ALUresult = A + B;
            if(!*ALUresult) *Zero = 1;
            break;
        
        case 1:
            *ALUresult = A - B;
            if(!*ALUresult) *Zero = 1;
            break;
        
        case 2:
            if(A < B) *ALUresult = 1;
            else      *ALUresult = 0;
            if(!*ALUresult) *Zero = 1;
            break;
            
        case 3:
            
            if(!*ALUresult) *Zero = 1;
            break;
            
        case 4:
            
            if(!*ALUresult) *Zero = 1;
            break;
            
        case 5:
            
            if(!*ALUresult) *Zero = 1;
            break;
            
        case 6:
            
            if(!*ALUresult) *Zero = 1;
            break;
            
        case 7:
            
            if(!*ALUresult) *Zero = 1;
            break;
            
        default:
            Halt = 1;
            break;
    }
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
	// Return 1 to triiger HALT if the address being fetched is not word-alligned (a multiple of 4).
	if(PC % 4 != 0)
		return 1;

	//	Fetch the instruction stored in Mem array at the address of PC and write (store) it in the instruction pointer. Return 0.
	*instruction = Mem[PC >> 2];
	return 0;
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
	// op = insruction ANDed with 0xFC000000, shifted right by 26 units.
	// 0xFC000000 = 1111 1100 0000 0000 0000 0000 0000 0000.
	*op = (instruction & 0xFC000000) >> 26;

	// r1 = instruction ANDed with 0x03C00000, shifted right by 21 units.
	// 0x03C00000 = 0000 0011 1110 0000 0000 0000 0000 0000.
	*r1 = (instruction & 0x03C00000)  >> 21;

	// r2 = instruction ANDed with 0x001F0000, shifted right by 16 units.
	// 0x001F0000 = 0000 0000 0001 1111 0000 0000 0000 0000.
	*r2 = (instruction & 0x001F0000) >> 16;

	// r3 = instruction ANDed with 0x0000F800, shifted right 11 units.
	// 0x0000F800 = 0000 0000 0000 0000 1111 1000 0000 0000.
	*r3 = (instruction & 0x0000F800) >> 11;

	// funct = instruction ANDed with 0x0000003F, no shift.
	// 0x0000003F = 0000 0000 0000 0000 0000 0000 0011 1111.
	*funct = instruction & 0x0000003F;

	// offset = instruction ANDed with 0x0000FFFF, no shift.
	// 0x0000FFFF = 0000 0000 0000 0000 1111 1111 1111 1111.
	*offset = instruction & 0x0000FFFF;

	// jsec = instruction ANDed with 0x03FFFFFF, no shift.
	// 0x03FFFFFF = 0000 0011 1111 1111 1111 1111 1111 1111.
	*jsec = instruction & 0x03FFFFFF;
}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
	// 1) Decode the instruction using the op code.
	// 2) Assign the values of the control signals to the variables in the structure controls.
	// 3) Return 1 if a halt condition occurs; otherwise, return 0. 

	// If the op code is 0, then it's an r-type instruction.
	if(op == 0b00000000){
		controls->RegDst = 1;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 7;
		controls->MemWrite = 0;
		controls->ALUSrc = 0;
		controls->RegWrite = 1;
		return 0;
	}

	// If the op code is 2, then it's for a jump.
	else if(op == 0b00000010){
		controls->RegDst = 1;
		controls->Jump = 1;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 0;
		controls->MemWrite = 0;
		controls->ALUSrc = 0;
		controls->RegWrite = 0;
		return 0;
	}

	// If the op code is 4, then it's for branch if equal (beq).
	else if(op == 0b00000100){
		controls->RegDst = 2;
		controls->Jump = 0;
		controls->Branch = 1;
		controls->MemRead = 0;
		controls->MemtoReg = 2;
		controls->ALUOp = 1;
		controls->MemWrite = 0;
		controls->ALUSrc = 0;
		controls->RegWrite = 0;
		return 0;
	}

	// If the op code is 8, then it's for add immediate (addi).
	else if(op == 0b00001000){
		controls->RegDst = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 0;
		controls->MemWrite = 0;
		controls->ALUSrc = 1;
		controls->RegWrite = 1;
		return 0;
	}

	// If the op code is 10, then it's set less than immediate (slti).
	else if(op == 0b00001010){
		controls->RegDst = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 2;
		controls->MemWrite = 0;
		controls->ALUSrc = 1;
		controls->RegWrite = 1;
		return 0;
	}

	// If the op code is 15, then it's load upper immediate (lui).
	else if(op == 0b00001111){
		controls->RegDst = 1;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 6;
		controls->MemWrite = 0;
		controls->ALUSrc = 1;
		controls->RegWrite = 1;
		return 0;
	}

	// If the op code is 35, then it's load word (lw).
	else if(op == 0b00100011){
		controls->RegDst = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 1;
		controls->MemtoReg = 1;
		controls->ALUOp = 0;
		controls->MemWrite = 0;
		controls->ALUSrc = 1;
		controls->RegWrite = 1;
		return 0;
	}

	// If the op code is 43, then it's store word (sw).
	else if(op == 0b00101011){
		controls->RegDst = 2;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 2;
		controls->ALUOp = 0;
		controls->MemWrite = 1;
		controls->ALUSrc = 1;
		controls->RegWrite = 0;
		return 0;
	}

	// Else if not one of the given op codes, return 1 for HALT.
	else{
		return 1;
	}
}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{

}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

