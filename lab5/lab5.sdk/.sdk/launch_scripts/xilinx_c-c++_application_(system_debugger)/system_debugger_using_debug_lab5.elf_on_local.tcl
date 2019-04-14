connect -url tcp:127.0.0.1:3121
source D:/xilinxwrk/lab5/lab5.sdk/system_wrapper_hw_platform_3/ps7_init.tcl
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent Zybo 210279A42846A"} -index 0
loadhw -hw D:/xilinxwrk/lab5/lab5.sdk/system_wrapper_hw_platform_3/system.hdf -mem-ranges [list {0x40000000 0xbfffffff}]
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent Zybo 210279A42846A"} -index 0
stop
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Zybo 210279A42846A"} -index 0
rst -processor
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Zybo 210279A42846A"} -index 0
dow D:/xilinxwrk/lab5/lab5.sdk/lab5/Debug/lab5.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Zybo 210279A42846A"} -index 0
con
