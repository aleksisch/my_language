#ifndef INC_OPCODE_H
#define INC_OPCODE_H

namespace opcode {
    std::string StrToHex(std::string hex_str) {
        std::string res;
        unsigned char tmp = 0;
        for (int i = 0; i < hex_str.size(); i++) {
            if (hex_str[i] >= '0' && hex_str[i] <= '9') {
                tmp += (1 + 15 * (i % 2 == 0)) * (hex_str[i] - '0');
            } else {
                tmp += (1 + 15 * (i % 2 == 0)) * (hex_str[i] - 'a' + 10);
            }
            if (i % 2 == 1) {
                res.append(1, tmp);
                tmp = 0;
            }
        }
        return res;
    };
    std::string ADD_XMM0XMM1   = StrToHex("f20f58c1");
	std::string SUB_XMM0XMM1   = StrToHex("f20f5cc1");
	std::string DIV_XMM0XMM1   = StrToHex("f20f5ec1");
	std::string MUL_XMM0XMM1   = StrToHex("f20f59c1");
	std::string PUSH_RAM       = StrToHex("ffb5");			//push[bp + x], expected 32bit x after opcode
    std::string POP_RAM        = StrToHex("8f85");            //pop [bp + x]
	std::string PUSH_ELEM      = StrToHex("48b8");            //mov rax, elem
	std::string RAX_TO_XMM1    = StrToHex("f2480f2ac8");      //cvtsi2sd xmm1, rax
    std::string R8_TO_XMM1     = StrToHex("f2490f2ac8");      //cvtsi2sd xmm1,r8
    std::string XMM0_TO_RAX    = StrToHex("f2480f2cc0");    //cvttsd2si rax, xmm0
	std::string CALL           = StrToHex("e8");              //call ...
    std::string JL             = StrToHex("0f82");
    std::string JME            = StrToHex("0f83");
    std::string JAE            = StrToHex("0f83");
    std::string JE             = StrToHex("0f84");
    std::string JNE            = StrToHex("0f85");
    std::string JLE            = StrToHex("0f86");
    std::string JM             = StrToHex("0f87");
    std::string JA             = StrToHex("0f87");
    std::string PUSH_RAX       = StrToHex("50");
    std::string POP_RAX        = StrToHex("58");
    std::string RET            = StrToHex("c3");
    std::string END_OF_PROGRAM = StrToHex("b801000000bb00000000cd80");
    std::string RESERVE_IN_STACK = StrToHex("4881ecf0000000");   //reserve 160 byte in stack
    std::string MOV_RBP_RSP      = StrToHex("4889e5");
    std::string CMP_XMMs         = StrToHex("660f2fc1");         //comisd xmm0,xmm1
    std::string POP_XMM0         = StrToHex("f20f100424");
    std::string POP_XMM1         = StrToHex("f20f100c24");
    std::string POP_XMM2         = StrToHex("f20f101424");
    std::string POP_XMM3         = StrToHex("f20f101c24");
    std::string PUSH_XMM0        = StrToHex("f20f110424");
    std::string PUSH_XMM1        = StrToHex("f20f110c24");
    std::string PUSH_XMM2        = StrToHex("f20f111424");
    std::string PUSH_XMM3        = StrToHex("f20f111c24");
    std::string SQRT_XMM1   = StrToHex("f20f51c1");
    std::string JMP              = StrToHex("e9");           //jmp near opcode


}

#endif