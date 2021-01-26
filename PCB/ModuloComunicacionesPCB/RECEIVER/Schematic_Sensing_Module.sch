<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.6.2">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="16" fill="1" visible="no" active="no"/>
<layer number="3" name="Route3" color="17" fill="1" visible="no" active="no"/>
<layer number="4" name="Route4" color="18" fill="1" visible="no" active="no"/>
<layer number="5" name="Route5" color="19" fill="1" visible="no" active="no"/>
<layer number="6" name="Route6" color="25" fill="1" visible="no" active="no"/>
<layer number="7" name="Route7" color="26" fill="1" visible="no" active="no"/>
<layer number="8" name="Route8" color="27" fill="1" visible="no" active="no"/>
<layer number="9" name="Route9" color="28" fill="1" visible="no" active="no"/>
<layer number="10" name="Route10" color="29" fill="1" visible="no" active="no"/>
<layer number="11" name="Route11" color="30" fill="1" visible="no" active="no"/>
<layer number="12" name="Route12" color="20" fill="1" visible="no" active="no"/>
<layer number="13" name="Route13" color="21" fill="1" visible="no" active="no"/>
<layer number="14" name="Route14" color="22" fill="1" visible="no" active="no"/>
<layer number="15" name="Route15" color="23" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="ESP32-W">
<packages>
<package name="DIP">
<pad name="GND" x="-13" y="13.5" drill="1.04" shape="square"/>
<pad name="3V3" x="-13" y="16" drill="1.04"/>
<pad name="D15" x="-13" y="11" drill="1.04"/>
<pad name="D2" x="-13" y="8.5" drill="1.04"/>
<pad name="D4" x="-13" y="6" drill="1.04"/>
<pad name="RX2" x="-13" y="3.5" drill="1.04"/>
<pad name="TX2" x="-13" y="1" drill="1.04"/>
<pad name="D5" x="-13" y="-1.5" drill="1.04"/>
<pad name="D18" x="-13" y="-4" drill="1.04"/>
<pad name="D19" x="-13" y="-6.5" drill="1.04"/>
<pad name="D21" x="-13" y="-9" drill="1.04"/>
<pad name="RX0" x="-13" y="-11.5" drill="1.04"/>
<pad name="TX0" x="-13" y="-14" drill="1.04"/>
<pad name="D22" x="-13" y="-16.5" drill="1.04"/>
<pad name="D23" x="-13" y="-19" drill="1.04"/>
<pad name="GND1" x="12" y="13.5" drill="1.04" shape="square"/>
<pad name="VIN" x="12" y="16" drill="1.04"/>
<pad name="D13" x="12" y="11" drill="1.04"/>
<pad name="D12" x="12" y="8.5" drill="1.04"/>
<pad name="D14" x="12" y="6" drill="1.04"/>
<pad name="D27" x="12" y="3.5" drill="1.04"/>
<pad name="D26" x="12" y="1" drill="1.04"/>
<pad name="D25" x="12" y="-1.5" drill="1.04"/>
<pad name="D33" x="12" y="-4" drill="1.04"/>
<pad name="D32" x="12" y="-6.5" drill="1.04"/>
<pad name="D35" x="12" y="-9" drill="1.04"/>
<pad name="D34" x="12" y="-11.5" drill="1.04"/>
<pad name="VN" x="12" y="-14" drill="1.04"/>
<pad name="VP" x="12" y="-16.5" drill="1.04"/>
<pad name="EN" x="12" y="-19" drill="1.04"/>
<wire x1="-14.5" y1="17" x2="13.5" y2="17" width="0.127" layer="21"/>
<wire x1="13.5" y1="17" x2="13.5" y2="-20.5" width="0.127" layer="21"/>
<wire x1="-14.5" y1="-20.5" x2="-14.5" y2="17" width="0.127" layer="21"/>
<dimension x1="-14.5" y1="-20.5" x2="-14.5" y2="17" x3="-16.5" y3="-1.75" textsize="1.27" layer="21"/>
<wire x1="-14.5" y1="-20.5" x2="-14.5" y2="-30.5" width="0.127" layer="21"/>
<wire x1="-14.5" y1="-30.5" x2="-5.5" y2="-30.5" width="0.127" layer="21"/>
<wire x1="5" y1="-30.5" x2="13.5" y2="-30.5" width="0.127" layer="21"/>
<wire x1="13.5" y1="-30.5" x2="13.5" y2="-20.5" width="0.127" layer="21"/>
<wire x1="-5.5" y1="-30.5" x2="-5.5" y2="-28.5" width="0.127" layer="21"/>
<wire x1="-5.5" y1="-28.5" x2="5" y2="-28.5" width="0.127" layer="21"/>
<wire x1="5" y1="-28.5" x2="5" y2="-30.5" width="0.127" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="ESP32-DEVKIT">
<wire x1="-15.24" y1="20.32" x2="-15.24" y2="-20.32" width="0.254" layer="94"/>
<wire x1="-15.24" y1="-20.32" x2="15.24" y2="-20.32" width="0.254" layer="94"/>
<wire x1="15.24" y1="-20.32" x2="15.24" y2="20.32" width="0.254" layer="94"/>
<wire x1="15.24" y1="20.32" x2="-15.24" y2="20.32" width="0.254" layer="94"/>
<pin name="3V3" x="-20.32" y="17.78" length="middle"/>
<pin name="GND" x="-20.32" y="15.24" length="middle"/>
<pin name="D15" x="-20.32" y="12.7" length="middle"/>
<pin name="D2" x="-20.32" y="10.16" length="middle"/>
<pin name="D4" x="-20.32" y="7.62" length="middle"/>
<pin name="RX2" x="-20.32" y="5.08" length="middle"/>
<pin name="TX2" x="-20.32" y="2.54" length="middle"/>
<pin name="D5" x="-20.32" y="0" length="middle"/>
<pin name="D18" x="-20.32" y="-2.54" length="middle"/>
<pin name="D19" x="-20.32" y="-5.08" length="middle"/>
<pin name="D21" x="-20.32" y="-7.62" length="middle"/>
<pin name="RX0" x="-20.32" y="-10.16" length="middle"/>
<pin name="TX0" x="-20.32" y="-12.7" length="middle"/>
<pin name="D22" x="-20.32" y="-15.24" length="middle"/>
<pin name="D23" x="-20.32" y="-17.78" length="middle"/>
<pin name="EN" x="20.32" y="-17.78" length="middle" rot="R180"/>
<pin name="VP" x="20.32" y="-15.24" length="middle" rot="R180"/>
<pin name="VN" x="20.32" y="-12.7" length="middle" rot="R180"/>
<pin name="D34" x="20.32" y="-10.16" length="middle" rot="R180"/>
<pin name="D35" x="20.32" y="-7.62" length="middle" rot="R180"/>
<pin name="D32" x="20.32" y="-5.08" length="middle" rot="R180"/>
<pin name="D33" x="20.32" y="-2.54" length="middle" rot="R180"/>
<pin name="D25" x="20.32" y="0" length="middle" rot="R180"/>
<pin name="D26" x="20.32" y="2.54" length="middle" rot="R180"/>
<pin name="D27" x="20.32" y="5.08" length="middle" rot="R180"/>
<pin name="D14" x="20.32" y="7.62" length="middle" rot="R180"/>
<pin name="D12" x="20.32" y="10.16" length="middle" rot="R180"/>
<pin name="D13" x="20.32" y="12.7" length="middle" rot="R180"/>
<pin name="GND1" x="20.32" y="15.24" length="middle" rot="R180"/>
<pin name="VIN" x="20.32" y="17.78" length="middle" rot="R180"/>
<text x="-15.24" y="22.86" size="1.778" layer="95">&gt;NAME</text>
<text x="-15.24" y="-25.4" size="1.778" layer="96">&gt;VALUE</text>
<text x="-5.08" y="0" size="1.778" layer="97">ESP32-W</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="ESP32-W">
<gates>
<gate name="G$1" symbol="ESP32-DEVKIT" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DIP">
<connects>
<connect gate="G$1" pin="3V3" pad="3V3"/>
<connect gate="G$1" pin="D12" pad="D12"/>
<connect gate="G$1" pin="D13" pad="D13"/>
<connect gate="G$1" pin="D14" pad="D14"/>
<connect gate="G$1" pin="D15" pad="D15"/>
<connect gate="G$1" pin="D18" pad="D18"/>
<connect gate="G$1" pin="D19" pad="D19"/>
<connect gate="G$1" pin="D2" pad="D2"/>
<connect gate="G$1" pin="D21" pad="D21"/>
<connect gate="G$1" pin="D22" pad="D22"/>
<connect gate="G$1" pin="D23" pad="D23"/>
<connect gate="G$1" pin="D25" pad="D25"/>
<connect gate="G$1" pin="D26" pad="D26"/>
<connect gate="G$1" pin="D27" pad="D27"/>
<connect gate="G$1" pin="D32" pad="D32"/>
<connect gate="G$1" pin="D33" pad="D33"/>
<connect gate="G$1" pin="D34" pad="D34"/>
<connect gate="G$1" pin="D35" pad="D35"/>
<connect gate="G$1" pin="D4" pad="D4"/>
<connect gate="G$1" pin="D5" pad="D5"/>
<connect gate="G$1" pin="EN" pad="EN"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="GND1" pad="GND1"/>
<connect gate="G$1" pin="RX0" pad="RX0"/>
<connect gate="G$1" pin="RX2" pad="RX2"/>
<connect gate="G$1" pin="TX0" pad="TX0"/>
<connect gate="G$1" pin="TX2" pad="TX2"/>
<connect gate="G$1" pin="VIN" pad="VIN"/>
<connect gate="G$1" pin="VN" pad="VN"/>
<connect gate="G$1" pin="VP" pad="VP"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U$1" library="ESP32-W" deviceset="ESP32-W" device=""/>
</parts>
<sheets>
<sheet>
<plain>
<wire x1="-81.28" y1="60.96" x2="86.36" y2="60.96" width="0.4064" layer="97"/>
<wire x1="86.36" y1="60.96" x2="86.36" y2="-60.96" width="0.4064" layer="97"/>
<wire x1="86.36" y1="-60.96" x2="-81.28" y2="-60.96" width="0.4064" layer="97"/>
<wire x1="-81.28" y1="-60.96" x2="-81.28" y2="60.96" width="0.4064" layer="97"/>
<text x="-78.74" y="63.5" size="3.81" layer="97">RECEIVER</text>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="0" y="0" smashed="yes">
<attribute name="NAME" x="-15.24" y="22.86" size="1.778" layer="95"/>
<attribute name="VALUE" x="-15.24" y="-25.4" size="1.778" layer="96"/>
</instance>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
