/*
 * Copyright (c) 2014, Thorben Hasenpusch <t.hasenpusch@icloud.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#pragma once

#include <cstdint>

#include "acpi/shared.h"

namespace Acpi {

enum class PmProfile : uint8_t {
    UNSPECIFIED = 0,
    DESKTOP = 1,
    MOBILE = 2,
    WORKSTATION = 3,
    ENTERPRISE_SERVER = 4,
    SOHO_SERVER = 5,
    APPLIANCE_PC = 6,
    PERFORMANCE_SERVER = 7,
    TABLET = 8
};

struct IaPcBootFlags {
    uint16_t legacy_devices : 1;
    uint16_t supp_8041 : 1;
    uint16_t vga_not_present : 1;
    uint16_t msi_not_supported : 1;
    uint16_t pcie_aspm_controls : 1;
    uint16_t cmos_rtc_not_present : 1;
    uint16_t reserved : 10;
};

struct FixedFeatureFlags {
    uint32_t wbinvd : 1;
    uint32_t wbinvd_flush : 1;
    uint32_t proc_c1 : 1;
    uint32_t p_lvl2_up : 1;
    uint32_t pwr_button : 1;
    uint32_t slp_button : 1;
    uint32_t fix_rtc : 1;
    uint32_t rtc_s4 : 1;
    uint32_t tmr_val_ext : 1;
    uint32_t dck_cap : 1;
    uint32_t reset_reg_supp : 1;
    uint32_t sealed_case : 1;
    uint32_t headless : 1;
    uint32_t cpu_sw_slp : 1;
    uint32_t pci_exp_wak : 1;
    uint32_t use_platform_clock : 1;
    uint32_t s4_rtc_sts_valid : 1;
    uint32_t remote_power_on_capable : 1;
    uint32_t force_apic_cluster_model : 1;
    uint32_t force_apic_physical_destination_mode : 1;
    uint32_t hw_reduced_acpi : 1;
    uint32_t low_power_s0_idl_capable : 1;
    uint32_t reserved : 10;
};

struct ArmBootFlags {
    uint16_t psci_compliant : 1;
    uint16_t psci_use_hvc : 1;
    uint16_t reserved : 14;
};

struct Facs;
struct Dsdt;

struct Fadt {
    TableHeader header;
    uint32_t firmware_ctrl;
    uint32_t dsdt;
    uint8_t reserved;
    PmProfile preferred_pm_profile;
    uint16_t sci_int;
    uint32_t ami_cmd;
    uint8_t acpi_enable;
    uint8_t acpi_disable;
    uint8_t s4bios_req;
    uint8_t pstate_cnt;
    uint32_t pm1a_evt_blk;
    uint32_t pm1b_evt_blk;
    uint32_t pm1a_cnt_blk;
    uint32_t pm1b_cnt_blk;
    uint32_t pm2_cnt_blk;
    uint32_t pm_tmr_blk;
    uint32_t gpe0_blk;
    uint32_t gpe1_blk;
    uint8_t pm1_evt_len;
    uint8_t pm1_cnt_len;
    uint8_t pm2_cnt_len;
    uint8_t pm_tmr_len;
    uint8_t gpe0_blk_len;
    uint8_t gpe1_blk_len;
    uint8_t gpe1_base;
    uint8_t cst_cnt;
    uint16_t p_lvl2_lat;
    uint16_t p_lvl3_lat;
    uint16_t flush_size;
    uint16_t flush_stride;
    uint8_t duty_offset;
    uint8_t duty_width;
    uint8_t day_alrm;
    uint8_t mon_alrm;
    uint8_t century;
    IaPcBootFlags ia_pc_boot_flags __attribute__((packed));
    uint8_t reserved2;
    FixedFeatureFlags fixed_feature_flags;
    GenericAddress reset_reg;
    uint8_t reset_value;
    ArmBootFlags arm_boot_flags __attribute__((packed));
    uint8_t fadt_minor_version;
    Facs *x_firmware_ctrl __attribute__((packed));
    Dsdt *x_dsdt __attribute__((packed));
    GenericAddress x_pm1a_evt_blk;
    GenericAddress x_pm1b_evt_blk;
    GenericAddress x_pm1a_cnt_blk;
    GenericAddress x_pm1b_cnt_blk;
    GenericAddress x_pm2_cnt_blk;
    GenericAddress x_pm_tmr_blk;
    GenericAddress x_gpe0_blk;
    GenericAddress x_gpe1_blk;
    GenericAddress sleep_control_reg;
    GenericAddress sleep_status_reg;
};

} // namespace Acpi end
