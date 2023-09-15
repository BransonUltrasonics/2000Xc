/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/genalarm.h_v   1.8   28 Nov 2014 07:55:26   rjamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/genalarm.h_v  $
 * 
 *    Rev 1.8   28 Nov 2014 07:55:26   rjamloki
 * WARNINGMASK macro changed to enable bits for USbMemoryNearlyFull and DiskMemoryNearlyFull alarm.
 * 
 *    Rev 1.7   10 Nov 2014 04:40:10   AnPawar
 * REJECTBITRESULTMASK mask changed for new downspeed reject alarm.
 * 
 *    Rev 1.6   05 Sep 2014 04:10:30   rjamloki
 * Enabled EQ26 in default equipment failure mask
*/
/*
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: genalarm.h

   Function name:


 --------------------------------- REVISIONS --------------------------------


------------------------------ INCLUDES ----------------------------------*/

#include "alarms.h"

/*-------------------------------- DEFINES ---------------------------------*/                           

#define SUSPECTBITRESULTMASK  0x00007ffe
#define REJECTBITRESULTMASK   0x0079fffe    /* Reject limits only         */
#define REJECTALARMMASK       0x00780000    /* Alarms grouped with reject */
#define OVERLOADMASK          0x000005fe
#define NOCYCLEMASK           0x000fffda
#define EQUIPMENTFAILUREMASK  0x0ff7ffde
#define CYCLEMODIFIEDMASK     0x00fffffe
#define WARNINGMASK           0x0000fffe/*enabled bits for usb and disk nearly full*/
#define CALIBRATEMASK         0x00000000

#define SETUPGROUP1MASK       0x0ffffffe
#define SETUPGROUP2MASK       0x0ffffffe
#define SETUPGROUP3MASK       0x0fffff3e
#define SETUPGROUP4MASK       0x0ffffffe
#define SETUPGROUP5MASK       0x0ffffffe
#define SETUPGROUP6MASK       0x0ffffdfe
#define SETUPGROUP7MASK       0x0e7ffffe
#define SETUPGROUP8MASK       0x0ffffffe
#define SETUPGROUP9MASK       0x003fff5e
#define SETUPGROUP10MASK      0x0003fffe


/*--  These masks need to be figured out again (07-21-97)  --*/

//#define SYSFAULTABORTMASK1    0x003FA13C
//#define GENALARMABORTMASK2    0x00000040


#define BIT33  BIT1
#define BIT34  BIT2
#define BIT35  BIT3  
#define BIT36  BIT4 
#define BIT37  BIT5  
#define BIT38  BIT6  
#define BIT39  BIT7  
#define BIT40  BIT8  
#define BIT41  BIT9  
#define BIT42  BIT10 
#define BIT43  BIT11 
#define BIT44  BIT12 
#define BIT45  BIT13 
#define BIT46  BIT14 
#define BIT47  BIT15 
#define BIT48  BIT16 	
#define BIT49  BIT17 
#define BIT50  BIT18 
#define BIT51  BIT19 
#define BIT52  BIT20 
#define BIT53  BIT21 
#define BIT54  BIT22 
#define BIT55  BIT23 
#define BIT56  BIT24
#define BIT57  BIT25
#define BIT58  BIT26
#define BIT59  BIT27
               
#define BIT65  BIT1
#define BIT66  BIT2
#define BIT67  BIT3  
#define BIT68  BIT4 
#define BIT69  BIT5  
#define BIT70  BIT6  
#define BIT71  BIT7  
#define BIT72  BIT8  
#define BIT73  BIT9  
#define BIT74  BIT10 
#define BIT75  BIT11 
#define BIT76  BIT12 
#define BIT77  BIT13 
#define BIT78  BIT14 
#define BIT79  BIT15 
#define BIT80  BIT16 	
#define BIT81  BIT17 
#define BIT82  BIT18 
#define BIT83  BIT19 
#define BIT84  BIT20 
#define BIT85  BIT21 
#define BIT86  BIT22 
#define BIT87  BIT23 
#define BIT88  BIT24
#define BIT89  BIT25
#define BIT90  BIT26
#define BIT91  BIT27

#define BIT97  BIT1
#define BIT98  BIT2
#define BIT99  BIT3  
#define BIT100 BIT4 
#define BIT101 BIT5  
#define BIT102 BIT6  
#define BIT103 BIT7  
#define BIT104 BIT8  
#define BIT105 BIT9  
#define BIT106 BIT10 
#define BIT107 BIT11 
#define BIT108 BIT12 
#define BIT109 BIT13 
#define BIT110 BIT14 
#define BIT111 BIT15 
#define BIT112 BIT16 	
#define BIT113 BIT17 
#define BIT114 BIT18 
#define BIT115 BIT19 
#define BIT116 BIT20 
#define BIT117 BIT21 
#define BIT118 BIT22 
#define BIT119 BIT23 
#define BIT120 BIT24
#define BIT121 BIT25
#define BIT122 BIT26
#define BIT123 BIT27

