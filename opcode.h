/*TODO: Primary haritada bi sıkıntı var*/
#include <string>

static const std::string primary_opcode_map32[] = {"ADD Eb Gb","ADD Ev Gv","ADD Gb Eb","ADD Gv Ev","ADD AL Ib","ADD EAX Iz","PUSH ES","POP ES",  "OR Eb Gb","OR Ev Gv","OR Gb Eb","OR Gv Ev","OR AL Ib","OR EAX Iz","PUSH CS","ESC secondary",
													"ADC Eb Gb","ADC Ev Gv","ADC Gb Eb","ADC Gv Ev","ADC AL Ib","ADC EAX Iz","PUSH SS","POP SS", "SBB Eb Gb","SBB Ev Gv","SBB Gb Eb","SBB Gv Ev","SBB AL Ib","SBB EAX Iz","PUSH DS","POP DS",
													"AND Eb Gb","AND Ev Gv","AND Gb Eb","AND Gv Ev","AND AL Ib","AND EAX Iz","SEG ES","DAA",     "SUB Eb Gb","SUB Ev Gv","SUB Gb Eb","SUB Gv Ev","SUB AL Ib","SUB EAX Iz","SEG CS","DAS",
													"XOR Eb Gb","XOR Ev Gv","XOR Gb Eb","XOR Gv Ev","XOR AL Ib","XOR EAX Iz","SEG SS","AAA",     "CMP Eb Gb","CMP Ev Gv","CMP Gb Eb","CMP Gv Ev","CMP AL Ib","CMP EAX Iz","SEG DS","AAS",
													"INC EAX","INC ECX","INC EDX","INC EBX","INC ESP","INC EBP","INC ESI","INC EDI",             "DEC EAX","DEC ECX","DEC EDX","DEC EBX","DEC ESP","DEC EBP","DEC ESI","DEC EDI",
													"PUSH EAX","PUSH ECX","PUSH EDX","PUSH EBX","PUSH ESP","PUSH EBP","PUSH ESI","PUSH EDI",     "POP EAX","POP ECX","POP EDX","POP EBX","POP ESP","POP EBP","POP ESI","POP EDI",
													"PUSHA","POPA","BOUND Gv Ma","ARPL Ew Gw","PRE FS","PRE GS","PRE OSO","PRE ASO",             "PUSH Iz","IMUL Gv Ev Iz","PUSH Ib", "IMUL Gv Ev Ib","INSB Yb DX","INSW Yz DX","OUTS DX Xb","OUTS DX,Xz",
													"JO Jb","JNO Jb","JB Jb","JNB Jb","JZ Jb","JNZ Jb","JBE Jb","JNBE Jb",                       "JS Jb","JNS Jb","JP Jb","JNP Jb","JL Jb","JNL Jb","JLE Jb","JNLE Jb",
													"GROUP 1","GROUP 1","GROUP 1","GROUP 1","TEST Eb Gb","TEST Ev Gv","XCHG Eb Gb","XCHG Ev Gv", "MOV Eb Gb","MOV Ev Gv","MOV Gb Eb","MOV Gv Ev","MOV Mw Sw","LEA Gv Mv","MOV Sw Ew","GROUP 1A",	"NOP","XCHG ECX EAX","XCHG EDX EAX","XCHG EBX EAX","XCHG ESP EAX","XCHG EBP EAX","XCHG ESI EAX","XCHG EDI EAX","CBW","CWD","CALL Ap","WAIT","PUSHF Fv","POPF Fv","SAHF","LAHF",	"MOV AL Ob","MOV EAX Ov","MOV Ob AL","MOV Ob EAX","MOVSB Yb Xb","MOVSW Yv Xv","CMPSB Xb Yb","CMPSW Xv Yv","TEST AL Ib","TEST EAX Iz","STOSB Yb AL","STOSW Yv EAX","LODSB AL Xb","LODSW EAX Xv","SCASB Al Yb","SCASW EAX Yv","MOV AL Ib","MOV CL Ib","MOV DL Ib","MOV BL IB","MOV AH Ib","MOV CH Ib","MOV DH Ib","MOV BH Ib","MOV EAX Iv","MOV EAX ECX Iv","MOV EDX Iv","MOV EBX Iv","MOV ESP Iv","MOV EBP Iv","MOV ESI Iv","MOV EDI Iv","GROUP 2","GROUP 2","RET Iw","RET","LES GZ Mp","LDS Gz Mp","GROUP 11","GROUP 11","ENTER Iw Ib","LEAVE","RET Iw","RET","INT3","INT Ib","INTO","IRET","GROUP 2","GROUP 2","GROUP 2","GROUP 2","AAM Ib","AAD Ib","","XLAT","ESC x87","ESC x87","ESC x87","ESC x87","ESC x87","ESC x87","ESC x87","ESC x87","LOOPNE Jb","LOOPE Jb","LOOP Jb","JrCXZ Jb","IN AL Ib","IN EAX Ib","OUT Ib AL","OUT Ib EAX","CALL Jz","JMP Jz","JMP Ap","JMP Jb","IN AL DX","IN EAX DX","OUT DX AL","OUT DX EAX","PRE LOCK","INT1","PRE REPNE","PRE REP","HLT","CMC","GROUP 3","GROUP 3","CLC","STC","CLI","STI","CLD","STD","GROUP 4","GROUP 5"};

