struct optcode opt_table[] = {
  { "ADC #x", 0x69, 4, 0 },
  { "ADC (x)", 0x72, 0xA, 0 },
  { "ADC [x]", 0x67, 0xA, 0 },
  { "ADC (x,X)", 0x61, 0xA, 0 },
  { "ADC (x),Y", 0x71, 0xA, 0 },
  { "ADC (x,S),Y", 0x73, 0xA, 0 },
  { "ADC [x],Y", 0x77, 0xA, 0 },
  { "ADC x", 0x65, 0xA, 2 },
  { "ADC ?", 0x6D, 2, 1 },
  { "ADC &", 0x6F, 3, 0 },
  { "ADC x,X", 0x75, 0xA, 2 },
  { "ADC ?,X", 0x7D, 2, 1 },
  { "ADC &,X", 0x7F, 3, 0 },
  { "ADC ?,Y", 0x79, 2, 0 },
  { "ADC x,S", 0x63, 0xA, 0 },
  { "ADC.B #x", 0x69, 0xA, 0 },
  { "ADC.W #?", 0x69, 2, 0 },
  { "ADC.B (x)", 0x72, 0xA, 0 },
  { "ADC.B [x]", 0x67, 0xA, 0 },
  { "ADC.B (x,X)", 0x61, 0xA, 0 },
  { "ADC.B (x),Y", 0x71, 0xA, 0 },
  { "ADC.B (x,S),Y", 0x73, 0xA, 0 },
  { "ADC.B [x],Y", 0x77, 0xA, 0 },
  { "ADC.B x", 0x65, 0xA, 0 },
  { "ADC.W ?", 0x6D, 2, 0 },
  { "ADC.L &", 0x6F, 3, 0 },
  { "ADC.B x,X", 0x75, 0xA, 0 },
  { "ADC.W ?,X", 0x7D, 2, 0 },
  { "ADC.L &,X", 0x7F, 3, 0 },
  { "ADC.W ?,Y", 0x79, 2, 0 },
  { "ADC.B x,S", 0x63, 0xA, 0 },

  { "AND #x", 0x29, 4, 0 },
  { "AND (x)", 0x32, 0xA, 0 },
  { "AND [x]", 0x27, 0xA, 0 },
  { "AND (x,X)", 0x21, 0xA, 0 },
  { "AND (x),Y", 0x31, 0xA, 0 },
  { "AND (x,S),Y", 0x33, 0xA, 0 },
  { "AND [x],Y", 0x37, 0xA, 0 },
  { "AND x", 0x25, 0xA, 2 },
  { "AND ?", 0x2D, 2, 1 },
  { "AND &", 0x2F, 3, 0 },
  { "AND x,X", 0x35, 0xA, 2 },
  { "AND ?,X", 0x3D, 2, 1 },
  { "AND &,X", 0x3F, 3, 0 },
  { "AND ?,Y", 0x39, 2, 0 },
  { "AND x,S", 0x23, 0xA, 0 },
  { "AND.B #x", 0x29, 0xA, 0 },
  { "AND.W #?", 0x29, 2, 0 },
  { "AND.B (x)", 0x32, 0xA, 0 },
  { "AND.B [x]", 0x27, 0xA, 0 },
  { "AND.B (x,X)", 0x21, 0xA, 0 },
  { "AND.B (x),Y", 0x31, 0xA, 0 },
  { "AND.B (x,S),Y", 0x33, 0xA, 0 },
  { "AND.B [x],Y", 0x37, 0xA, 0 },
  { "AND.B x", 0x25, 0xA, 0 },
  { "AND.W ?", 0x2D, 2, 0 },
  { "AND.L &", 0x2F, 3, 0 },
  { "AND.B x,X", 0x35, 0xA, 0 },
  { "AND.W ?,X", 0x3D, 2, 0 },
  { "AND.L &,X", 0x3F, 3, 0 },
  { "AND.W ?,Y", 0x39, 2, 0 },
  { "AND.B x,S", 0x23, 0xA, 0 },

  { "ASL A", 0x0A, 0, 0 },
  { "ASL", 0x0A, 0, 0 },
  { "ASL x", 0x06, 0xA, 2 },
  { "ASL ?", 0x0E, 2, 0 },
  { "ASL x,X", 0x16, 0xA, 2 },
  { "ASL ?,X", 0x1E, 2, 0 },
  { "ASL.B x", 0x06, 0xA, 0 },
  { "ASL.W ?", 0x0E, 2, 0 },
  { "ASL.B x,X", 0x16, 0xA, 0 },
  { "ASL.W ?,X", 0x1E, 2, 0 },

