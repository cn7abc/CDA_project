// La Salchicha group
// Jacob Rogers, Anthony Espinosa
// ja573625 (4196143), an580126 (2997208)
// December-1-2017

#include "spimcore.h"

/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{

    switch (ALUControl){

        case 0:// Addition or don't care
            *ALUresult = A + B;
            break;

        case 1:// subtraction
            *ALUresult = A - B;
            break;

        case 2:// set less than.
            if((signed int)A < (signed int)B) 
            	*ALUresult = 1;
            else      
            	*ALUresult = 0;
            break;

        case 3:// set less than unsigned.
        	if(A < B)
        		*ALUresult = 1;
        	else
        		*ALUresult = 0;
            break;

        case 4:// AND
        	*ALUresult = A & B;
            break;

        case 5:// OR
        	*ALUresult = A|B;
            break;

        case 6:// Shift by 16.
        	*ALUresult =B << 16;
            break;

        case 7:// R type.
        	*ALUresult = ~A; 
            break;

        
    }

    if(*ALUresult == 0)
    	*Zero = 1;
    else
    	*Zero = 0;
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

	// If the op code is 0, then it's an r-type instruction. R
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

	// If the op code is 2, then it's for a jump. J
	else if(op == 0x2){
		controls->RegDst = 0;
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

	// If the op code is 4, then it's for branch if equal (beq). I
	else if(op == 0x4){
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

	// If the op code is 8, then it's for add immediate (addi). I
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

	// If the op code is 10, then it's set less than immediate (slti). I
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

	// If the op code is 11, then it's set less than unsigned immediate. I
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

	// If the op code is 15, then it's load upper immediate (lui). I
	else if(op == 0xF){
		controls->RegDst = 0;
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

	// If the op code is 35, then it's load word (lw). I
	else if(op == 0x23){
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

	// If the op code is 43, then it's store word (sw). I
	else if(op == 0x2B){
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
		// Set data1 equal to the value stored at r1.
		// Set data2 equal to the value stored at r2.
		*data1 = Reg[r1];
		*data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
	// Shift upto the signed bit and check if it is 1 or zero.
	if(offset>>15 == 0x1)
		// Fill upper 16 with 1s.
		*extended_value = offset | 0xFFFF0000;
	else
		// Upper 16 are 0s already.
		*extended_value = offset;	
}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
	// If it's an r type:
	if(ALUOp == 7){
		if (funct == 0x20)
        	ALU(data1, data2, 0, ALUresult, Zero);        
        
		else if (funct == 0x22)
        	ALU(data1, data2, 1, ALUresult, Zero);        
        
        else if (funct == 0x24)
       	 	ALU(data1, data2, 4, ALUresult, Zero);       
        
        else if (funct == 0x25)
        	ALU(data1, data2, 5, ALUresult, Zero);        
        
        else if (funct == 0x2a)
        	ALU(data1, data2, 2, ALUresult, Zero);        
        
        else if (funct == 0x2b)
        	ALU(data1, data2, 3, ALUresult, Zero);        
        else
        	return 1;
 
        return 0;
    }

    // Otherwise, check the ALUsource and pass data2 if it's 0 or extended value if it's 1.
    if(ALUSrc == 0){
	    ALU(data1, data2, ALUOp, ALUresult, Zero);  
		return 0;
    }  

    if(ALUSrc == 1){
	    ALU(data1, extended_value, ALUOp, ALUresult, Zero);   
	   return 0;
    }

    return 1;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

	
	if(MemRead == 1)
	{

		
		if(ALUresult %  4 != 0)
		{

			return 1;

		}
	
		
		*memdata = Mem[ALUresult>>2];

	}

	
	
	else if(MemWrite == 1)
	{
			
		
		if(ALUresult %  4 != 0)
		{
			return 1;
		}
		
		
		Mem[ALUresult>>2] = data2;
	
	}

	return 0;

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
	// Write to register only if RegWrite is asserted.
	if(RegWrite == 1)
	{
		//  Write to r2. 
		if( RegDst == 0 )
		{
			if(MemtoReg == 1)
			{
				// From mem to register r2
				Reg[r2] = memdata; 
				return; 
			}
		
			else
			{

				// we save into r2 registar 
				Reg[r2] = ALUresult;
				return;

			}
		}
	
		// Or r3.
		else
		{
				if(MemtoReg == 1)
		{

				// From mem to register r3
				Reg[r3] = memdata;
  
		}

		else
		{

				Reg[r3] = ALUresult;

		}
	 }
	}

	return;

}


/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

	// if it tells us to branch and  zero is 1 do the inside
	if((Branch == 1) && (Zero == 1))
	{

		// which the inside here offsets + PC + 4 and it puts  four zeros in the 
		// most signifcant btye to delay it
		*PC = ((*PC) + (4) + (extended_value<<2));
		return;

	}

	// else it told us to jump
	else if(Jump == 1)
	{

		// it gets the least sinficant btyes and it sifts them by 2 
		// PC(31 - 28) and jsec shifted left 2
		*PC = (((*PC + 4) & 0xF0000000) + (jsec<<2));
		return; 

	}

	// it progresses it by Incrementing it  by 4
	else
	{

		// it progresses it by Incrementing it  by 4
		*PC = (*PC + 4);
		return;

	}
}

