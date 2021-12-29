// mbed_error()はlibmbed内でエラーになった時に呼ばれる。
// 標準で提供されているものは、割り込み禁止状態で無限ループに入ってしまい、
// USB経由の書き込みができなくなってしまう。
// この実装では、割り込みを禁止せず無限ループに入るため、USB経由での
// リセットが可能となる。

#include <stdbool.h>
#include <Arduino.h>
#include <xprintf.h>

extern "C" {
// platform/include/platform/internal/mbed_fault_handler.h
typedef struct {
    uint32_t R0_reg;
    uint32_t R1_reg;
    uint32_t R2_reg;
    uint32_t R3_reg;
    uint32_t R4_reg;
    uint32_t R5_reg;
    uint32_t R6_reg;
    uint32_t R7_reg;
    uint32_t R8_reg;
    uint32_t R9_reg;
    uint32_t R10_reg;
    uint32_t R11_reg;
    uint32_t R12_reg;
    uint32_t SP_reg;
    uint32_t LR_reg;
    uint32_t PC_reg;
    uint32_t xPSR;
    uint32_t PSP;
    uint32_t MSP;
    uint32_t EXC_RETURN;
    uint32_t CONTROL;
} mbed_fault_context_t;


extern mbed_fault_context_t mbed_fault_context;

}

extern "C" void 
mbed_error(int error_status, const char *error_msg, unsigned int error_value, const char *filename, int line_number)
{
    if (filename == nullptr)
    {
        char buf[80];
        // error_status = 0x80ff013d
        // 0xff : MBED_MODULE_UNKNOWN
        // 0x013d : HARDFAULT_EXCEPTION
        snprintf(buf, sizeof(buf), "%s %08x %08x %08x\n",
                 error_msg, error_status,
                 static_cast<unsigned int>(mbed_fault_context.PC_reg),
                 static_cast<unsigned int>(mbed_fault_context.LR_reg));
        Serial.println(buf);
        for (;;)
        {
        }
    }
    Serial.print(filename);
    Serial.print(line_number, DEC);
    Serial.print(": ");
    if (error_msg != nullptr)
    {
        Serial.print(error_msg);
    }
    else
    {
        Serial.print("(no msg)");
    }
    Serial.print(" ");
    Serial.println(error_value, DEC);

    for (;;)
    {
    }
}