  { "BCC x", 0x90, 11, 0 },
  { "BCS x", 0xB0, 11, 0 },
  { "BEQ x", 0xF0, 11, 0 },
  { "BNE x", 0xD0, 11, 0 },
  { "BMI x", 0x30, 11, 0 },
  { "BPL x", 0x10, 11, 0 },
  { "BVC x", 0x50, 11, 0 },
  { "BVS x", 0x70, 11, 0 },
  { "BRA x", 0x80, 11, 0 },
  { "BRL ?", 0x82, 9, 0 },
  { "BCC.B x", 0x90, 11, 0 },
  { "BCS.B x", 0xB0, 11, 0 },
  { "BEQ.B x", 0xF0, 11, 0 },
  { "BNE.B x", 0xD0, 11, 0 },
  { "BMI.B x", 0x30, 11, 0 },
  { "BPL.B x", 0x10, 11, 0 },
  { "BVC.B x", 0x50, 11, 0 },
  { "BVS.B x", 0x70, 11, 0 },
  { "BRA.B x", 0x80, 11, 0 },
  { "BRL.W ?", 0x82, 9, 0 },

  { "BIT #x", 0x89, 4, 0 },
  { "BIT x", 0x24, 0xA, 2 },
  { "BIT ?", 0x2C, 2, 0 },
  { "BIT x,X", 0x34, 0xA, 2 },
  { "BIT ?,X", 0x3C, 2, 0 },
  { "BIT.B #x", 0x89, 0xA, 0 },
  { "BIT.W #?", 0x89, 2, 0 },
  { "BIT.B x", 0x24, 0xA, 0 },
  { "BIT.W ?", 0x2C, 2, 0 },
  { "BIT.B x,X", 0x34, 0xA, 0 },
  { "BIT.W ?,X", 0x3C, 2, 0 },

  { "BRK x", 0x00, 0xA, 0 },
  { "BRK.B x", 0x00, 0xA, 0 },
  { "BRK", 0x0000, 8, 0 },

  { "CLC", 0x18, 0, 0 },
  { "CLD", 0xD8, 0, 0 },
  { "CLI", 0x58, 0, 0 },
  { "CLV", 0xB8, 0, 0 },

  { "CMP #x", 0xC9, 4, 0 },
  { "CMP (x)", 0xD2, 0xA, 0 },
  { "CMP [x]", 0xC7, 0xA, 0 },
  { "CMP (x,X)", 0xC1, 0xA, 0 },
  { "CMP (x),Y", 0xD1, 0xA, 0 },
  { "CMP (x,S),Y", 0xD3, 0xA, 0 },
  { "CMP [x],Y", 0xD7, 0xA, 0 },
  { "CMP x", 0xC5, 0xA, 2 },
  { "CMP ?", 0xCD, 2, 1 },
  { "CMP &", 0xCF, 3, 0 },
  { "CMP x,X", 0xD5, 0xA, 2 },
  { "CMP ?,X", 0xDD, 2, 1 },
  { "CMP &,X", 0xDF, 3, 0 },
  { "CMP ?,Y", 0xD9, 2, 0 },
  { "CMP x,S", 0xC3, 0xA, 0 },
  { "CMP.B #x", 0xC9, 0xA, 0 },
  { "CMP.W #?", 0xC9, 2, 0 },
  { "CMP.B (x)", 0xD2, 0xA, 0 },
  { "CMP.B [x]", 0xC7, 0xA, 0 },
  { "CMP.B (x,X)", 0xC1, 0xA, 0 },
  { "CMP.B (x),Y", 0xD1, 0xA, 0 },
  { "CMP.B (x,S),Y", 0xD3, 0xA, 0 },
  { "CMP.B [x],Y", 0xD7, 0xA, 0 },
  { "CMP.B x", 0xC5, 0xA, 0 },
  { "CMP.W ?", 0xCD, 2, 0 },
  { "CMP.L &", 0xCF, 3, 0 },
  { "CMP.B x,X", 0xD5, 0xA, 0 },
  { "CMP.W ?,X", 0xDD, 2, 0 },
  { "CMP.L &,X", 0xDF, 3, 0 },
  { "CMP.W ?,Y", 0xD9, 2, 0 },
  { "CMP.B x,S", 0xC3, 0xA, 0 },

