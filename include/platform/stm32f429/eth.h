#ifndef PLATFORM_STM32F429_ETH_H_
#define PLATFORM_STM32F429_ETH_H_

#include <platform/link.h>
#include <platform/stm32f429/registers.h>

#define ETH_MAC_OFFSET 0x0000U
#define ETH_MMC_OFFSET 0x0100U
#define ETH_PTP_OFFSET 0x0700U
#define ETH_DMA_OFFSET 0x1000U

struct eth_mac_regs {
    volatile uint32_t cr;     /* 0x00: MAC configuration register */
    volatile uint32_t ffr;    /* 0x04: MAC frame filter register */
    volatile uint32_t hthr;   /* 0x08: MAC hash table high register */
    volatile uint32_t htlr;   /* 0x0C: MAC hash table low register */
    volatile uint32_t miiar;  /* 0x10: MAC MII address register */
    volatile uint32_t miidr;  /* 0x14: MAC MII data register */
    volatile uint32_t fcr;    /* 0x18: MAC flow control register */
    volatile uint32_t vlantr; /* 0x1C: MAC VLAN tag register */
    uint32_t reserved1[2];    /* 0x20-0x24 */
    volatile uint32_t rwuffr; /* 0x28: MAC remote wakeup filter register */
    volatile uint32_t pmtcsr; /* 0x2C: MAC PMT control and status register */
    uint32_t reserved2;       /* 0x30 */
    volatile uint32_t dbgr;   /* 0x34: MAC debug register */
    volatile uint32_t sr;     /* 0x38: MAC interrupt status register */
    volatile uint32_t imr;    /* 0x3C: MAC interrupt mask register */
    volatile uint32_t a0hr;   /* 0x40: MAC address 0 high register */
    volatile uint32_t a0lr;   /* 0x44: MAC address 0 low register */
    volatile uint32_t a1hr;   /* 0x48: MAC address 1 high register */
    volatile uint32_t a1lr;   /* 0x4C: MAC address 1 low register */
    volatile uint32_t a2hr;   /* 0x50: MAC address 2 high register */
    volatile uint32_t a2lr;   /* 0x54: MAC address 2 low register */
    volatile uint32_t a3hr;   /* 0x58: MAC address 3 high register */
    volatile uint32_t a3lr;   /* 0x5C: MAC address 3 low register */
};

struct eth_mmc_regs {
    volatile uint32_t cr;      /* 0x100: MMC control register */
    volatile uint32_t rir;     /* 0x104: MMC Rx interrupt register */
    volatile uint32_t tir;     /* 0x108: MMC Tx interrupt register */
    volatile uint32_t rimr;    /* 0x10C: MMC Rx interrupt mask register */
    volatile uint32_t timr;    /* 0x110: MMC Tx interrupt mask register */
    uint32_t reserved1[14];    /* 0x114–0x148 */
    volatile uint32_t tgfsccr; /* 0x14C: Tx good frames after a single collision
                                  counter register */
    volatile uint32_t tgfmscr; /* 0x150: Tx good frame counter register */
    uint32_t reserved2[5];     /* 0x154–0x164 */
    volatile uint32_t tgfcr;   /* 0x168: Tx good frame counter register */
    uint32_t reserved3[10];    /* 0x16C–0x190 */
    volatile uint32_t
        rfcecr; /* 0x194: Rx frame counter with CRC error counter register */
    volatile uint32_t rfaecr; /* 0x198: Rx frame counter with alignment error
                                 counter register */
    uint32_t reserved4[10];   /* 0x19C–0x1C0 */
    volatile uint32_t rgufcr; /* 0x1C4: Rx good unicast frame counter register*/
};

struct eth_ptp_regs {
    volatile uint32_t tscr;   /* 0x700: Time stamp control register */
    volatile uint32_t ssir;   /* 0x704: Sub-second increment register */
    volatile uint32_t tshr;   /* 0x708: Time stamp high register (seconds) */
    volatile uint32_t tslr;   /* 0x70C: Time stamp low register (sub-seconds) */
    volatile uint32_t tshur;  /* 0x710: Time stamp high update register */
    volatile uint32_t tslur;  /* 0x714: Time stamp low update register */
    volatile uint32_t tsar;   /* 0x718: Time stamp addend register */
    volatile uint32_t ttssr;  /* 0x71C: Target time seconds register */
    volatile uint32_t ttsslr; /* 0x720: Target time sub-seconds register */
    volatile uint32_t tsssr;  /* 0x724: Time stamp status register */
    volatile uint32_t ppscr;  /* 0x728: PPS control register */
};

struct eth_dma_regs {
    volatile uint32_t bmr;   /* 0x1000: DMA bus mode register */
    volatile uint32_t tpdr;  /* 0x1004: Transmit poll demand register */
    volatile uint32_t rpdr;  /* 0x1008: Receive poll demand register */
    volatile uint32_t rdlar; /* 0x100C: Rx descriptor list address register */
    volatile uint32_t tdlar; /* 0x1010: Tx descriptor list address register */
    volatile uint32_t sr;    /* 0x1014: DMA status register */
    volatile uint32_t omr;   /* 0x1018: DMA operation mode register */
    volatile uint32_t ier;   /* 0x101C: DMA interrupt enable register */
    volatile uint32_t
        mfbocr;              /* 0x1020: Missed frame & FIFO overflow register */
    volatile uint32_t rswtr; /* 0x1024: Receive status watchdog timer */
    uint32_t reserved1[8];   /* 0x1028–0x1044 */
    volatile uint32_t chtdr; /* 0x1048: Current host Tx descriptor */
    volatile uint32_t chrdr; /* 0x104C: Current host Rx descriptor */
    volatile uint32_t chtbar; /* 0x1050: Current host Tx buffer */
    volatile uint32_t chrbar; /* 0x1054: Current host Rx buffer */
};

#define ETH_MAC ((struct eth_mac_regs *) (ETH_BASE + ETH_MAC_OFFSET))
#define ETH_MMC ((struct eth_mmc_regs *) (ETH_BASE + ETH_MMC_OFFSET))
#define ETH_PTP ((struct eth_ptp_regs *) (ETH_BASE + ETH_PTP_OFFSET))
#define ETH_DMA ((struct eth_dma_regs *) (ETH_BASE + ETH_DMA_OFFSET))

/* MAC MII Address Register Bit Fields */
/* MAC Address 0 High Register Bit Fields */
#define ETH_MACA0HR_ADDRHI_Pos 0 /* MAC Address 0 [47:32] */
#define ETH_MACA0HR_ADDRHI_Msk (0xFFFFU << ETH_MACA0HR_ADDRHI_Pos)
#define ETH_MACA0HR_ADDRHI ETH_MACA0HR_ADDRHI_Msk

/* MAC Address 0 Low Register Bit Fields */
#define ETH_MACA0LR_ADDRLO_Pos 0 /* MAC Address 0 [31:0] */
#define ETH_MACA0LR_ADDRLO_Msk (0xFFFFFFFFU << ETH_MACA0LR_ADDRLO_Pos)
#define ETH_MACA0LR_ADDRLO ETH_MACA0LR_ADDRLO_Msk

#endif /* PLATFORM_STM32F429_ETH_H_ */
