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
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction){
    if(!instruction || !Mem || PC % 4) return 1;
    
    *instruction = MEM(PC);
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec){
    
}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

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

	// if MemRead is 1 Load instruction
	if(MemRead == 1)
	{

		// Check if word is aligned by 4 indexes 
		if(ALUresult %  4 != 0)
		{

			return 1;

		}
	
		// this mulitpes by 4 by shifting  right by 2, and it moves us 4 indexes
		*memdata = Mem[ALUresult>>2];

	}

	
	// if MemWrite is 1 we save instruction
	else if(MemWrite == 1)
	{
			
		// Check if word is aligned by 4 indexes 
		if(ALUresult %  4 != 0)
		{
			return 1;
		}
		
		// this mulitpes by 4 by shifting  right by 2, and it moves us 4 indexes
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
)		{

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
		*PC = ((*PC & 0xF0000000) + (jsec<<2);
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