  { "COP x", 0x02, 0xA, 0 },
  { "COP.B x", 0x02, 0xA, 0 },
  { "COP", 0x0200, 8, 0 },

  { "CPX #x", 0xE0, 7, 0 },
  { "CPX x", 0xE4, 0xA, 2 },
  { "CPX ?", 0xEC, 2, 0 },
  { "CPX.B #x", 0xE0, 0xA, 0 },
  { "CPX.W #?", 0xE0, 2, 0 },
  { "CPX.B x", 0xE4, 0xA, 0 },
  { "CPX.W ?", 0xEC, 2, 0 },

  { "CPY #x", 0xC0, 7, 0 },
  { "CPY x", 0xC4, 0xA, 2 },
  { "CPY ?", 0xCC, 2, 0 },
  { "CPY.B #x", 0xC0, 0xA, 0 },
  { "CPY.W #?", 0xC0, 2, 0 },
  { "CPY.B x", 0xC4, 0xA, 0 },
  { "CPY.W ?", 0xCC, 2, 0 },

  { "DEA", 0x3A, 0, 0 },
  { "DEX", 0xCA, 0, 0 },
  { "DEY", 0x88, 0, 0 },
  { "DEC A", 0x3A, 0, 0 },
  { "DEC x", 0xC6, 0xA, 2 },
  { "DEC ?", 0xCE, 2, 0 },
  { "DEC x,X", 0xD6, 0xA, 2 },
  { "DEC ?,X", 0xDE, 2, 0 },
  { "DEC.B x", 0xC6, 0xA, 0 },
  { "DEC.W ?", 0xCE, 2, 0 },
  { "DEC.B x,X", 0xD6, 0xA, 0 },
  { "DEC.W ?,X", 0xDE, 2, 0 },

  { "EOR #x", 0x49, 4, 0 },
  { "EOR (x)", 0x52, 0xA, 0 },
  { "EOR [x]", 0x47, 0xA, 0 },
  { "EOR (x,X)", 0x41, 0xA, 0 },
  { "EOR (x),Y", 0x51, 0xA, 0 },
  { "EOR (x,S),Y", 0x53, 0xA, 0 },
  { "EOR [x],Y", 0x57, 0xA, 0 },
  { "EOR x", 0x45, 0xA, 2 },
  { "EOR ?", 0x4D, 2, 1 },
  { "EOR &", 0x4F, 3, 0 },
  { "EOR x,X", 0x55, 0xA, 2 },
  { "EOR ?,X", 0x5D, 2, 1 },
  { "EOR &,X", 0x5F, 3, 0 },
  { "EOR ?,Y", 0x59, 2, 0 },
  { "EOR x,S", 0x43, 0xA, 0 },
  { "EOR.B #x", 0x49, 0xA, 0 },
  { "EOR.W #?", 0x49, 2, 0 },
  { "EOR.B (x)", 0x52, 0xA, 0 },
  { "EOR.B [x]", 0x47, 0xA, 0 },
  { "EOR.B (x,X)", 0x41, 0xA, 0 },
  { "EOR.B (x),Y", 0x51, 0xA, 0 },
  { "EOR.B (x,S),Y", 0x53, 0xA, 0 },
  { "EOR.B [x],Y", 0x57, 0xA, 0 },
  { "EOR.B x", 0x45, 0xA, 0 },
  { "EOR.W ?", 0x4D, 2, 0 },
  { "EOR.L &", 0x4F, 3, 0 },
  { "EOR.B x,X", 0x55, 0xA, 0 },
  { "EOR.W ?,X", 0x5D, 2, 0 },
  { "EOR.L &,X", 0x5F, 3, 0 },
  { "EOR.W ?,Y", 0x59, 2, 0 },
  { "EOR.B x,S", 0x43, 0xA, 0 },

  { "INA", 0x1A, 0, 0 },
  { "INX", 0xE8, 0, 0 },
  { "INY", 0xC8, 0, 0 },
  { "INC A", 0x1A, 0, 0 },
  { "INC x", 0xE6, 0xA, 2 },
  { "INC ?", 0xEE, 2, 0 },
  { "INC x,X", 0xF6, 0xA, 2 },
  { "INC ?,X", 0xFE, 2, 0 },
  { "INC.B x", 0xE6, 0xA, 0 },
  { "INC.W ?", 0xEE, 2, 0 },
  { "INC.B x,X", 0xF6, 0xA, 0 },
  { "INC.W ?,X", 0xFE, 2, 0 },

