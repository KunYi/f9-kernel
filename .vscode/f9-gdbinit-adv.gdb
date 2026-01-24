# -------------------------------------------
# F9-Kernel Advanced Auto Debug GDB Init
# -------------------------------------------

# 1 CPU reset + halt
# monitor reset halt

# 2 啟用 vector catch for MPU/HardFault/BusFault/UsageFault
# monitor arm vector_catch all

# 3 設置硬體 watchpoint
# current
# watch -l *(volatile uint32_t*)0x20001364
# current_utcb
# watch -l *(volatile uint32_t*)0x20005000

# 4 輸出初始狀態
echo -----------------------------\n
echo F9-Kernel Debug Init Complete\n
info registers
echo -----------------------------\n

# 5 自動分析停止 (hook-stop)
define hook-stop
    echo -----------------------------\n
    echo Watchpoint / Breakpoint Triggered\n
    echo PC: $pc\n
    info registers

    # 判斷使用的堆疊 (PSP/MSP)
    if ($control & 0x2)
        set $sp_used = $psp
        echo Using PSP (User Thread Stack)\n
    else
        set $sp_used = $sp
        echo Using MSP (Kernel/Exception Stack)\n
    end

    # 顯示 top 32 words of stack
    x/32wx $sp_used

    # Backtrace
    bt

    # 判斷是否在 CRT zero-init
    if ($pc >= 0x08000000 && $pc <= 0x08002000)
        echo WARNING: PC in Flash startup/CRT zero-init region\n
    else
        echo PC outside startup region (likely kernel/user code)\n
    end

    echo -----------------------------\n
end

# 6 強制啟用硬體單步（optional，可觀察 fault propagation）
# set $cpsr = $cpsr | 0x20

# 7 自動運行到 main() (與 launch.json runToMain: true 一致)
# continue

