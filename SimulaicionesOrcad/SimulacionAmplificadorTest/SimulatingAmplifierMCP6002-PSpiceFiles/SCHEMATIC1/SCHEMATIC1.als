.ALIASES
V_V1            V1(+=VCC -=0 ) CN @SIMULATINGAMPLIFIERMCP6002.SCHEMATIC1(sch_1):INS67@SOURCE.VDC.Normal(chips)
V_V2            V2(+=0 -=VEE ) CN @SIMULATINGAMPLIFIERMCP6002.SCHEMATIC1(sch_1):INS83@SOURCE.VDC.Normal(chips)
X_U2            U2(IN+=0 IN-=N01469 V+=VCC V-=VEE OUT=N01348 ) CN
+@SIMULATINGAMPLIFIERMCP6002.SCHEMATIC1(sch_1):INS964@MICROCHIP_OPAMP.MCP6001.Normal(chips)
R_R1            R1(1=N01348 2=N01469 ) CN @SIMULATINGAMPLIFIERMCP6002.SCHEMATIC1(sch_1):INS1261@ANALOG.R.Normal(chips)
R_R2            R2(1=0 2=N01469 ) CN @SIMULATINGAMPLIFIERMCP6002.SCHEMATIC1(sch_1):INS1277@ANALOG.R.Normal(chips)
_    _(VCC=VCC)
_    _(VEE=VEE)
.ENDALIASES