  { "JMP (?)", 0x6C, 2, 0 },
  { "JMP (?,X)", 0x7C, 2, 0 },
  { "JMP [?]", 0xDC, 2, 0 },
  { "JML [?]", 0xDC, 2, 0 },
  { "JMP ?", 0x4C, 2, 1 },
  { "JMP &", 0x5C, 3, 0 },
  { "JML &", 0x5C, 3, 0 },
  { "JMP.W (?)", 0x6C, 2, 0 },
  { "JMP.W (?,X)", 0x7C, 2, 0 },
  { "JMP.W [?]", 0xDC, 2, 0 },
  { "JML.W [?]", 0xDC, 2, 0 },
  { "JMP.W ?", 0x4C, 2, 0 },
  { "JMP.L &", 0x5C, 3, 0 },
  { "JML.L &", 0x5C, 3, 0 },

  { "JSR (?,X)", 0xFC, 2, 0 },
  { "JSR ?", 0x20, 2, 1 },
  { "JSR &", 0x22, 3, 0 },
  { "JSL &", 0x22, 3, 0 },
  { "JSR.W (?,X)", 0xFC, 2, 0 },
  { "JSR.W ?", 0x20, 2, 0 },
  { "JSR.L &", 0x22, 3, 0 },
  { "JSL.L &", 0x22, 3, 0 },

  { "LDA #x", 0xA9, 4, 0 },
  { "LDA (x)", 0xB2, 0xA, 0 },
  { "LDA [x]", 0xA7, 0xA, 0 },
  { "LDA (x,X)", 0xA1, 0xA, 0 },
  { "LDA (x),Y", 0xB1, 0xA, 0 },
  { "LDA (x,S),Y", 0xB3, 0xA, 0 },
  { "LDA [x],Y", 0xB7, 0xA, 0 },
  { "LDA x", 0xA5, 0xA, 2 },
  { "LDA ?", 0xAD, 2, 1 },
  { "LDA &", 0xAF, 3, 0 },
  { "LDA x,X", 0xB5, 0xA, 2 },
  { "LDA ?,X", 0xBD, 2, 1 },
  { "LDA &,X", 0xBF, 3, 0 },
  { "LDA ?,Y", 0xB9, 2, 0 },
  { "LDA x,S", 0xA3, 0xA, 0 },
  { "LDA.B #x", 0xA9, 0xA, 0 },
  { "LDA.W #?", 0xA9, 2, 0 },
  { "LDA.B (x)", 0xB2, 0xA, 0 },
  { "LDA.B [x]", 0xA7, 0xA, 0 },
  { "LDA.B (x,X)", 0xA1, 0xA, 0 },
  { "LDA.B (x),Y", 0xB1, 0xA, 0 },
  { "LDA.B (x,S),Y", 0xB3, 0xA, 0 },
  { "LDA.B [x],Y", 0xB7, 0xA, 0 },
  { "LDA.B x", 0xA5, 0xA, 0 },
  { "LDA.W ?", 0xAD, 2, 0 },
  { "LDA.L &", 0xAF, 3, 0 },
  { "LDA.B x,X", 0xB5, 0xA, 0 },
  { "LDA.W ?,X", 0xBD, 2, 0 },
  { "LDA.L &,X", 0xBF, 3, 0 },
  { "LDA.W ?,Y", 0xB9, 2, 0 },
  { "LDA.B x,S", 0xA3, 0xA, 0 },

  { "LDX #x", 0xA2, 7, 0 },
  { "LDX x", 0xA6, 0xA, 2 },
  { "LDX ?", 0xAE, 2, 0 },
  { "LDX x,Y", 0xB6, 0xA, 2 },
  { "LDX ?,Y", 0xBE, 2, 0 },
  { "LDX.B #x", 0xA2, 0xA, 0 },
  { "LDX.W #?", 0xA2, 2, 0 },
  { "LDX.B x", 0xA6, 0xA, 0 },
  { "LDX.W ?", 0xAE, 2, 0 },
  { "LDX.B x,Y", 0xB6, 0xA, 0 },
  { "LDX.W ?,Y", 0xBE, 2, 0 },