static const std::string primary_opcode_map64[] = {"ADD Eb Gb","ADD Ev Gv","ADD Gb Eb","ADD Gv Ev","ADD AL Ib","ADD RAX Iz","","","OR Eb Gb","OR Ev Gv","OR Gb Eb","OR Gv Ev","OR AL Ib","OR RAX Iz","","ESC secondary",
													"ADC Eb Gb","ADC Ev Gv","ADC Gb Eb","ADC Gv Ev","ADC AL Ib","ADC RAX Iz","","","SBB Eb Gb","SBB Ev Gv","SBB Gb Eb","SBB Gv Ev","SBB AL Ib","SBB RAX Iz","","",
													"AND Eb Gb","AND Ev Gv","AND Gb Eb","AND Gv Ev","AND AL Ib","AND RAX Iz","PRE NULL","","SUB Eb Gb","SUB Ev Gv","SUB Gb Eb","SUB Gv Ev","SUB AL Ib","SUB RAX Iz","PRE NULL","",
													"XOR Eb Gb","XOR Ev Gv","XOR Gb Eb","XOR Gv Ev","XOR AL Ib","XOR RAX Iz","PRE NULL","","CMP Eb Gb","CMP Ev Gv","CMP Gb Eb","CMP Gv Ev","CMP AL Ib","CMP RAX Iz","PRE NULL","",
													"PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX",
													"PUSH RAX","PUSH RCX","PUSH RDX","PUSH RBX","PUSH RSP","PUSH RBP","PUSH RSI","PUSH RDI","POP RAX","POP RCX","POP RDX","POP RBX","POP RSP","POP RBP","POP RSI","POP RDI",
													"","","","MOVSXD Gv Ez","PRE FS","PRE GS","PRE OSO","PRE ASO","PUSH Iz","IMUL Gv Ev Iz","PUSH Ib", "IMUL Gv Ev,Ib","INSB Yb DX","INSW Yz DX","OUTS DX Xb","OUTS DX,Xz",
													"JO Jb","JNO Jb","JB Jb","JNB Jb","JZ Jb","JNZ Jb","JBE Jb","JNBE Jb","JS Jb","JNS Jb","JP Jb","JNP Jb","JL Jb","JNL Jb","JLE Jb","JNLE Jb","GROUP 1","GROUP 1","","GROUP 1","TEST Eb Gb","TEST Ev Gv","XCHG Eb Gb","XCHG Ev Gv","MOV Eb Gb","MOV Ev Gv","MOV Gb Eb","MOV Gv Ev","MOV Mw Sw","LEA Gv Mv","MOV Sw Ew","GROUP 1A",	"XCHG r8 RAX","XCHG RCX RAX","XCHG RDX RAX","XCHG RBX RAX","XCHG RSP RAX","XCHG RBP RAX","XCHG RSI RAX","XCHG RDI RAX","CBW","CWD","","WAIT","PUSHF Fv","POPF Fv","SAHF","LAHF","MOV AL Ob","MOV RAX Ov","MOV Ob AL","MOV Ob RAX","MOVSB Yb Xb","MOVSW Yv Xv","CMPSB Xb Yb","CMPSW Xv Yv","TEST AL Ib","TEST RAX Iz","STOSB Yb AL","STOSW Yv RAX","LODSB AL Xb","LODSW RAX Xv","SCASB Al Yb","SCASW RAX Yv","MOV AL Ib","MOV CL Ib","MOV DL Ib","MOV BL IB","MOV AH Ib","MOV CH Ib","MOV DH Ib","MOV BH Ib","MOV RAX Iv","MOV RAX RCX Iv","MOV RDX Iv","MOV RBX Iv","MOV RSP Iv","MOV RBP Iv","MOV RSI Iv","MOV RDI Iv","GROUP 2","GROUP 2","RET Iw","RET","ESC VEX","ESC VEX","GROUP 11","GROUP 11","ENTER Iw Ib","LEAVE","RET Iw","RET","INT3","INT Ib","INTO","IRET","GROUP 2","GROUP 2","GROUP 2","GROUP 2","","","","XLAT","ESC x87","ESC x87","ESC x87","ESC x87","ESC x87","ESC x87","ESC x87","ESC x87","LOOPNE Jb","LOOPE Jb","LOOP Jb","JrCXZ Jb","IN AL Ib","IN EAX Ib","OUT Ib AL","OUT Ib EAX","CALL Jz","JMP Jz","","JMP Jb","IN AL DX","IN EAX DX","OUT DX AL","OUT DX EAX",	"PRE LOCK","INT1","PRE REPNE","PRE REP","HLT","CMC","GROUP 3","GROUP 3","CLC","STC","CLI","STI","CLD","STD","GROUP 4","GROUP 5"};

static const std::string secondary_opcode_map_none[] = {"GROUP 6", "GROUP 7", "LAR Gv Ew", "LSL Gv Ew", "", "SYSCALL", "CLTS", "SYSRET", "INVD", "WBINVD", "", "UD2", "", "GROUP P", "FEMSS", "ESC 3DNOW",
														"MOVUPS Vps Wps", "MOVUPS Wps Vps", "MOVLPS Vq Mq", "MOVLPS Mq Vq", "UNPCKLPS Vps Wps", "UNPCKHPS Vps Wps", "MOVHPS Vo.q Mq", "MOVHPS Mq Vo.q","GROUP 16", "NOP Mv", "NOP Mv", "NOP Mv", "NOP Mv", "NOP Mv", "NOP Mv", "NOP Mv",
														"MOV Rd Cd", "MOV Rd Dd", "MOV Cd Rd", "MOV Dd Rd", "",  "", "", "", "MOVAPS Vps Wps", "MOVAPS Wps Vps", "CVTPI2PS Vps Qpj", "MOVNTPS Mo Vps", "CVTTPS2PI Ppj Wps", "CVTPS2PI Ppj Wps", "UCOMISS Vss Wss", "COMISS Vss Wss",
														"WRMSR", "RDTSC", "RDMSR", "RDPMC", "SYSENTER", "SYSEXIT","","", "ESC 0F_38h", "", "ESC 0F_3Ah", "", "", "", "", "",
														"CMOVO Gv Ev", "CMOVNO Gv Ev", "CMOVB Gv Ev", "CMOVNB Gv Ev", "CMOVZ Gv Ev", "CMOVNZ Gv Ev", "CMOVBE Gv Ev", "CMOVNBE Gv Ev", "CMOVS Gv Ev", "CMOVNS Gv Ev", "CMOVP Gv Ev", "CMOVNP Gv Ev", "CMOVL Gv Ev", "CMOVNL Gv Ev", "CMOVLE Gv Ev", "CMOVNLE Gv Ev",
														"MOVMSKPS Gd Ups", "SQRTPS Vps Wps", "RSQRTPS Vps Wps", "RCPPS Vps Wps", "ANDPS Vps Wps", "ANDNPS Vps Wps", "ORPS Vps Wps", "XORPS Vps Wps", "ADDPS Vps Wps", "MULPS Vps Wps", "CVTPS2PD Vpd Wps", "CVTDQ2PS Vps Wo", "SUBPS Vps Wps", "MINPS Vps Wps", "DIVPS Vps Wps", "MAXPS Vps Wps", "PUN-PCKLBW Pq Qd", "PUN- PCKLWD Pq Qd", "PUN- PCKLDQ Pq Qd", "PACKSSWB Ppi Qpi", "PCMPGTB Ppk Qpk", "PCMPGTW Ppi Qpi", "PCMPGTD Ppj Qpj", "PACKUSWB Ppi Qpi", "PUNPCK-HBW Pq Qd", "PUNPCK-HWD Pq Qd", "PUNPCK-HDQ Pq Qd", "PACKSSDW Pq Qq", "", "", "MOVD Py Ey", "MOVQ Pq Qq", "PUN-PCKLBW Pq Qd", "PUN- PCKLWD Pq Qd", "PUN- PCKLDQ Pq Qd", "PACKSSWB Ppi Qpi", "PCMPGTB Ppk Qpk", "PCMPGTW Ppi Qpi", "PCMPGTD Ppj Qpj", "PACKUSWB Ppi Qpi", "PUNPCK-HBW Pq Qd", "PUNPCK-HWD Pq Qd", "PUNPCK-HDQ Pq Qd", "PACKSSDW Pq Qq", "", "", "MOVD Py Ey", "MOVQ Pq Qq", "PSHUFW Pq Qq Ib", "GROUP 12", "Group 13", "Group 14", "PCMPEQB Ppk Qpk", "PCMPEQW Ppi Qpi", "PCMPEQD Ppj Qpj", "EMMS", "", "", "", "", "", "", "MOVD Ey, Py", "MOVQ Qq, Pq", "JO Jz", "JNO Jz", "JB Jz", "JNB Jz", "JZ Jz", "JNZ Jz", "JBE Jz", "JNBE Jz", "JS Jz", "JNS Jz", "JP Jz", "JNP Jz", "JL Jz", "JNL Jz", "JLE Jz", "JNLE Jz", "SETO Eb", "SETNO Eb", "SETB Eb", "SETNB Eb", "SETZ Eb", "SETNZ Eb", "SETBE Eb", "SETNBE Eb", "SETS Eb", "SETNS Eb", "SETP Eb", "SETNP Eb", "SETL Eb", "SETNL Eb", "SETLE Eb", "SETNLE Eb", "PUSH FS", "POP FS", "CPUID", "BT Ev Gv", "SHLD Ev Gv Ib", "SHLD Ev Gv CL", "", "", "PUSH GS", "POP GS", "RSM", "BTS Ev Gv", "SHRD Ev Gv Ib", "SHRD Ev Gv CL", "GROUP 15", "IMUL Gv Ev", "CMPXCHG Eb Gb", "CMPXCHG Ev Gv", "LSS Gz Mp", "BTR Ev Gv", "LFS Gz Mp", "LGS Gz Mp", "MOVZX Gv Eb", "MOVZX Gv Ew", "", "GROUP 10", "GROUP 8", "BTC Ev Gv", "BSF Gv Ev", "BSR Gv Ev", "MOVSX Gv Eb" "MOVSX Gv Ew", "XADD Eb Gb", "XADD Ev Gv", "CMPPS Vps Wps Ib", "MOVNTI My Gy", "PINSRW Pq Ew Ib", "PEXTRW Gd Nq Ib", "SHUFPS Vps Wps Ib", "GROUP 9", "BSWAP RAX", "BSWAP rCX", "BSWAP rDX","BSWAP rBX", "BSWAP rSP", "BSWAP rBP", "BSWAP rSI", "BSWAP rDI", "", "PSRLW Pq Qq", "PSRLD Pq Qq", "PSRLQ Pq Qq", "PADDQ Pq Qq", "PMULLW Pq Qq", "", "PMOVMSKB Gd Nq", "PSUBUSB Pq Qq", "PSUBUSW Pq Qq", "PMINUB Pq Qq", "PAND Pq Qq", "PADDUSB Pq Qq", "PADDUSW Pq Qq", "PMAXUB Pq Qq", "PANDN Pq Qq", "PAVGB Pq Qq", "PSRAW Pq Qq", "PSRAD Pq Qq", "PAVGW Pq Qq", "PMULHUW Pq Qq", "PMULHW Pq Qq", "", "MOVNTQ Mq Pq", "PSUBSB Pq Qq", "PSUBSW Pq Qq", "PMINSW Pq Qq", "POR Pq Qq", "PADDSB Pq Qq", "PADDSW Pq Qq", "PMAXSW Pq Qq", "PXOR Pq Qq", "", "PSLLW Pq Qq", "PSLLD Pq Qq", "PSLLQ Pq Qq", "PMULUDQ Pq Qq", "PMADDWD Pq Qq", "PSADBW Pq Qq", "MASKMOVQ Pq Nq", "PSUBB Pq Qq", "PSUBW Pq Qq", "PSUBD Pq Qq", "PSUBQ Pq Qq", "PADDB Pq Qq", "PADDW Pq Qq", "PADDD Pq Qq", "UD0"};

