static const string primary_opcode_map32[] = ["ADD Eb, Gb","ADD Ev, Gv","ADD Gb, Eb","ADD Gv, Ev","ADD AL, Ib","ADD EAX, Iz","PUSH ES","POP ES","OR Eb, Gb","OR Ev, Gv","OR Gb, Eb","OR Gv, Ev","OR AL, Ib","OR EAX, Iz","PUSH CS","ESC secondary",
								"ADC Eb, Gb","ADC Ev, Gv","ADC Gb, Eb","ADC Gv, Ev","ADC AL, Ib","ADC EAX, Iz","PUSH SS","POP SS","SBB Eb, Gb","SBB Ev, Gv","SBB Gb, Eb","SBB Gv, Ev","SBB AL, Ib","SBB EAX, Iz","PUSH DS","POP DS",
								"AND Eb, Gb","AND Ev, Gv","AND Gb, Eb","AND Gv, Ev","AND AL, Ib","AND EAX, Iz","SEG ES","DAA","SUB Eb, Gb","SUB Ev, Gv","SUB Gb, Eb","SUB Gv, Ev","SUB AL, Ib","SUB EAX, Iz","SEG CS","DAS",
								"XOR Eb, Gb","XOR Ev, Gv","XOR Gb, Eb","XOR Gv, Ev","XOR AL, Ib","XOR EAX, Iz","SEG SS","AAA","CMP Eb, Gb","CMP Ev, Gv","CMP Gb, Eb","CMP Gv, Ev","CMP AL, Ib","CMP EAX, Iz","SEG DS","AAS",
								"INC EAX","INC ECX","INC EDX","INC EBX","INC ESP","INC EBP","INC ESI","INC EDI","DEC EAX","DEC ECX","DEC EDX","DEC EBX","DEC ESP","DEC EBP","DEC ESI","DEC EDI",
								"PUSH EAX","PUSH ECX","PUSH EDX","PUSH EBX","PUSH ESP","PUSH EBP","PUSH ESI","PUSH EDI","POP EAX","POP ECX","POP EDX","POP EBX","POP ESP","POP EBP","POP ESI","POP EDI",
								"PUSHA","POPA","BOUND Gv, Ma","ARPL Ew, Gw","PRE FS","PRE GS","PRE OSO","PRE ASO","PUSH Iz","IMUL Gv, Ev, Iz","PUSH Ib", "IMUL Gv, Ev,Ib","INSB Yb, DX","INSW Yz, DX","OUTS DX, Xb","OUTS DX,Xz",
								"JO Jb","JNO Jb","JB Jb","JNB Jb","JZ Jb","JNZ Jb","JBE Jb","JNBE Jb","JS Jb","JNS Jb","JP Jb","JNP Jb","JL Jb","JNL Jb","JLE Jb","JNLE Jb",
								"GROUP 1","GROUP 1","GROUP 1","GROUP 1","TEST Eb, Gb","TEST Ev, Gv","XCHG Eb, Gb","XCHG Ev, Gv","MOV Eb, Gb","MOV Ev, Gv","MOV Gb, Eb","MOV Gv,Ev","MOV Mw, Sw","LEA Gv, M","MOV Sw, Ew","GROUP 1A",
								"NOP","XCHG ECX, EAX","XCHG EDX, EAX","XCHG EBX, EAX","XCHG ESP, EAX","XCHG EBP, EAX","XCHG ESI, EAX","XCHG EDI, EAX","CBW","CWD","CALL Ap","WAIT","PUSHF Fv","POPF Fv","SAHF","LAHF",
								"MOV AL, Ob","MOV EAX, Ov","MOV Ob, AL","MOV Ob, EAX","MOVSB Yb, Xb","MOVSW Yv, Xv","CMPSB Xb, Yb","CMPSW Xv, Yv","TEST AL, Ib","TEST EAX, Iz","STOSB Yb, AL","STOSW Yv, EAX","LODSB AL, Xb","LODSW EAX, Xv","SCASB Al, Yb","SCASW EAX, Yv",
								"MOV AL, Ib","MOV CL, Ib","MOV DL, Ib","MOV BL, IB","MOV AH, Ib","MOV CH, Ib","MOV DH, Ib","MOV BH, Ib","MOV EAX, Iv","MOV EAX, ECX, Iv","MOV EDX, Iv","MOV EBX, Iv","MOV ESP, Iv","MOV EBP, Iv","MOV ESI, Iv","MOV EDI, Iv",
								"GROUP 2","GROUP 2","RET Iw","RET","LES GZ, Mp","LDS Gz, Mp","GROUP 11","GROUP 11","ENTER Iw, Ib","LEAVE","RET Iw","RET","INT3","INT Ib","INTO","IRET",
								"GROUP 2","GROUP 2","GROUP 2","GROUP 2","AAM Ib","AAD Ib","","XLAT","ESC x87","ESC x87","ESC x87","ESC x87","ESC x87","ESC x87","ESC x87","ESC x87",
								"LOOPNE Jb","LOOPE Jb","LOOP Jb","JrCXZ Jb","IN AL, Ib","IN EAX, Ib","OUT Ib, AL","OUT Ib, EAX","CALL Jz","JMP Jz","JMP Ap","JMP Jb","IN AL, DX","IN EAX, DX","OUT DX, AL","OUT DX, EAX",
								"PRE LOCK","INT1","PRE REPNE","PRE REP","HLT","CMC","GROUP 3","GROUP 3","CLC","STC","CLI","STI","CLD","STD","GROUP 4","GROUP 5"];
								

