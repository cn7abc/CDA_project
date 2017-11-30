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
	// Check if the address is word aligned
	if(PC % 4 == 0){
		// Copy the contents of Mem at the address into instruction.
		*instruction = Mem[PC >> 2];
		return 0;	
	}
	else{
		return 1;
	}
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
	// AND with 1111 1100 0000 0000 0000 0000 0000 0000 and then shift 26 to get op.
	*op = (instruction & 0xFC000000) >> 26;

	// AND with 0000 0011 1110 0000 0000 0000 0000 0000 and then shift 21 to get r1.
	*r1 = (instruction & 0x03C00000) >> 21;

	// AND with 0000 0000 0001 1111 0000 0000 0000 0000 and then shift 16 to get r2.
	*r2 = (instruction & 0x001F0000) >> 16;

	// AND with 0000 0000 0000 0000 1111 1000 0000 0000 and then shift 11 to get r3.
	*r3 = (instruction & 0x0000F800) >> 11;

	// AND with 0000 0000 0000 0000 0000 0000 0011 1111 to get funct.
	*funct = (instruction & 0x0000003F);

	// AND with 0000 0000 0000 0000 1111 1111 1111 1111 to get offset.
	*offset = (instruction & 0x0000FFFF);

	// AND with 0000 0011 1111 1111 1111 1111 1111 1111 to get jsec.
	*jsec = (instruction & 0x03FFFFFF);
}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
	// This is an r-type instruction (000000).
	if(op == 0x0){
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
	// This is for jump (000010).
	else if(op == 0x2){
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
	// This is for beq (000100).
	else if(op == 0x4){
		controls->RegDst = 2;
		controls->Jump = 0;
		controls->Branch = 1;
		controls->MemRead = 0;
		controls->MemtoReg = 2;
		controls->ALUOp = 1;		// ALUOp = 01, ALU will do a subtract
		controls->MemWrite = 0;
		controls->ALUSrc = 0;
		controls->RegWrite = 0;
		return 0;
	}
	// This is for addi (001000).
	else if(op == 0x8){
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
	// This is for slti (001010).
	else if(op == 0xA){
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
	// This is for sltui (001011).
	else if(op == 0xB){
		controls->RegDst = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 3;
		controls->MemWrite = 0;
		controls->ALUSrc = 1;
		controls->RegWrite = 1;
		return 0;
	}
	// This is for lui (001111).
	else if(op == 0xF){
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
	// This is for lw (100011).
	else if(op == 0x23){
		controls->RegDst = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 1;
		controls->MemtoReg = 1;
		controls->ALUOp = 0;		// ALUOp = 00, ALU will add
		controls->MemWrite = 0;
		controls->ALUSrc = 1;
		controls->RegWrite = 1;
		return 0;
	}
	// This is for sw (101011).
	else if(op == 0x2B){
		controls->RegDst = 2;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 2;
		controls->ALUOp = 0;		// ALUOp = 00, ALU will add
		controls->MemWrite = 1;
		controls->ALUSrc = 1;
		controls->RegWrite = 0;
		return 0;
	}
	else{
		// If it is not one of the instructions above, then it is an illegal instruction. Set HALT to 1.
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