static const std::string secondary_opcode_map_66[] = {"GROUP 6", "GROUP 7", "LAR Gv Ew", "LSL Gv Ew", "", "SYSCALL", "CLTS", "SYSRET", "INVD", "WBINVD", "", "UD2", "", "GROUP P", "FEMSS", "ESC 3DNOW",
														"MOVUPD Vpd Wpd", "MOVUPD Wpd Vpd", "MOVLPD Vo.q Mq", "MOVLPD Mq Vo.q", "UNPCKLPD Vo.q Wo.q", "UNPCKHPD Vo.q Wo.q", "MOVHPD Vo.q Mq", "MOVHPD Mq, Vo.q","GROUP 16", "NOP Mv", "NOP Mv", "NOP Mv", "NOP Mv", "NOP Mv", "NOP Mv", "NOP Mv",
														"MOV Rd Cd", "MOV Rd Dd", "MOV Cd Rd", "MOV Dd Rd", "",  "", "", "", "MOVAPD Vpd Wpd", "MOVADP Wpd Vpd", "CVTPI2PD Vpd Qpj", "MOVNTPD Mo Vpd", "CVTTPD2PI Ppj Wpd", "CVTPD2PI Ppj Wpd", "UCOMISD Vsd Wsd", "COMISD Vsd Wsd",
														"WRMSR", "RDTSC", "RDMSR", "RDPMC", "SYSENTER", "SYSEXIT","","", "ESC 0F_38h", "", "ESC 0F_3Ah", "", "", "", "", "",
														"CMOVO Gv Ev", "CMOVNO Gv Ev", "CMOVB Gv Ev", "CMOVNB Gv Ev", "CMOVZ Gv Ev", "CMOVNZ Gv Ev", "CMOVBE Gv Ev", "CMOVNBE Gv Ev", "CMOVS Gv Ev", "CMOVNS Gv Ev", "CMOVP Gv Ev", "CMOVNP Gv Ev", "CMOVL Gv Ev", "CMOVNL Gv Ev", "CMOVLE Gv Ev", "CMOVNLE Gv Ev", "MOVMSKPD Gd Upd", "SQRTPD Vpd Wpd", "","", "ANDPD Vpd Wpd", "ANDNPD Vpd Wpd", "ORPD Vpd Wpd", "XORPD Vpd Wpd", "ADDPD Vpd Wpd", "MULPD Vpd Wpd", "CVTPD2PS Vps Wpd", "CVTPS2DQ Vo Wps", "SUBPD Vpd Wpd", "MINPD Vpd Wpd", "DIVPD Vpd Wpd", "MAXPD Vpd Wpd", "PUN-PCKLBW Vo.q Wo.q", "PUN- PCKLWD Vo.q Wo.q", "PUN- PCKLDQ Vo.q, Wo.q", "PACKSSWB Vpi Wpi", "PCMPGTB Vpk Wpk", "PCMPGTW Vpi Wpi", "PCMPGTD Vpj Wpj", "PACKUSWB Vpi, Wpi", "PUNPCK-HBW Vo Wq", "PUNPCK-HWD Vo Wq", "PUNPCK-HDQ Vo Wq", "PACKSSDW Vo Wo", "PUNPCK-LQDQ Vo Wq", "PUNPCK-HQDQ Vo Wq", "MOVD Vy Ey", "MOVDQA Vo Wo", "PSHUFD Vo Wo Ib", "GROUP 12", "GROUP 13", "GROUP 14", "PCMPEQB Vpk Wpk", "PCMPEQW Vpi Wpi", "PCMPEQD Vpj, Wpj", "GROUP 17", "EXTRQ Vo.q Uo", "", "", "HADDPD Vpd Wpd", "HSUBPD Vpd Wpd", "MOVD Ey Vy", "MOVDQA Wo Vo", "JO Jz", "JNO Jz", "JB Jz", "JNB Jz", "JZ Jz", "JNZ Jz", "JBE Jz", "JNBE Jz", "JS Jz", "JNS Jz", "JP Jz", "JNP Jz", "JL Jz", "JNL Jz", "JLE Jz", "JNLE Jz", "SETO Eb", "SETNO Eb", "SETB Eb", "SETNB Eb", "SETZ Eb", "SETNZ Eb", "SETBE Eb", "SETNBE Eb", "SETS Eb", "SETNS Eb", "SETP Eb", "SETNP Eb", "SETL Eb", "SETNL Eb", "SETLE Eb", "SETNLE Eb", "PUSH FS", "POP FS", "CPUID", "BT Ev Gv", "SHLD Ev Gv Ib", "SHLD Ev Gv CL", "", "", "PUSH GS", "POP GS", "RSM", "BTS Ev Gv", "SHRD Ev Gv Ib", "SHRD Ev Gv CL", "GROUP 15", "IMUL Gv Ev", "CMPXCHG Eb Gb", "CMPXCHG Ev Gv", "LSS Gz Mp", "BTR Ev Gv", "LFS Gz Mp", "LGS Gz Mp", "MOVZX Gv Eb", "MOVZX Gv Ew", "", "", "", "", "", "", "", "", "XADD Eb Gb", "XADD Ev Gv", "CMPPD Vpd Wpd Ib", "", "PINSRW Vo Ew Ib", "PEXTRW Gd Uo Ib", "SHUFPD Vpd Wpd Ib", "GROUP 9", "BSWAP RAX", "BSWAP rCX", "BSWAP rDX","BSWAP rBX", "BSWAP rSP", "BSWAP rBP", "BSWAP rSI", "BSWAP rDI","ADDSUBPD Vpd Wpd", "PSRLW Vo Wo", "PSRLD Vo Wo", "PSRLQ Vo Wo", "PADDQ Vo Wo","PMULLW Vo Wo","MOVQ Wq Vq", "PMOVMSKB Gd Uo", "PSUBUSB Vo Wo", "PSUBUSW Vo Wo", "PMINUB Vo Wo", "PAND Vo Wo", "PADDUSB Vo Wo", "PADDUSW Vo Wo", "PMAXUB Vo Wo", "PANDN Vo Wo", "PAVGB Vo Wo", "PSRAW Vo Wo", "PSRAD Vo Wo", "PAVGW Vo Wo", "PMULHUW Vo Wo", "PMULHW Vo Wo", "CVTTPD2DQ Vpj Wpd", "MOVNTDQ Mo Vo", "PSUBSB Vo Wo", "PSUBSW Vo Wo", "PMINSW Vo Wo", "POR Vo Wo", "PADDSB Vo Wo", "PADDSW Vo Wo", "PMAXSW Vo Wo", "PXOR Vo Wo", "", "PSLLW Vpw Wo.q", "PSLLD Vpwd Wo.q", "PSLLQ Vpqw Wo.q", "PMULUDQ Vpj Wpj", "PMADDWD Vpi Wpi", "PSADBW Vpk Wpk", "MASKMOVDQU Vpb Upb", "PSUBB Vo Wo", "PSUBW Vo Wo", "PSUBD Vo Wo", "PSUBQ Vo Wo", "PADDB Vo Wo", "PADDW Vo Wo", "PADDD Vo Wo"};