static const string primary_opcode_map64[] = ["ADD Eb, Gb","ADD Ev, Gv","ADD Gb, Eb","ADD Gv, Ev","ADD AL, Ib","ADD RAX, Iz","","","OR Eb, Gb","OR Ev, Gv","OR Gb, Eb","OR Gv, Ev","OR AL, Ib","OR RAX, Iz","","ESC secondary",
								"ADC Eb, Gb","ADC Ev, Gv","ADC Gb, Eb","ADC Gv, Ev","ADC AL, Ib","ADC RAX, Iz","","","SBB Eb, Gb","SBB Ev, Gv","SBB Gb, Eb","SBB Gv, Ev","SBB AL, Ib","SBB RAX, Iz","","",
								"AND Eb, Gb","AND Ev, Gv","AND Gb, Eb","AND Gv, Ev","AND AL, Ib","AND RAX, Iz","PRE NULL","","SUB Eb, Gb","SUB Ev, Gv","SUB Gb, Eb","SUB Gv, Ev","SUB AL, Ib","SUB RAX, Iz","PRE NULL","",
								"XOR Eb, Gb","XOR Ev, Gv","XOR Gb, Eb","XOR Gv, Ev","XOR AL, Ib","XOR RAX, Iz","PRE NULL","","CMP Eb, Gb","CMP Ev, Gv","CMP Gb, Eb","CMP Gv, Ev","CMP AL, Ib","CMP RAX, Iz","PRE NULL","",
								"PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX","PRE REX",
								"PUSH RAX","PUSH RCX","PUSH RDX","PUSH RBX","PUSH RSP","PUSH RBP","PUSH RSI","PUSH RDI","POP RAX","POP RCX","POP RDX","POP RBX","POP RSP","POP RBP","POP RSI","POP RDI",
								"","","","MOVSXD Gv, Ez","PRE FS","PRE GS","PRE OSO","PRE ASO","PUSH Iz","IMUL Gv, Ev, Iz","PUSH Ib", "IMUL Gv, Ev,Ib","INSB Yb, DX","INSW Yz, DX","OUTS DX, Xb","OUTS DX,Xz",
								"JO Jb","JNO Jb","JB Jb","JNB Jb","JZ Jb","JNZ Jb","JBE Jb","JNBE Jb","JS Jb","JNS Jb","JP Jb","JNP Jb","JL Jb","JNL Jb","JLE Jb","JNLE Jb",
								"GROUP 1","GROUP 1","","GROUP 1","TEST Eb, Gb","TEST Ev, Gv","XCHG Eb, Gb","XCHG Ev, Gv","MOV Eb, Gb","MOV Ev, Gv","MOV Gb, Eb","MOV Gv,Ev","MOV Mw, Sw","LEA Gv, M","MOV Sw, Ew","GROUP 1A",
								"XCHG r8, RAX","XCHG RCX, RAX","XCHG RDX, RAX","XCHG RBX, RAX","XCHG RSP, RAX","XCHG RBP, RAX","XCHG RSI, RAX","XCHG RDI, RAX","CBW","CWD","","WAIT","PUSHF Fv","POPF Fv","SAHF","LAHF",
								"MOV AL, Ob","MOV RAX, Ov","MOV Ob, AL","MOV Ob, RAX","MOVSB Yb, Xb","MOVSW Yv, Xv","CMPSB Xb, Yb","CMPSW Xv, Yv","TEST AL, Ib","TEST RAX, Iz","STOSB Yb, AL","STOSW Yv, RAX","LODSB AL, Xb","LODSW RAX, Xv","SCASB Al, Yb","SCASW RAX, Yv",
								"MOV AL, Ib","MOV CL, Ib","MOV DL, Ib","MOV BL, IB","MOV AH, Ib","MOV CH, Ib","MOV DH, Ib","MOV BH, Ib","MOV RAX, Iv","MOV RAX, RCX, Iv","MOV RDX, Iv","MOV RBX, Iv","MOV RSP, Iv","MOV RBP, Iv","MOV RSI, Iv","MOV RDI, Iv",
								"GROUP 2","GROUP 2","RET Iw","RET","ESC VEX","ESC VEX","GROUP 11","GROUP 11","ENTER Iw, Ib","LEAVE","RET Iw","RET","INT3","INT Ib","INTO","IRET",
								"GROUP 2","GROUP 2","GROUP 2","GROUP 2","","","","XLAT","ESC x87","ESC x87","ESC x87","ESC x87","ESC x87","ESC x87","ESC x87","ESC x87",
								"LOOPNE Jb","LOOPE Jb","LOOP Jb","JrCXZ Jb","IN AL, Ib","IN EAX, Ib","OUT Ib, AL","OUT Ib, EAX","CALL Jz","JMP Jz","","JMP Jb","IN AL, DX","IN EAX, DX","OUT DX, AL","OUT DX, EAX",
								"PRE LOCK","INT1","PRE REPNE","PRE REP","HLT","CMC","GROUP 3","GROUP 3","CLC","STC","CLI","STI","CLD","STD","GROUP 4","GROUP 5"];