#define BIT129 BIT1
#define BIT130 BIT2
#define BIT131 BIT3  
#define BIT132 BIT4 
#define BIT133 BIT5  
#define BIT134 BIT6  
#define BIT135 BIT7  
#define BIT136 BIT8  
#define BIT137 BIT9  
#define BIT138 BIT10 
#define BIT139 BIT11 
#define BIT140 BIT12 
#define BIT141 BIT13 
#define BIT142 BIT14 
#define BIT143 BIT15 
#define BIT144 BIT16 	
#define BIT145 BIT17 
#define BIT146 BIT18 
#define BIT147 BIT19 
#define BIT148 BIT20 
#define BIT149 BIT21 
#define BIT150 BIT22 
#define BIT151 BIT23 
#define BIT152 BIT24
#define BIT153 BIT25
#define BIT154 BIT26
#define BIT155 BIT27

#define BIT161 BIT1
#define BIT162 BIT2
#define BIT163 BIT3  
#define BIT164 BIT4 
#define BIT165 BIT5  
#define BIT166 BIT6  
#define BIT167 BIT7  
#define BIT168 BIT8  
#define BIT169 BIT9  
#define BIT170 BIT10 
#define BIT171 BIT11 
#define BIT172 BIT12 
#define BIT173 BIT13 
#define BIT174 BIT14 
#define BIT175 BIT15 
#define BIT176 BIT16 	
#define BIT177 BIT17 
#define BIT178 BIT18 
#define BIT179 BIT19 
#define BIT180 BIT20 
#define BIT181 BIT21 
#define BIT182 BIT22 
#define BIT183 BIT23 
#define BIT184 BIT24
#define BIT185 BIT25
#define BIT186 BIT26
#define BIT187 BIT27

#define BIT193 BIT1
#define BIT194 BIT2
#define BIT195 BIT3  
#define BIT196 BIT4 
#define BIT197 BIT5  
#define BIT198 BIT6  
#define BIT199 BIT7  
#define BIT200 BIT8  
#define BIT201 BIT9  
#define BIT202 BIT10 
#define BIT203 BIT11 
#define BIT204 BIT12 
#define BIT205 BIT13 
#define BIT206 BIT14 
#define BIT207 BIT15 
#define BIT208 BIT16 	
#define BIT209 BIT17 
#define BIT210 BIT18 
#define BIT211 BIT19 
#define BIT212 BIT20 
#define BIT213 BIT21 
#define BIT214 BIT22 
#define BIT215 BIT23 
#define BIT216 BIT24
#define BIT217 BIT25
#define BIT218 BIT26
#define BIT219 BIT27

#define BIT225 BIT1
#define BIT226 BIT2
#define BIT227 BIT3  
#define BIT228 BIT4 
#define BIT229 BIT5  
#define BIT230 BIT6  
#define BIT231 BIT7  
#define BIT232 BIT8  
#define BIT233 BIT9  
#define BIT234 BIT10 
#define BIT235 BIT11 
#define BIT236 BIT12 
#define BIT237 BIT13 
#define BIT238 BIT14 
#define BIT239 BIT15 
#define BIT240 BIT16 	
#define BIT241 BIT17 
#define BIT242 BIT18 
#define BIT243 BIT19 
#define BIT244 BIT20 
#define BIT245 BIT21 
#define BIT246 BIT22 
#define BIT247 BIT23 
#define BIT248 BIT24
#define BIT249 BIT25
#define BIT250 BIT26
#define BIT251 BIT27

#define BIT257 BIT1
#define BIT258 BIT2
#define BIT259 BIT3  
#define BIT260 BIT4 
#define BIT261 BIT5  
#define BIT262 BIT6  
#define BIT263 BIT7  
#define BIT264 BIT8  
#define BIT265 BIT9  
#define BIT266 BIT10 
#define BIT267 BIT11 
#define BIT268 BIT12 
#define BIT269 BIT13 
#define BIT270 BIT14 
#define BIT271 BIT15 
#define BIT272 BIT16 	
#define BIT273 BIT17 
#define BIT274 BIT18 
#define BIT275 BIT19 
#define BIT276 BIT20 
#define BIT277 BIT21 
#define BIT278 BIT22 
#define BIT279 BIT23 
#define BIT280 BIT24
#define BIT281 BIT25
#define BIT282 BIT26
#define BIT283 BIT27

#define BIT289 BIT1
#define BIT290 BIT2
#define BIT291 BIT3  
#define BIT292 BIT4 
#define BIT293 BIT5  
#define BIT294 BIT6  
#define BIT295 BIT7  
#define BIT296 BIT8  
#define BIT297 BIT9  
#define BIT298 BIT10 
#define BIT299 BIT11 
#define BIT300 BIT12 
#define BIT301 BIT13 
#define BIT302 BIT14 
#define BIT303 BIT15 
#define BIT304 BIT16 	
#define BIT305 BIT17 
#define BIT306 BIT18 
#define BIT307 BIT19 
#define BIT308 BIT20 
#define BIT309 BIT21 
#define BIT310 BIT22 
#define BIT311 BIT23 
#define BIT312 BIT24
#define BIT313 BIT25
#define BIT314 BIT26
#define BIT315 BIT27



/*--------------------------- FUNCTION PROTOTYPES --------------------------*/