static const std::string secondary_opcode_map_f2[] = {"GROUP 6", "GROUP 7", "LAR Gv Ew", "LSL Gv Ew", "", "SYSCALL", "CLTS", "SYSRET", "INVD", "WBINVD", "", "UD2", "", "GROUP P", "FEMSS", "ESC 3DNOW","MOVSD Vsd Wsd", "MOVSD Wsd Vsd", "MOVDDUP Vo Wsd", "", "", "", "", "","GROUP 16", "NOP Mv", "NOP Mv", "NOP Mv", "NOP Mv", "NOP Mv", "NOP Mv", "NOP Mv","MOV Rd Cd", "MOV Rd Dd", "MOV Cd Rd", "MOV Dd Rd", "",  "", "", "", "", "", "CVTSI2SD Vsd Ey", "MOVNTSD Mq Vsd", "CVTTSD2SI Gy Wsd", "CVTSD2SI Gy Wsd", "", "", "WRMSR", "RDTSC", "RDMSR", "RDPMC", "SYSENTER", "SYSEXIT", "","", "ESC 0F_38h", "", "ESC 0F_3Ah", "", "", "", "", "", "CMOVO Gv Ev", "CMOVNO Gv Ev", "CMOVB Gv Ev", "CMOVNB Gv Ev", "CMOVZ Gv Ev", "CMOVNZ Gv Ev", "CMOVBE Gv Ev", "CMOVNBE Gv Ev", "CMOVS Gv Ev", "CMOVNS Gv Ev", "CMOVP Gv Ev", "CMOVNP Gv Ev", "CMOVL Gv Ev", "CMOVNL Gv Ev", "CMOVLE Gv Ev", "CMOVNLE Gv Ev", "", "SQRTSD Vsd Wsd", "", "", "", "", "", "", "ADDSD Vsd Wsd", "MULSD Vsd Wsd", "CVTSD2SS Vss Wsd", "", "SUBSD Vsd Wsd", "MINSD Vsd Wsd", "DIVSD Vsd Wsd", "MAXSD Vsd Wsd", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "PSHUFLW Vq Wq Ib", "GROUP 12", "GROUP 13", "GROUP 14", "", "", "", "", "INSERTQ Vo.q Uo.q Ib, Ib", "INSERTQ Vo.q Uo", "", "", "HADDPS Vps Wps", "HSUBPS Vps Wps", "", "","JO Jz", "JNO Jz", "JB Jz", "JNB Jz", "JZ Jz", "JNZ Jz", "JBE Jz", "JNBE Jz", "JS Jz", "JNS Jz", "JP Jz", "JNP Jz", "JL Jz", "JNL Jz", "JLE Jz", "JNLE Jz", "SETO Eb", "SETNO Eb", "SETB Eb", "SETNB Eb", "SETZ Eb", "SETNZ Eb", "SETBE Eb", "SETNBE Eb", "SETS Eb", "SETNS Eb", "SETP Eb", "SETNP Eb", "SETL Eb", "SETNL Eb", "SETLE Eb", "SETNLE Eb", "PUSH FS", "POP FS", "CPUID", "BT Ev Gv", "SHLD Ev Gv Ib", "SHLD Ev Gv CL", "", "", "PUSH GS", "POP GS", "RSM", "BTS Ev Gv", "SHRD Ev Gv Ib", "SHRD Ev Gv CL", "GROUP 15", "IMUL Gv Ev", "CMPXCHG Eb Gb", "CMPXCHG Ev Gv", "LSS Gz Mp", "BTR Ev Gv", "LFS Gz Mp", "LGS Gz Mp", "MOVZX Gv Eb", "MOVZX Gv Ew", "", "", "", "", "", "", "", "", "XADD Eb Gb", "XADD Ev Gv", "CMPSD Vsd Wsd Ib", "", "", "", "", "GROUP 9","BSWAP RAX", "BSWAP rCX", "BSWAP rDX","BSWAP rBX", "BSWAP rSP", "BSWAP rBP", "BSWAP rSI", "BSWAP rDI","ADDSUBPS Vas Wps", "", "", "", "", "", "MOVDQ2Q Pq Uq", "","", "", "", "", "", "", "", "", "", "", "", "", "", "", "CVTPD2DQ Vpj Wpd", "", "", "", "", "", "", "", "", "", "LDDQU Vo Mo", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "UD0"};
static const std::string secondary_opcode_map_f3[] = {"GROUP 6", "GROUP 7", "LAR Gv Ew", "LSL Gv Ew", "", "SYSCALL", "CLTS", "SYSRET", "INVD", "WBINVD", "", "UD2", "", "GROUP P", "FEMSS", "ESC 3DNOW","MOVSS Vss Wss", "MOVSS Wss Vss", "MOVSLDUP Vps Wps", "", "", "", "MOVSHDUP Vps Wps", "","GROUP 16", "NOP Mv", "NOP Mv", "NOP Mv", "NOP Mv", "NOP Mv", "NOP Mv", "NOP Mv","MOV Rd Cd", "MOV Rd Dd", "MOV Cd Rd", "MOV Dd Rd", "",  "", "", "", "", "", "VTSI2SS Vss Ey", "MOVNTSS Md Vss", "CVTTSS2SI Gy Wss", "CVTSS2SI Gy Wss", "", "", "WRMSR", "RDTSC", "RDMSR", "RDPMC", "SYSENTER", "SYSEXIT","","", "ESC 0F_38h", "", "ESC 0F_3Ah", "", "", "", "", "", "CMOVO Gv Ev", "CMOVNO Gv Ev", "CMOVB Gv Ev", "CMOVNB Gv Ev", "CMOVZ Gv Ev", "CMOVNZ Gv Ev", "CMOVBE Gv Ev", "CMOVNBE Gv Ev", "CMOVS Gv Ev", "CMOVNS Gv Ev", "CMOVP Gv Ev", "CMOVNP Gv Ev", "CMOVL Gv Ev", "CMOVNL Gv Ev", "CMOVLE Gv Ev", "CMOVNLE Gv Ev", "", "SQRTSS Vss Wss", "RSQRTSS Vss Wss", "RCPSS Vss Wss", "", "", "", "", "ADDSS Vss Wss", "MULSS Vss Wss", "CVTSS2SD Vsd Wss", "CVTTPS2D Q Vo Wps", "SUBSS Vss Wss", "MINSS Vss Wss", "DIVSS Vss Wss", "MAXSS Vss Wss", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "MOVDQU Vo Mo", "PSHUFHW Vq Wq Ib", "GROUP 12", "GROUP 13", "GROUP 14", "", "", "", "", "", "", "", "", "", "", "MOVQ Vq Wq", "MOVDQA Wo Vo","JO Jz", "JNO Jz", "JB Jz", "JNB Jz", "JZ Jz", "JNZ Jz", "JBE Jz", "JNBE Jz", "JS Jz", "JNS Jz", "JP Jz", "JNP Jz", "JL Jz", "JNL Jz", "JLE Jz", "JNLE Jz", "SETO Eb", "SETNO Eb", "SETB Eb", "SETNB Eb", "SETZ Eb", "SETNZ Eb", "SETBE Eb", "SETNBE Eb", "SETS Eb", "SETNS Eb", "SETP Eb", "SETNP Eb", "SETL Eb", "SETNL Eb", "SETLE Eb", "SETNLE Eb", "PUSH FS", "POP FS", "CPUID", "BT Ev Gv", "SHLD Ev Gv Ib", "SHLD Ev Gv CL", "", "", "PUSH GS", "POP GS", "RSM", "BTS Ev Gv", "SHRD Ev Gv Ib", "SHRD Ev Gv CL", "GROUP 15", "IMUL Gv Ev", "CMPXCHG Eb Gb", "CMPXCHG Ev Gv", "LSS Gz Mp", "BTR Ev Gv", "LFS Gz Mp", "LGS Gz Mp", "MOVZX Gv Eb", "MOVZX Gv Ew", "POPCNT Gv Ev", "", "", "", "TZCNT Gv Ev", "LZCNT Gv Ev", "", "", "XADD Eb Gb", "XADD Ev Gv", "CMPSS Vss Wss Ib", "", "", "", "", "GROUP 9", "BSWAP RAX", "BSWAP rCX", "BSWAP rDX","BSWAP rBX", "BSWAP rSP", "BSWAP rBP", "BSWAP rSI", "BSWAP rDI", "", "", "", "", "", "", "MOVQ2DQ Vo Nq", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "CVTDQ2PD Vpd Wpj", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "UD0"};

