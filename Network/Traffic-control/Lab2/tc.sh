#!/bin/bash
if="ens3"

tc q del dev $if root

tc q add dev $if root handle 1:0 htb default 10
tc c add dev $if parent 1:0 classid 1:1 htb rate 20mbit

tc c add dev $if parent 1:1 classid 1:3 htb rate 10mbps
tc c add dev $if parent 1:3 classid 1:31 htb rate 8mbps ceil 10mbps prio 0
tc c add dev $if parent 1:3 classid 1:33 htb rate 1mbps ceil 2mbps pri 1

tc f add dev $if parent 1:0 protocol ip prio 9 u32 match ip dst 192.168.1.10 flowid 1:31
tc f add dev $if parent 1:0 protocol ip prio 10 u32 match ip dst 192.168.1.20 flowid 1:33
tc f add dev $if parent 1:0 protocol ip prio 10 u32 match ip dst 192.168.1.30 flowid 1:33
