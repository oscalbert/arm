void vPortSVCHandler(void);
void xPortPendSVHandler(void);
void xPortSysTickHandler(void);


void sv_call_handler(void) {
    vPortSVCHandler();
}

void pend_sv_handler(void) {
    xPortPendSVHandler();
}

void sys_tick_handler(void) {
    xPortSysTickHandler();
}

