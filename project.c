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

