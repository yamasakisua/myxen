/******************************************************************************
 * asm-x86/hypercall.h
 */

#ifndef __ASM_X86_HYPERCALL_H__
#define __ASM_X86_HYPERCALL_H__

#include <public/physdev.h>
#include <public/arch-x86/xen-mca.h> /* for do_mca */
#include <xen/types.h>

/*
 * Both do_mmuext_op() and do_mmu_update():
 * We steal the m.s.b. of the @count parameter to indicate whether this
 * invocation of do_mmu_update() is resuming a previously preempted call.
 */
#define MMU_UPDATE_PREEMPTED          (~(~0U>>1))

extern long
do_event_channel_op_compat(
    XEN_GUEST_HANDLE_PARAM(evtchn_op_t) uop);

extern long
do_set_trap_table(
    XEN_GUEST_HANDLE_PARAM(const_trap_info_t) traps);

extern long
do_mmu_update(
    XEN_GUEST_HANDLE_PARAM(mmu_update_t) ureqs,
    unsigned int count,
    XEN_GUEST_HANDLE_PARAM(uint) pdone,
    unsigned int foreigndom);

extern long
do_set_gdt(
    XEN_GUEST_HANDLE_PARAM(xen_ulong_t) frame_list,
    unsigned int entries);

extern long
do_stack_switch(
    unsigned long ss,
    unsigned long esp);

extern long
do_fpu_taskswitch(
    int set);

extern long
do_set_debugreg(
    int reg,
    unsigned long value);

extern unsigned long
do_get_debugreg(
    int reg);

extern long
do_update_descriptor(
    u64 pa,
    u64 desc);

extern long
do_mca(XEN_GUEST_HANDLE_PARAM(xen_mc_t) u_xen_mc);

extern long
do_update_va_mapping(
    unsigned long va,
    u64 val64,
    unsigned long flags);

extern long
do_physdev_op(
    int cmd, XEN_GUEST_HANDLE_PARAM(void) arg);

extern long
do_update_va_mapping_otherdomain(
    unsigned long va,
    u64 val64,
    unsigned long flags,
    domid_t domid);

extern long
do_mmuext_op(
    XEN_GUEST_HANDLE_PARAM(mmuext_op_t) uops,
    unsigned int count,
    XEN_GUEST_HANDLE_PARAM(uint) pdone,
    unsigned int foreigndom);

extern unsigned long
do_iret(
    void);

extern long
do_set_callbacks(
    unsigned long event_address,
    unsigned long failsafe_address,
    unsigned long syscall_address);

extern long
do_set_segment_base(
    unsigned int which,
    unsigned long base);

extern int
compat_physdev_op(
    int cmd,
    XEN_GUEST_HANDLE_PARAM(void) arg);

extern int
arch_compat_vcpu_op(
    int cmd, struct vcpu *v, XEN_GUEST_HANDLE_PARAM(void) arg);

extern void
do_set_ple_count(
	unsigned long long);

extern unsigned long long 
do_get_ple_count(
	void);

extern unsigned long
do_get_ple_table(
	void);

extern unsigned long long
do_get_ple_elem(
	unsigned long long,
	int);

extern void
do_reset_ple_table(
	int);

extern unsigned long long
do_get_tsc_value(
    void);

extern void
do_set_ple_sched(
    int);

extern void
do_reset_runq_table(
    void);

extern int
do_get_runq_elem(
    unsigned int index,
    unsigned int cpu_num,
    unsigned int elem);
#endif /* __ASM_X86_HYPERCALL_H__ */