static const std::string group1_80[8] = {"ADD Eb Ib","OR Eb Ib","ADC Eb Ib","SBB Eb Ib","AND Eb Ib","SUB Eb Ib","XOR Eb Ib","CMP Eb Ib"};
static const std::string group1_81[8] = {"ADD Ev Iz","OR Ev Iz","ADC Ev Iz","SBB Ev Iz","AND Ev Iz","SUB Ev Iz","XOR Ev Iz","CMP Ev Iz"};
static const std::string group1_82[8] = {"ADD Eb Ib","OR Eb Ib","ADC Eb Ib","SBB Eb Ib","AND Eb Ib","SUB Eb Ib","XOR Eb Ib","CMP Eb Ib"};
static const std::string group1_83[8] = {"ADD Ev Ib","OR Ev Ib","ADC Ev Ib","SBB Ev Ib","AND Ev Ib","SUB Ev Ib","XOR Ev Ib","CMP Ev Ib"};

static const std::string group1a[8] = {"POP Ev","ESC XOP","ESC XOP","ESC XOP","ESC XOP","ESC XOP","ESC XOP","ESC XOP"};

static const std::string group2_C0[8] = {"ROL Eb Ib","ROR Eb Ib","RCL Eb Ib","RCR Eb Ib","SAL Eb Ib","SHR Eb Ib","SAL Eb Ib","SAR Eb Ib"};
static const std::string group2_C1[8] = {"ROL Ev Ib","ROR Ev Ib","RCL Ev Ib","RCR Ev Ib","SAL Ev Ib","SHR Ev Ib","SAL Ev Ib","SAR Ev Ib"};
static const std::string group2_D0[8] = {"ROL Eb 1","ROR Eb 1","RCL Eb 1","RCR Eb 1","SAL Eb 1","SHR Eb 1","SAL Eb 1","SAR Eb 1"};
static const std::string group2_D1[8] = {"ROL Ev 1","ROR Ev 1","RCL Ev 1","RCR Ev 1","SAL Ev 1","SHR Ev 1","SAL Ev 1","SAR Ev 1"};
static const std::string group2_D2[8] = {"ROL Eb CL","ROR Eb CL","RCL Eb CL","RCR Eb CL","SAL Eb CL","SHR Eb CL","SAL Eb CL","SAR Eb CL"};
static const std::string group2_D3[8] = {"ROL Ev CL","ROR Ev CL","RCL Ev CL","RCR Ev CL","SAL Ev CL","SHR Ev CL","SAL Ev CL","SAR Ev CL"};

