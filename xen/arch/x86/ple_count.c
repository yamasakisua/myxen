#include <xen/config.h>
#include <xen/types.h>
#include <xen/lib.h>
#include <xen/mm.h>
#include <xen/guest_access.h>
#include <xen/hypercall.h>
#include <public/sysctl.h>
#include <xen/sched.h>
#include <xen/event.h>
#include <xen/domain_page.h>
#include <asm/msr.h>
#include <xen/trace.h>
#include <xen/console.h>
#include <xen/iocap.h>
#include <asm/irq.h>
#include <asm/hvm/hvm.h>
#include <asm/hvm/support.h>
#include <asm/processor.h>
#include <asm/numa.h>
#include <xen/nodemask.h>
#include <xen/cpu.h>
#include <xsm/xsm.h>
#include <asm/psr.h>
#include <asm/hvm/vmx/vmcs.h>


unsigned long long ple_count = 0;
int ple_table_size = 0;
int ple_table_mode = 1;

#define PLE_TABLE_SIZE 1000

struct ple_info ple_table[PLE_TABLE_SIZE];

void do_set_ple_count(unsigned long long num){
	ple_count = num;
}

unsigned long long do_get_ple_count(void){
	return	ple_count;
}

unsigned long do_get_ple_table(void){
	return ple_table;
}

unsigned long long do_get_ple_elem(int index, int elem){
	switch(elem){
		case 1:
			return ple_table[index].vcpu_id;
		case 2:
			return ple_table[index].dom_id;
		case 3:
			return ple_table[index].ip;
		case 4:
			return ple_table[index].time;
		case 5:
			return ple_table[index].count;
		default:
			return 0;
	}
}

void do_reset_ple_table(int num){
	int i = 0;
    if(num != 0){
    	for(i = 0; i < PLE_TABLE_SIZE; i++){
    		ple_table[i].vcpu_id = 0;
    		ple_table[i].dom_id = 0;
    		ple_table[i].ip = 0;
    		ple_table[i].time = 0;
    		ple_table[i].count = 0;
    	}
    	ple_table_mode = num;
    	ple_table_size = 0;
    	ple_count = 0;
    }else{
        ple_table_size = PLE_TABLE_SIZE;
    } 
}