  { "LDY #x", 0xA0, 7, 0 },
  { "LDY x", 0xA4, 0xA, 2 },
  { "LDY ?", 0xAC, 2, 0 },
  { "LDY x,X", 0xB4, 0xA, 2 },
  { "LDY ?,X", 0xBC, 2, 0 },
  { "LDY.B #x", 0xA0, 0xA, 0 },
  { "LDY.W #?", 0xA0, 2, 0 },
  { "LDY.B x", 0xA4, 0xA, 0 },
  { "LDY.W ?", 0xAC, 2, 0 },
  { "LDY.B x,X", 0xB4, 0xA, 0 },
  { "LDY.W ?,X", 0xBC, 2, 0 },

  { "LSR A", 0x4A, 0, 0 },
  { "LSR", 0x4A, 0, 0 },
  { "LSR x", 0x46, 0xA, 2 },
  { "LSR ?", 0x4E, 2, 0 },
  { "LSR x,X", 0x56, 0xA, 2 },
  { "LSR ?,X", 0x5E, 2, 0 },
  { "LSR.B x", 0x46, 0xA, 0 },
  { "LSR.W ?", 0x4E, 2, 0 },
  { "LSR.B x,X", 0x56, 0xA, 0 },
  { "LSR.W ?,X", 0x5E, 2, 0 },

  { "MVN x,x", 0x54, 5, 0 },
  { "MVP x,x", 0x44, 5, 0 },
  { "MVN.B x,x", 0x54, 5, 0 },
  { "MVP.B x,x", 0x44, 5, 0 },

  { "NOP", 0xEA, 0, 0 },

  { "ORA #x", 0x09, 4, 0 },
  { "ORA (x)", 0x12, 0xA, 0 },
  { "ORA [x]", 0x07, 0xA, 0 },
  { "ORA (x,X)", 0x01, 0xA, 0 },
  { "ORA (x),Y", 0x11, 0xA, 0 },
  { "ORA (x,S),Y", 0x13, 0xA, 0 },
  { "ORA [x],Y", 0x17, 0xA, 0 },
  { "ORA x", 0x05, 0xA, 2 },
  { "ORA ?", 0x0D, 2, 1 },
  { "ORA &", 0x0F, 3, 0 },
  { "ORA x,X", 0x15, 0xA, 2 },
  { "ORA ?,X", 0x1D, 2, 1 },
  { "ORA &,X", 0x1F, 3, 0 },
  { "ORA ?,Y", 0x19, 2, 0 },
  { "ORA x,S", 0x03, 0xA, 0 },
  { "ORA.B #x", 0x09, 0xA, 0 },
  { "ORA.W #?", 0x09, 2, 0 },
  { "ORA.B (x)", 0x12, 0xA, 0 },
  { "ORA.B [x]", 0x07, 0xA, 0 },
  { "ORA.B (x,X)", 0x01, 0xA, 0 },
  { "ORA.B (x),Y", 0x11, 0xA, 0 },
  { "ORA.B (x,S),Y", 0x13, 0xA, 0 },
  { "ORA.B [x],Y", 0x17, 0xA, 0 },
  { "ORA.B x", 0x05, 0xA, 0 },
  { "ORA.W ?", 0x0D, 2, 0 },
  { "ORA.L &", 0x0F, 3, 0 },
  { "ORA.B x,X", 0x15, 0xA, 0 },
  { "ORA.W ?,X", 0x1D, 2, 0 },
  { "ORA.L &,X", 0x1F, 3, 0 },
  { "ORA.W ?,Y", 0x19, 2, 0 },
  { "ORA.B x,S", 0x03, 0xA, 0 },

  { "PEA ?", 0xF4, 2, 0 },
  { "PEA.W ?", 0xF4, 2, 0 },
  { "PEI (x)", 0xD4, 0xA, 0 },
  { "PEI.B (x)", 0xD4, 0xA, 0 },
  { "PER ?", 0x62, 9, 0 },
  { "PER.W ?", 0x62, 9, 0 },

  { "PHA", 0x48, 0, 0 },
  { "PHP", 0x08, 0, 0 },
  { "PHX", 0xDA, 0, 0 },
  { "PHY", 0x5A, 0, 0 },
  { "PLA", 0x68, 0, 0 },
  { "PLP", 0x28, 0, 0 },
  { "PLX", 0xFA, 0, 0 },
  { "PLY", 0x7A, 0, 0 },