static const std::string group3_F6[8] = {"TEST Eb Ib", "TEST Eb Ib", "NOT Eb","NEG Eb","MUL Eb","IMUL Eb","DIV Eb","IDIV Eb"};
static const std::string group3_F7[8] = {"TEST Ev Iz", "TEST Ev Ib", "NOT Ev","NEG Ev","MUL Ev","IMUL Ev","DIV Ev","IDIV Ev"};

//none-66-F2-F3
static const std::string group4[8] = {"INC Eb", "DEC Eb", "", "", "", "", "", ""};
static const std::string group5[8] = {"INC Ev", "DEC Ev", "CALL Ev", "CALL Mp", "JMP Ev", "JMP Mp", "PUSH Ev", ""};


static const std::string group6[8] = {"SLDT Mw/Rv", "STR Mw/Rv", "LLDT Ew", "LTR Ew", "VERR Ew", "VERW Ew", "", ""};
static const std::string group7[8] = {"SGDT Ms", "SIDT Ms", "LGDT Ms", "LIDT Ms", "SMSW Mw", "", "LMSW Ew", "INVLPG Mb"};
static const std::string group8[8] = {"", "", "", "", "BT Ev Ib", "BTS Ev Ib", "BTR Ev Ib", "BTC Ev Ib"};
static const std::string group9[8] = {"", "CMPXCHG 8B Mq", "", "", "", "", "RDRAND Rv", ""};
static const std::string group10[8] = {"UD1", "UD1", "UD1", "UD1", "UD1", "UD1", "UD1", "UD1"};

static const std::string group11_C6[8] = {"MOV Eb Ib", "", "", "", "", "", "", ""};
static const std::string group11_C7[8] = {"MOV Ev Iz", "", "", "", "", "", "", ""};

static const std::string group12[4][8] = {{"", "", "PSRLW Nq Ib", "", "PSRAW Nq Ib", "", "PSLLW Nq Ib", ""},
										{"", "", "PSRLW Uo Ib", "", "PSRAW Uo Ib", "", "PSLLW Uo Ib", ""},
										{"", "", "", "", "", "", "", ""},
										{"", "", "", "", "", "", "", ""}};

static const std::string group13[4][8] = {{"", "", "PSRLD Nq Ib", "", "PSRAD Nq Ib", "", "PSLLD Nq Ib", ""},
										{"", "", "PSRLD Uo Ib", "", "PSRAD Uo Ib", "", "PSLLD Uo Ib", ""},
										{"", "", "", "", "", "", "", ""},
										{"", "", "", "", "", "", "", ""}};

static const std::string group14[4][8] = {{"", "", "PSRLQ Nq Ib", "", "", "", "PSLLQ Nq Ib", ""},
										{"", "", "PSRLQ Uo Ib", "PSRLDQ Uo Ib", "", "", "PSLLQ Uo Ib", "PSLLDQ Uo Ib"},
										{"", "", "", "", "", "", "", ""},
										{"", "", "", "", "", "", "", ""}};

static const std::string group15[4][8] = {{"FXSAVE M", "FXRSTOR M", "LDMXCSR Md", "STMXCSR Md", "XSAVE M", "LFENCE5 XRSTOR M", "MFENCE5 XSAVE-OPT M", "SFENCE5 CLFLUSH Mb"},
										{"", "", "", "", "", "", "", ""},
										{"", "", "", "", "", "", "", ""},
										{"RDFSBASE Rv", "RDGSBASE Rv", "WRFSBASE Rv", "WRGSBASE Rv", "", "", "", ""}};

static const std::string group16[4][8] = {{"PREFETCH NTA","PREFETCH T0", "PREFETCH T1", "PREFETCH T2", "NOP", "NOP", "NOP", "NOP"},
										{"", "", "", "", "", "", "", ""},
										{"", "", "", "", "", "", "", ""},
										{"", "", "", "", "", "", "", ""}};

static const std::string group17[4][8] = {{"", "", "", "", "", "", "", ""},
										{"EXTRQ Vo.q Ib Ib", "", "", "", "", "", "", ""},
										{"", "", "", "", "", "", "", ""},
										{"", "", "", "", "", "", "", ""}};

static const std::string groupP[4][8] = {{"PREFETCH Exclusive", "PREFETCH Modified", "PREFETCH Reserved", "PREFETCH Modified", "PREFETCH Reserved", "PREFETCH Reserved", "PREFETCH Reserved", "PREFETCH Reserved"},
										{"", "", "", "", "", "", "", ""},
										{"", "", "", "", "", "", "", ""},
										{"", "", "", "", "", "", "", ""}};


enum modrm_mnemonic{reg8 = 0, reg16, reg32, reg64, mmx, xmm, ymm, sreg, creg, dreg};

static const std::string modrm_reg_map[10][16] = {{"AL", "CL","DL","BL","AH","CH","DH","BH","R8B","R9B","R10B","R11B","R12B","R13B","R14B","R15B"},
												{"AX", "CX","DX","BX","SP","BP","SI","DI","R8W","R9W","R10W","R11W","R12W","R13W","R14W","R15W"},
												{"EAX", "ECX","EDX","EBX","ESP","EBP","ESI","EDI","R8D","R9D","R10D","R11D","R12D","R13D","R14D","R15D"},
												{"RAX", "RCX","RDX","RBX","RSP","RBP","RSI","RDI","R8","R9","R10","R11","R12","R13","R14","R15"},
												{"MMX0", "MMX1","MMX2","MMX3","MMX4","MMX5","MMX6","MMX7","MMX0", "MMX1","MMX2","MMX3","MMX4","MMX5","MMX6","MMX7"},
												{"XMM0", "XMM1","XMM2","XMM3","XMM4","XMM5","XMM6","XMM7","XMM8","XMM9","XMM10","XMM11","XMM12","XMM13","XMM14","XMM15"},
												{"YMM0", "YMM1","YMM2","YMM3","YMM4","YMM5","YMM6","YMM7","YMM8","YMM9","YMM10","YMM11","YMM12","YMM13","YMM14","YMM15"},
												{"ES", "CS","SS","DS","FS","GS","","","ES", "CS","SS","DS","FS","GS","",""},
												{"CR0", "CR1","CR2","CR3","CR4","CR5","CR6","CR7","CR8","CR9","CR10","CR11","CR12","CR13","CR14","CR15"},
												{"DR0", "DR1","DR2","DR3","DR4","DR5","DR6","DR7","DR8","DR9","DR10","DR11","DR12","DR13","DR14","DR15"}};

static const std::string modrm_rm_map[] = {"RAX", "RCX","RDX","RBX","","RIP","RSI","RDI","RAX", "RCX","RDX","RBX","","RBP","RSI","RDI","RAX", "RCX","RDX","RBX","","RBP","RSI","RDI","","","","","","","","","R8","R9","R10","R11","","RIP","R14","R15","R8","R9","R10","R11","","R13","R14","R15","R8","R9","R10","R11","","R13","R14","R15","","","","","","","",""};

//rex.b + sib.index
static const std::string sib_byte_map[] = {"RAX", "RCX","RDX","RBX","RSP","RBP","RSI","RDI","R8","R9","R10","R11","R12","R13","R14","R15"};

