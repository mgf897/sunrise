#Using formulas from the LM3401 datasheet
import pprint

Iled = 0.4 #400mA
Iled_max = 0.45 #450mA
Vsns = 0.2 #200mV

Rsns = Vsns/Iled
Wrsns = Vsns*Iled
SNShys_max = (Iled_max - Iled) * Rsns
#Set SNShys halfway between 10mV and SNShys_max
SNShys = (SNShys_max/2)+(0.010/2)
R2 = (SNShys*5)/(20E-6) #(SNShys*5)/20uA
Iled_rip = (SNShys*2)/Rsns
Iled_pk = Iled + (Iled_rip/2) #Peak LED current = dc + half ripple

pprint.pprint(locals())