  { "PHB", 0x8B, 0, 0 },
  { "PHD", 0x0B, 0, 0 },
  { "PHK", 0x4B, 0, 0 },
  { "PLB", 0xAB, 0, 0 },
  { "PLD", 0x2B, 0, 0 },

  { "REP #x", 0xC2, 6, 0 },
  { "REP.B #x", 0xC2, 6, 0 },

  { "ROL A", 0x2A, 0, 0 },
  { "ROL", 0x2A, 0, 0 },
  { "ROL x", 0x26, 0xA, 2 },
  { "ROL ?", 0x2E, 2, 0 },
  { "ROL x,X", 0x36, 0xA, 2 },
  { "ROL ?,X", 0x3E, 2, 0 },
  { "ROL.B x", 0x26, 0xA, 0 },
  { "ROL.W ?", 0x2E, 2, 0 },
  { "ROL.B x,X", 0x36, 0xA, 0 },
  { "ROL.W ?,X", 0x3E, 2, 0 },

  { "ROR A", 0x6A, 0, 0 },
  { "ROR", 0x6A, 0, 0 },
  { "ROR x", 0x66, 0xA, 2 },
  { "ROR ?", 0x6E, 2, 0 },
  { "ROR x,X", 0x76, 0xA, 2 },
  { "ROR ?,X", 0x7E, 2, 0 },
  { "ROR.B x", 0x66, 0xA, 0 },
  { "ROR.W ?", 0x6E, 2, 0 },
  { "ROR.B x,X", 0x76, 0xA, 0 },
  { "ROR.W ?,X", 0x7E, 2, 0 },

  { "RTI", 0x40, 0, 0 },
  { "RTL", 0x6B, 0, 0 },
  { "RTS", 0x60, 0, 0 },

  { "SEC", 0x38, 0, 0 },
  { "SED", 0xF8, 0, 0 },
  { "SEI", 0x78, 0, 0 },

  { "SBC #x", 0xE9, 4, 0 },
  { "SBC (x)", 0xF2, 0xA, 0 },
  { "SBC [x]", 0xE7, 0xA, 0 },
  { "SBC (x,X)", 0xE1, 0xA, 0 },
  { "SBC (x),Y", 0xF1, 0xA, 0 },
  { "SBC (x,S),Y", 0xF3, 0xA, 0 },
  { "SBC [x],Y", 0xF7, 0xA, 0 },
  { "SBC x", 0xE5, 0xA, 2 },
  { "SBC ?", 0xED, 2, 1 },
  { "SBC &", 0xEF, 3, 0 },
  { "SBC x,X", 0xF5, 0xA, 2 },
  { "SBC ?,X", 0xFD, 2, 1 },
  { "SBC &,X", 0xFF, 3, 0 },
  { "SBC ?,Y", 0xF9, 2, 0 },
  { "SBC x,S", 0xE3, 0xA, 0 },
  { "SBC.B #x", 0xE9, 0xA, 0 },
  { "SBC.W #?", 0xE9, 2, 0 },
  { "SBC.B (x)", 0xF2, 0xA, 0 },
  { "SBC.B [x]", 0xE7, 0xA, 0 },
  { "SBC.B (x,X)", 0xE1, 0xA, 0 },
  { "SBC.B (x),Y", 0xF1, 0xA, 0 },
  { "SBC.B (x,S),Y", 0xF3, 0xA, 0 },
  { "SBC.B [x],Y", 0xF7, 0xA, 0 },
  { "SBC.B x", 0xE5, 0xA, 0 },
  { "SBC.W ?", 0xED, 2, 0 },
  { "SBC.L &", 0xEF, 3, 0 },
  { "SBC.B x,X", 0xF5, 0xA, 0 },
  { "SBC.W ?,X", 0xFD, 2, 0 },
  { "SBC.L &,X", 0xFF, 3, 0 },
  { "SBC.W ?,Y", 0xF9, 2, 0 },
  { "SBC.B x,S", 0xE3, 0xA, 0 },

  { "SEP #x", 0xE2, 6, 1 },
  { "SEP.B #x", 0xE2, 6, 1 },