static const std::string x87_low_map[8][8] = {{"FADD mem32real","FMUL mem32real","FCOM mem32real","FCOMP mem32real","FSUB mem32real","FSUBR mem32real","FDIV mem32real","FDIVR mem32real"},
												{"FLD mem32real","","FST mem32real","FSTP mem32real","FLDENV mem14env","FLDCW mem16","FNSTENV mem14env","FNSTCW mem16"},
												{"FIADD mem32int","FIMUL mem32int","FICOM mem32int","FICOMP mem32int","FISUB mem32int","FISUBR mem32int","FIDIV mem32int","FIDIVR mem32int"},
												{"FILD mem32int","FISTTP mem32int","FIST mem32int","FISTP mem32int","","FLD mem80real","","FSTP mem80real"},
												{"FADD mem64real","FMUL mem64real","FCOM mem64real","FCOMP mem64real","FSUB mem64real","FSUBR mem64real","FDIV mem64real","FDIVR mem64real"},
												{"FLD mem64real","FISTTP mem64real","FST mem64real","FSTP mem64real","FRSTOR mem98env","","FNSAVE mem98env","FNSTSW mem16"},
												{"FIADD mem16int","FIMUL mem16int","FICOM mem16int","FICOMP mem16int","FISUB mem16int","FISUBR mem16int","FIDIV mem16int","FIDIVR mem16int"},
												{"FILD mem16int","FISTTP mem16int","FIST mem16int","FISTP mem16int","FBLD mem80dec","FILD mem64int","FBSTP mem80dec","FISTP mem64int"}};

