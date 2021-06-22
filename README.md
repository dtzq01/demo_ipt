Demo for iptables developing ko and utilities.
ipt: based on iptables-1.8.6.tar and modify extensions;
ko: based on MARK module and parameters.

## Demo file
* libxt_DEMO.c as extension file in iptables
* demo.c ko file, custom your function here
## Compile
### ipt
``` bash
mkdir ins_dir
cd ipt
./configure --disable-nftables --prefix=$(pwd)/../ins_dir
make && make install

```

### ko
``` bash
make
```
## Run log

``` bash
test@test:~/code/demo_ipt$ sudo insmod demo.ko

test@test:~/code/demo_ipt/ins_dir/sbin$ ./iptables -j DEMO --help
DEMO: Could not determine whether revision 2 is supported, assuming it is.
iptables v1.8.6

...

Demo target options:
  --set value   pass value(char[20]) to ko

test@test:~/code/demo_ipt/ins_dir/sbin$ sudo ./iptables -t mangle -A POSTROUTING -d1.1.1.1 -j DEMO --set eth1

test@test:~/code/demo_ipt/ins_dir/sbin$ sudo ./iptables -t mangle -nvL
Chain PREROUTING (policy ACCEPT 1903 packets, 1103K bytes)
 pkts bytes target     prot opt in     out     source               destination         

Chain INPUT (policy ACCEPT 1903 packets, 1103K bytes)
 pkts bytes target     prot opt in     out     source               destination         

Chain FORWARD (policy ACCEPT 0 packets, 0 bytes)
 pkts bytes target     prot opt in     out     source               destination         

Chain OUTPUT (policy ACCEPT 2008 packets, 1924K bytes)
 pkts bytes target     prot opt in     out     source               destination         

Chain POSTROUTING (policy ACCEPT 2008 packets, 1924K bytes)
 pkts bytes target     prot opt in     out     source               destination         
  733  921K DEMO       all  --  *      *       0.0.0.0/0            192.168.248.1        DEMO value eth1 

test@test:~/code/demo_ipt/ins_dir/sbin$ dmesg 
[1037866.442384] eth1   
...
```