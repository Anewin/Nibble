# Nibble
Nibble is a protocol designed by Anewin and used by the Five Wire product to export execution marks or variable values. Execution marks are set in the execution flow of a microprocessor to flag execution progress. This can be especially helpful in multi-tasking systems such as FreeRTOS. You can determine order of execution or look for blocked execution. Up to 15 unique marks using nibble protocol.

Nibble also supports the real-time trace of variable values. It can export bytes, words, or longs (8, 16, 32 bits). Exporting variable values takes 1 - 3 microseconds which for most real-time systems is an acceptable delay.

The nibble protocol requires allocation of 4 output pins on the microprocessor. The C and H files included here implement the protocol. These files must be modified to select the specific pins used in an implementation and the pins must have been configured as outputs by user code.

For further desciptions of the Nibble protocol and its use with the Five Wire product go to https://AnewinLogic.com
