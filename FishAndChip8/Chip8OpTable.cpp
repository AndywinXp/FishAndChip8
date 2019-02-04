#include "Chip8OpTable.h"

Chip8OpTable::Chip8OpTable()
{
}

Chip8OpTable::~Chip8OpTable()
{
}

void (*Chip8Table[OPCODE_HIGH_NIBBLE])(unsigned short op) = 
{
	OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP,
	ARITHM, OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP
};

void(*Chip8TableClsRet[OPCODE_CLS_RET])(unsigned short op) =
{
	OP_000E, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG,
	OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_00EE, OP_ILLG
};

void(*Chip8TableArithmetic[OPCODE_ARITHMETIC])(unsigned short op) =
{
	OP_8xy0, OP_8xy1, OP_8xy2, OP_8xy3, OP_8xy4, OP_8xy5, OP_8xy6, OP_8xy7,
	OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_ILLG, OP_8xyE, OP_ILLG
};

void(*Chip8TableKeybCheck[OPCODE_KEYB_CHECK])(unsigned short op) =
{
	OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP,
	OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP
};

void(*Chip8TableFInstructions[OPCODE_F_INSTRUCTIONS])(unsigned short op) =
{
	OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP,
	OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP, OP_NOP
};

void ARITHM(unsigned short op)
{
	Chip8TableArithmetic[(op & 0x000F)](op);
}

void CLSRET(unsigned short op)
{
	Chip8TableClsRet[(op & 0x000F)](op);
}

void OP_NOP(unsigned short op)
{
	// Do nothing
}

void OP_ILLG(unsigned short op)
{
	std::cout << "Illegal opcode.\n";
}

void OP_000E(unsigned short op, void obj)
{

}

void OP_00EE(unsigned short op)
{

}

void OP_8xy0(unsigned short op)
{

}

void OP_8xy1(unsigned short op)
{

}

void OP_8xy2(unsigned short op)
{

}

void OP_8xy3(unsigned short op)
{

}

void OP_8xy4(unsigned short op)
{

}

void OP_8xy5(unsigned short op)
{

}

void OP_8xy6(unsigned short op)
{

}

void OP_8xy7(unsigned short op)
{

}

void OP_8xyE(unsigned short op)
{

}