static const std::string x87_high_map[8][64] = {{"FADD ST(0) ST(0)","FADD ST(0) ST(1)","FADD ST(0) ST(2)","FADD ST(0) ST(3)","FADD ST(0) ST(4)","FADD ST(0) ST(5)","FADD ST(0) ST(6)","FADD ST(0) ST(7)","FMUL ST(0) ST(0)","FMUL ST(0) ST(1)","FMUL ST(0) ST(2)","FMUL ST(0) ST(3)","FMUL ST(0) ST(4)","FMUL ST(0) ST(5)","FMUL ST(0) ST(6)","FMUL ST(0) ST(7)","FCOM ST(0) ST(0)","FCOM ST(0) ST(1)","FCOM ST(0) ST(2)","FCOM ST(0) ST(3)","FCOM ST(0) ST(4)","FCOM ST(0) ST(5)","FCOM ST(0) ST(6)","FCOM ST(0) ST(7)","FCOMP ST(0) ST(0)","FCOMP ST(0) ST(1)","FCOMP ST(0) ST(2)","FCOMP ST(0) ST(3)","FCOMP ST(0) ST(4)","FCOMP ST(0) ST(5)","FCOMP ST(0) ST(6)","FCOMP ST(0) ST(7)","FSUB ST(0) ST(0)","FSUB ST(0) ST(1)","FSUB ST(0) ST(2)","FSUB ST(0) ST(3)","FSUB ST(0) ST(4)","FSUB ST(0) ST(5)","FSUB ST(0) ST(6)","FSUB ST(0) ST(7)","FSUBR ST(0) ST(0)","FSUBR ST(0) ST(1)","FSUBR ST(0) ST(2)","FSUBR ST(0) ST(3)","FSUBR ST(0) ST(4)","FSUBR ST(0) ST(5)","FSUBR ST(0) ST(6)","FSUBR ST(0) ST(7)","FDIV ST(0) ST(0)","FDIV ST(0) ST(1)","FDIV ST(0) ST(2)","FDIV ST(0) ST(3)","FDIV ST(0) ST(4)","FDIV ST(0) ST(5)","FDIV ST(0) ST(6)","FDIV ST(0) ST(7)","FDIVR ST(0) ST(0)","FDIVR ST(0) ST(1)","FDIVR ST(0) ST(2)","FDIVR ST(0) ST(3)","FDIVR ST(0) ST(4)","FDIVR ST(0) ST(5)","FDIVR ST(0) ST(6)","FDIVR ST(0) ST(7)"},
												{"FLD ST(0) ST(0)","FLD ST(0) ST(1)","FLD ST(0) ST(2)","FLD ST(0) ST(3)","FLD ST(0) ST(4)","FLD ST(0) ST(5)","FLD ST(0) ST(6)","FLD ST(0) ST(7)","FXCH ST(0) ST(0)","FXCH ST(0) ST(1)","FXCH ST(0) ST(2)","FXCH ST(0) ST(3)","FXCH ST(0) ST(4)","FXCH ST(0) ST(5)","FXCH ST(0) ST(6)","FXCH ST(0) ST(7)","FNOP","","","","","","","","","","","","","","","","FCHS","FABS","","","FTST","FXAM","","","FLD1","FLDL2T","FLDL2E","FLDPI","FLDLG2","FLDLN2","FLDZ","","F2XM1","FYL2X","FPTAN","FPATAN","FXTRACT","FPREM1","FDECSTP","FINCSTP","FPREM","FYL2XP1","FSQRT","FSINCOS","FRNDINT","FSCALE","FSIN","FCOS"},
												{"FCMOVB ST(0) ST(0)","FCMOVB ST(0) ST(1)","FCMOVB ST(0) ST(2)","FCMOVB ST(0) ST(3)","FCMOVB ST(0) ST(4)","FCMOVB ST(0) ST(5)","FCMOVB ST(0) ST(6)","FCMOVB ST(0) ST(7)","FCMOVE ST(0) ST(0)","FCMOVE ST(0) ST(1)","FCMOVE ST(0) ST(2)","FCMOVE ST(0) ST(3)","FCMOVE ST(0) ST(4)","FCMOVE ST(0) ST(5)","FCMOVE ST(0) ST(6)","FCMOVE ST(0) ST(7)","FCMOVBE ST(0) ST(0)","FCMOVBE ST(0) ST(1)","FCMOVBE ST(0) ST(2)","FCMOVBE ST(0) ST(3)","FCMOVBE ST(0) ST(4)","FCMOVBE ST(0) ST(5)","FCMOVBE ST(0) ST(6)","FCMOVBE ST(0) ST(7)","FCMOVU ST(0) ST(0)","FCMOVU ST(0) ST(1)","FCMOVU ST(0) ST(2)","FCMOVU ST(0) ST(3)","FCMOVU ST(0) ST(4)","FCMOVU ST(0) ST(5)","FCMOVU ST(0) ST(6)","FCMOVU ST(0) ST(7)","","","","","","","","","","FUCOMPP","","","","","","","","","","","","","","","","","","","","","",""},
												{"FCMOVNB ST(0) ST(0)","FCMOVNB ST(0) ST(1)","FCMOVNB ST(0) ST(2)","FCMOVNB ST(0) ST(3)","FCMOVNB ST(0) ST(4)","FCMOVNB ST(0) ST(5)","FCMOVNB ST(0) ST(6)","FCMOVNB ST(0) ST(7)","FCMOVNE ST(0) ST(0)","FCMOVNE ST(0) ST(1)","FCMOVNE ST(0) ST(2)","FCMOVNE ST(0) ST(3)","FCMOVNE ST(0) ST(4)","FCMOVNE ST(0) ST(5)","FCMOVNE ST(0) ST(6)","FCMOVNE ST(0) ST(7)","FCMOVNBE ST(0) ST(0)","FCMOVNBE ST(0) ST(1)","FCMOVNBE ST(0) ST(2)","FCMOVNBE ST(0) ST(3)","FCMOVNBE ST(0) ST(4)","FCMOVNBE ST(0) ST(5)","FCMOVNBE ST(0) ST(6)","FCMOVNBE ST(0) ST(7)","FCMOVNU ST(0) ST(0)","FCMOVNU ST(0) ST(1)","FCMOVNU ST(0) ST(2)","FCMOVNU ST(0) ST(3)","FCMOVNU ST(0) ST(4)","FCMOVNU ST(0) ST(5)","FCMOVNU ST(0) ST(6)","FCMOVNU ST(0) ST(7)","","","FNCLEX","FNINIT","","","","","FUCOMI ST(0) ST(0)","FUCOMI ST(0) ST(1)","FUCOMI ST(0) ST(2)","FUCOMI ST(0) ST(3)","FUCOMI ST(0) ST(4)","FUCOMI ST(0) ST(5)","FUCOMI ST(0) ST(6)","FUCOMI ST(0) ST(7)","FCOMI ST(0) ST(0)","FCOMI ST(0) ST(1)","FCOMI ST(0) ST(2)","FCOMI ST(0) ST(3)","FCOMI ST(0) ST(4)","FCOMI ST(0) ST(5)","FCOMI ST(0) ST(6)","FCOMI ST(0) ST(7)","","","","","","","",""},
												{"FADD ST(0) ST(0)","FADD ST(1) ST(0)","FADD ST(2) ST(0)","FADD ST(3) ST(0)","FADD ST(4) ST(0)","FADD ST(5) ST(0)","FADD ST(6) ST(0)","FADD ST(7) ST(0)","FMUL ST(0) ST(0)","FMUL ST(1) ST(0)","FMUL ST(2) ST(0)","FMUL ST(3) ST(0)","FMUL ST(4) ST(0)","FMUL ST(5) ST(0)","FMUL ST(6) ST(0)","FMUL ST(7) ST(0)","","","","","","","","","","","","","","","","","FSUBR ST(0) ST(0)","FSUBR ST(1) ST(0)","FSUBR ST(2) ST(0)","FSUBR ST(3) ST(0)","FSUBR ST(4) ST(0)","FSUBR ST(5) ST(0)","FSUBR ST(6) ST(0)","FSUBR ST(7) ST(0)","FSUB ST(0) ST(0)","FSUB ST(1) ST(0)","FSUB ST(2) ST(0)","FSUB ST(3) ST(0)","FSUB ST(4) ST(0)","FSUB ST(5) ST(0)","FSUB ST(6) ST(0)","FSUB ST(7) ST(0)","FDIVR ST(0) ST(0)","FDIVR ST(1) ST(0)","FDIVR ST(2) ST(0)","FDIVR ST(3) ST(0)","FDIVR ST(4) ST(0)","FDIVR ST(5) ST(0)","FDIVR ST(6) ST(0)","FDIVR ST(7) ST(0)","FDIV ST(0) ST(0)","FDIV ST(1) ST(0)","FDIV ST(2) ST(0)","FDIV ST(3) ST(0)","FDIV ST(4) ST(0)","FDIV ST(5) ST(0)","FDIV ST(6) ST(0)","FDIV ST(7) ST(0)"},
												{"FFREE ST(0)","FFREE ST(1)","FFREE ST(2)","FFREE ST(3)","FFREE ST(4)","FFREE ST(5)","FFREE ST(6)","FFREE ST(7)","","","","","","","","","FST (0)","FST (1)","FST (2)","FST (3)","FST (4)","FST (5)","FST (6)","FST (7)","FSTP (0)","FSTP (1)","FSTP (2)","FSTP (3)","FSTP (4)","FSTP (5)","FSTP (6)","FSTP (7)","FUCOM ST(0) ST(0)","FUCOM ST(1) ST(0)","FUCOM ST(2) ST(0)","FUCOM ST(3) ST(0)","FUCOM ST(4) ST(0)","FUCOM ST(5) ST(0)","FUCOM ST(6) ST(0)","FUCOM ST(7) ST(0)","FUCOMP ST(0)","FUCOMP ST(1)","FUCOMP ST(2)","FUCOMP ST(3)","FUCOMP ST(4)","FUCOMP ST(5)","FUCOMP ST(6)","FUCOMP ST(7)","","","","","","","","","","","","","","","",""},
												{"FADDP ST(0) ST(0)","FADDP ST(1) ST(0)","FADDP ST(2) ST(0)","FADDP ST(3) ST(0)","FADDP ST(4) ST(0)","FADDP ST(5) ST(0)","FADDP ST(6) ST(0)","FADDP ST(7) ST(0)","FMULP ST(0) ST(0)","FMULP ST(1) ST(0)","FMULP ST(2) ST(0)","FMULP ST(3) ST(0)","FMULP ST(4) ST(0)","FMULP ST(5) ST(0)","FMULP ST(6) ST(0)","FMULP ST(7) ST(0)","","","","","","","","","","","","","","","","","FSUBRP ST(0) ST(0)","FSUBRP ST(1) ST(0)","FSUBRP ST(2) ST(0)","FSUBRP ST(3) ST(0)","FSUBRP ST(4) ST(0)","FSUBRP ST(5) ST(0)","FSUBRP ST(6) ST(0)","FSUBRP ST(7) ST(0)","FSUBP ST(0) ST(0)","FSUBP ST(1) ST(0)","FSUBP ST(2) ST(0)","FSUBP ST(3) ST(0)","FSUBP ST(4) ST(0)","FSUBP ST(5) ST(0)","FSUBP ST(6) ST(0)","FSUBP ST(7) ST(0)","FDIVRP ST(0) ST(0)","FDIVRP ST(1) ST(0)","FDIVRP ST(2) ST(0)","FDIVRP ST(3) ST(0)","FDIVRP ST(4) ST(0)","FDIVRP ST(5) ST(0)","FDIVRP ST(6) ST(0)","FDIVRP ST(7) ST(0)","FDIVP ST(0) ST(0)","FDIVP ST(1) ST(0)","FDIVP ST(2) ST(0)","FDIVP ST(3) ST(0)","FDIVP ST(4) ST(0)","FDIVP ST(5) ST(0)","FDIVP ST(6) ST(0)","FDIVP ST(7) ST(0)"},
												{"","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","FNSTSW AX","","","","","","","","FUCOMIP ST(0) ST(0)","FUCOMIP ST(0) ST(1)","FUCOMIP ST(0) ST(2)","FUCOMIP ST(0) ST(3)","FUCOMIP ST(0) ST(4)","FUCOMIP ST(0) ST(5)","FUCOMIP ST(0) ST(6)","FUCOMIP ST(0) ST(7)","FCOMIP ST(0) ST(0)","FCOMIP ST(0) ST(1)","FCOMIP ST(0) ST(2)","FCOMIP ST(0) ST(3)","FCOMIP ST(0) ST(4)","FCOMIP ST(0) ST(5)","FCOMIP ST(0) ST(6)","FCOMIP ST(0) ST(7)","","","","","","","",""}};