  { "STA (x)", 0x92, 0xA, 0 },
  { "STA [x]", 0x87, 0xA, 0 },
  { "STA (x,X)", 0x81, 0xA, 0 },
  { "STA (x),Y", 0x91, 0xA, 0 },
  { "STA (x,S),Y", 0x93, 0xA, 0 },
  { "STA [x],Y", 0x97, 0xA, 0 },
  { "STA x", 0x85, 0xA, 2 },
  { "STA ?", 0x8D, 2, 1 },
  { "STA &", 0x8F, 3, 0 },
  { "STA x,X", 0x95, 0xA, 2 },
  { "STA ?,X", 0x9D, 2, 1 },
  { "STA &,X", 0x9F, 3, 0 },
  { "STA ?,Y", 0x99, 2, 0 },
  { "STA x,S", 0x83, 0xA, 0 },
  { "STA.B (x)", 0x92, 0xA, 0 },
  { "STA.B [x]", 0x87, 0xA, 0 },
  { "STA.B (x,X)", 0x81, 0xA, 0 },
  { "STA.B (x),Y", 0x91, 0xA, 0 },
  { "STA.B (x,S),Y", 0x93, 0xA, 0 },
  { "STA.B [x],Y", 0x97, 0xA, 0 },
  { "STA.B x", 0x85, 0xA, 0 },
  { "STA.W ?", 0x8D, 2, 0 },
  { "STA.L &", 0x8F, 3, 0 },
  { "STA.B x,X", 0x95, 0xA, 0 },
  { "STA.W ?,X", 0x9D, 2, 0 },
  { "STA.L &,X", 0x9F, 3, 0 },
  { "STA.W ?,Y", 0x99, 2, 0 },
  { "STA.B x,S", 0x83, 0xA, 0 },

  { "STP", 0xDB, 0, 0 },

  { "STX x", 0x86, 0xA, 2 },
  { "STX ?", 0x8E, 2, 0 },
  { "STX x,Y", 0x96, 0xA, 0 },
  { "STX.B x", 0x86, 0xA, 0 },
  { "STX.W ?", 0x8E, 2, 0 },
  { "STX.B x,Y", 0x96, 0xA, 0 },

  { "STY x", 0x84, 0xA, 2 },
  { "STY ?", 0x8C, 2, 0 },
  { "STY x,X", 0x94, 0xA, 0 },
  { "STY.B x", 0x84, 0xA, 0 },
  { "STY.W ?", 0x8C, 2, 0 },
  { "STY.B x,X", 0x94, 0xA, 0 },

  { "STZ x", 0x64, 0xA, 2 },
  { "STZ ?", 0x9C, 2, 0 },
  { "STZ x,X", 0x74, 0xA, 2 },
  { "STZ ?,X", 0x9E, 2, 0 },
  { "STZ.B x", 0x64, 0xA, 0 },
  { "STZ.W ?", 0x9C, 2, 0 },
  { "STZ.B x,X", 0x74, 0xA, 0 },
  { "STZ.W ?,X", 0x9E, 2, 0 },

  { "SWA", 0xEB, 0, 0 },

  { "TAX", 0xAA, 0, 0 },
  { "TAY", 0xA8, 0, 0 },
  { "TXA", 0x8A, 0, 0 },
  { "TYA", 0x98, 0, 0 },
  { "TSX", 0xBA, 0, 0 },
  { "TXS", 0x9A, 0, 0 },
  { "TXY", 0x9B, 0, 0 },
  { "TYX", 0xBB, 0, 0 },

  { "TCD", 0x5B, 0, 0 },
  { "TAD", 0x5B, 0, 0 },
  { "TDC", 0x7B, 0, 0 },
  { "TDA", 0x7B, 0, 0 },

  { "TCS", 0x1B, 0, 0 },
  { "TAS", 0x1B, 0, 0 },
  { "TSC", 0x3B, 0, 0 },
  { "TSA", 0x3B, 0, 0 },

  { "TRB x", 0x14, 0xA, 2 },
  { "TRB ?", 0x1C, 2, 0 },
  { "TSB x", 0x04, 0xA, 2 },
  { "TSB ?", 0x0C, 2, 0 },
  { "TRB.B x", 0x14, 0xA, 0 },
  { "TRB.W ?", 0x1C, 2, 0 },
  { "TSB.B x", 0x04, 0xA, 0 },
  { "TSB.W ?", 0x0C, 2, 0 },

  { "WAI", 0xCB, 0, 0 },
  { "WDM", 0x42, 0, 0 },

  { "XBA", 0xEB, 0, 0 },
  { "XCE", 0xFB, 0, 0 },

  { "E", 0x100, -1, 0 }
};